/**
 * @file GameIO.cpp
 * 
 * @author C. Smith
 * @date Dec 6, 2015
 */


#include "GameIO.h"

GameIO::GameIO(const int windowHeight, const int windowWidth, const SDL_Color bgColor, const SDL_Color borderColor) : pWindowHeight( windowHeight ), pWindowWidth( windowWidth ), pBgColor( bgColor ), pBorderColor( borderColor )
{
    this->pWindow = NULL;
    this->pRenderer = NULL;
    this->pBlockTexture = NULL;

    this->pKeyCallbacks[0] = { NULL, NULL };
    this->pKeyCallbacks[1] = { NULL, NULL };

    this->pBgMusic = NULL;
}

GameIO::~GameIO()
{
    this->Destroy();
}

bool GameIO::Init()
{
    SDL_Surface* loadedSurface;
    const char * blockImagePath = "media/block.bmp";

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("SDL ERROR: %s", SDL_GetError());
        return false;
    }

    if (Mix_Init(MIX_INIT_MP3))
    {
        SDL_Log("Error: Could not initialize mixer: %s", Mix_GetError());
    }

    if (Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2046 ) != 0)
    {
        SDL_Log("Error: Could not open audio: %s", Mix_GetError());
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        SDL_Log("Warning: Linear texture filtering not enabled");
    }

    this->pWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, this->pWindowWidth, this->pWindowHeight,
            SDL_WINDOW_SHOWN);

    if (this->pWindow == NULL)
    {
        SDL_Log("SDL ERROR: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!this->pRenderer)
    {
        SDL_Log("SDL ERROR: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(this->pRenderer, this->pBgColor.r, this->pBgColor.g, this->pBgColor.b, this->pBgColor.a);

    loadedSurface = SDL_LoadBMP(blockImagePath);
    if( loadedSurface == NULL )
    {
        SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", blockImagePath, SDL_GetError() );
        return false;
    }

    this->pBlockTexture = SDL_CreateTextureFromSurface(this->pRenderer, loadedSurface);
    if( this->pBlockTexture == NULL )
    {
        SDL_Log( "Unable to create texture! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    SDL_FreeSurface(loadedSurface);

    return true;
}

void GameIO::Destroy()
{
    if( this->pBgMusic )
    {
        if( Mix_PlayingMusic() )
        {
            Mix_HaltMusic();
        }

        Mix_FreeMusic(this->pBgMusic);
    }

    if( this->pBlockTexture )
    {
        SDL_DestroyTexture(this->pBlockTexture);
        this->pBlockTexture = NULL;
    }
    if(this->pRenderer)
    {
        SDL_DestroyRenderer(this->pRenderer);
        this->pRenderer = NULL;
    }

    if(this->pWindow)
    {
        SDL_DestroyWindow(this->pWindow);
        this->pWindow = NULL;
    }

    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();
}

void GameIO::RegisterKeyCB(tKeyCB callback, void* context, int keyDirection)
{
    if (keyDirection != IO_KEY_DOWN && keyDirection != IO_KEY_UP)
    {
        return;
    }

    this->pKeyCallbacks[keyDirection].callback = callback;
    this->pKeyCallbacks[keyDirection].context = context;
}

void GameIO::ClearScreen()
{
    SDL_SetRenderDrawColor(this->pRenderer, this->pBgColor.r, this->pBgColor.g, this->pBgColor.b, this->pBgColor.a);
    SDL_RenderClear(this->pRenderer);
}

void GameIO::DrawBorder()
{
    SDL_Rect fill_rect;

    fill_rect.x = 0;
    fill_rect.y = 0;
    fill_rect.w = ( BORDER_SIZE_PIXELS * 2 ) + ( BLOCK_SIZE_PIXELS * BOARD_WIDTH );
    fill_rect.h = ( BLOCK_SIZE_PIXELS * BOARD_HEIGHT );

    SDL_SetRenderDrawColor(this->pRenderer, this->pBorderColor.r, this->pBorderColor.g, this->pBorderColor.b, this->pBorderColor.a);
    SDL_RenderFillRect(this->pRenderer, &fill_rect);

    fill_rect.x += BORDER_SIZE_PIXELS;
    fill_rect.w = ( BLOCK_SIZE_PIXELS * BOARD_WIDTH );
    fill_rect.h = ( BLOCK_SIZE_PIXELS * BOARD_HEIGHT );

    SDL_SetRenderDrawColor(this->pRenderer, this->pBgColor.r, this->pBgColor.g, this->pBgColor.b, this->pBgColor.a);
    SDL_RenderFillRect(this->pRenderer, &fill_rect);
}

void GameIO::DrawBoard(Board* board)
{
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        for (int j = 0; j < BOARD_HEIGHT; ++j)
        {
            if (board->IsFilled(i, j))
            {
                this->internalDrawBlock(board->GetBlockColor(i, j), i, j);
            }
        }
    }
}

void GameIO::DrawTetromino(Tetromino* tetro)
{
    this->internalDrawTetro(tetro, tetro->GetX(), tetro->GetY());
}

void GameIO::DrawNextTetromino(Tetromino* tetro)
{
    this->internalDrawTetro(tetro, NEXT_TETROMINO_X, NEXT_TETROMINO_Y);
}

void GameIO::internalDrawTetro(Tetromino* tetro, int x, int y)
{
    for (int i = 0; i < TETROMINO_BLOCKS; ++i)
    {
    	for (int j = 0; j < TETROMINO_BLOCKS; ++j)
    	{
    		if (tetro->IsBlockFilled(i, j))
    		{
    		    this->internalDrawBlock(tetro->GetColor(), (i + x), (j + y));
    		}
		}
	}
}

void GameIO::internalDrawBlock(SDL_Color* color, int x, int y)
{
    SDL_Rect filledSquare;

    filledSquare.w = BLOCK_SIZE_PIXELS;
    filledSquare.h = BLOCK_SIZE_PIXELS;
    filledSquare.x = BORDER_SIZE_PIXELS + ( x * BLOCK_SIZE_PIXELS );
    filledSquare.y = ( y * BLOCK_SIZE_PIXELS );

    //SDL_SetRenderDrawColor(this->pRenderer, color->r, color->g, color->b, color->a);
    //SDL_RenderFillRect(this->pRenderer, &filledSquare);
    SDL_SetTextureColorMod(this->pBlockTexture, color->r, color->g, color->b);
    SDL_RenderCopy(this->pRenderer, this->pBlockTexture, NULL, &filledSquare);
}

void GameIO::Present()
{
    SDL_RenderPresent(this->pRenderer);
}

void GameIO::LoadBgMusicFromFile(const char * filename)
{
    if (this->pBgMusic)
        return;

    this->pBgMusic = Mix_LoadMUS(filename);
    if (this->pBgMusic == NULL)
    {
        SDL_Log("Error: Could not load music from file %s: %s", filename, Mix_GetError());
    }
}

void GameIO::PlayBgMusic()
{
    if (!this->pBgMusic)
        return;

    if (!Mix_PlayingMusic())
    {
        Mix_PlayMusic(this->pBgMusic, -1);
    }
}

bool GameIO::PollInputs()
{
    SDL_Event oEvent;

    while(SDL_PollEvent(&oEvent) != 0)
    {
        if (oEvent.type == SDL_QUIT)
        {
            Mix_HaltMusic();
            return false;
        }
        else if (oEvent.type == SDL_KEYDOWN)
        {
            if (this->pKeyCallbacks[IO_KEY_DOWN].callback)
            {
                this->pKeyCallbacks[IO_KEY_DOWN].callback(oEvent.key.keysym.sym, this->pKeyCallbacks[IO_KEY_DOWN].context);
            }
        }
        else if (oEvent.type == SDL_KEYUP)
        {
            if (this->pKeyCallbacks[IO_KEY_UP].callback)
            {
                this->pKeyCallbacks[IO_KEY_UP].callback(oEvent.key.keysym.sym, this->pKeyCallbacks[IO_KEY_UP].context);
            }
        }
    }

    return true;
}
