/**
 * @file GameIO.cpp
 * 
 * @author C. Smith
 * @date Dec 6, 2015
 */

#include <SDL.h>
#include <SDL_mixer.h>

#include "GameIO.h"

class GameIOImpl
{
    public:
        SDL_Window*   pWindow;
        SDL_Renderer* pRenderer;
        SDL_Texture* pBlockTexture;
        Mix_Music* pBgMusic;
};

GameIO::GameIO(const int windowHeight, const int windowWidth, const Color bgColor, const Color borderColor) : pWindowHeight( windowHeight ), pWindowWidth( windowWidth ), pBgColor( bgColor ), pBorderColor( borderColor )
{
    this->pImpl = new GameIOImpl();
    this->pImpl->pWindow = NULL;
    this->pImpl->pRenderer = NULL;
    this->pImpl->pBlockTexture = NULL;
    this->pImpl->pBgMusic = NULL;

    this->pKeyCallbacks[KEYCODE_UP].callback = NULL;
    this->pKeyCallbacks[KEYCODE_DOWN].callback = NULL;
    this->pKeyCallbacks[KEYCODE_LEFT].callback = NULL;
    this->pKeyCallbacks[KEYCODE_RIGHT].callback = NULL;
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

    this->pImpl->pWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, this->pWindowWidth, this->pWindowHeight,
            SDL_WINDOW_SHOWN);

    if (this->pImpl->pWindow == NULL)
    {
        SDL_Log("SDL ERROR: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    this->pImpl->pRenderer = SDL_CreateRenderer(this->pImpl->pWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!this->pImpl->pRenderer)
    {
        SDL_Log("SDL ERROR: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(this->pImpl->pRenderer, this->pBgColor.r, this->pBgColor.g, this->pBgColor.b, this->pBgColor.a);

    loadedSurface = SDL_LoadBMP(blockImagePath);
    if( loadedSurface == NULL )
    {
        SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", blockImagePath, SDL_GetError() );
        return false;
    }

    this->pImpl->pBlockTexture = SDL_CreateTextureFromSurface(this->pImpl->pRenderer, loadedSurface);
    if( this->pImpl->pBlockTexture == NULL )
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
    if( this->pImpl->pBgMusic )
    {
        if( Mix_PlayingMusic() )
        {
            Mix_HaltMusic();
        }

        Mix_FreeMusic(this->pImpl->pBgMusic);
    }

    if( this->pImpl->pBlockTexture )
    {
        SDL_DestroyTexture(this->pImpl->pBlockTexture);
        this->pImpl->pBlockTexture = NULL;
    }
    if(this->pImpl->pRenderer)
    {
        SDL_DestroyRenderer(this->pImpl->pRenderer);
        this->pImpl->pRenderer = NULL;
    }

    if(this->pImpl->pWindow)
    {
        SDL_DestroyWindow(this->pImpl->pWindow);
        this->pImpl->pWindow = NULL;
    }

    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();
}

static bool validateKeycode(eKeyCode keycode)
{
    if (keycode != KEYCODE_UP   &&
        keycode != KEYCODE_DOWN &&
        keycode != KEYCODE_LEFT &&
        keycode != KEYCODE_RIGHT)
    {
        return false;
    }

    return true;
}

void GameIO::RegisterKeyCB(tKeyCB callback, void* context, eKeyCode keycode)
{
    if (!validateKeycode(keycode))
        return;

    this->pKeyCallbacks[keycode].callback = callback;
    this->pKeyCallbacks[keycode].context = context;
}

void GameIO::ClearScreen()
{
    SDL_SetRenderDrawColor(this->pImpl->pRenderer, this->pBgColor.r, this->pBgColor.g, this->pBgColor.b, this->pBgColor.a);
    SDL_RenderClear(this->pImpl->pRenderer);
}

void GameIO::DrawBorder()
{
    SDL_Rect fill_rect;

    fill_rect.x = 0;
    fill_rect.y = 0;
    fill_rect.w = ( BORDER_SIZE_PIXELS * 2 ) + ( BLOCK_SIZE_PIXELS * BOARD_WIDTH );
    fill_rect.h = ( BLOCK_SIZE_PIXELS * BOARD_HEIGHT );

    SDL_SetRenderDrawColor(this->pImpl->pRenderer, this->pBorderColor.r, this->pBorderColor.g, this->pBorderColor.b, this->pBorderColor.a);
    SDL_RenderFillRect(this->pImpl->pRenderer, &fill_rect);

    fill_rect.x += BORDER_SIZE_PIXELS;
    fill_rect.w = ( BLOCK_SIZE_PIXELS * BOARD_WIDTH );
    fill_rect.h = ( BLOCK_SIZE_PIXELS * BOARD_HEIGHT );

    SDL_SetRenderDrawColor(this->pImpl->pRenderer, this->pBgColor.r, this->pBgColor.g, this->pBgColor.b, this->pBgColor.a);
    SDL_RenderFillRect(this->pImpl->pRenderer, &fill_rect);
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

void GameIO::internalDrawBlock(Color* color, int x, int y)
{
    SDL_Rect filledSquare;

    filledSquare.w = BLOCK_SIZE_PIXELS;
    filledSquare.h = BLOCK_SIZE_PIXELS;
    filledSquare.x = BORDER_SIZE_PIXELS + ( x * BLOCK_SIZE_PIXELS );
    filledSquare.y = ( y * BLOCK_SIZE_PIXELS );

    SDL_SetTextureColorMod(this->pImpl->pBlockTexture, color->r, color->g, color->b);
    SDL_RenderCopy(this->pImpl->pRenderer, this->pImpl->pBlockTexture, NULL, &filledSquare);
}

void GameIO::Present()
{
    SDL_RenderPresent(this->pImpl->pRenderer);
}

void GameIO::LoadBgMusicFromFile(const char * filename)
{
    if (this->pImpl->pBgMusic)
        return;

    this->pImpl->pBgMusic = Mix_LoadMUS(filename);
    if (this->pImpl->pBgMusic == NULL)
    {
        SDL_Log("Error: Could not load music from file %s: %s", filename, Mix_GetError());
    }
}

void GameIO::PlayBgMusic()
{
    if (!this->pImpl->pBgMusic)
        return;

    if (!Mix_PlayingMusic())
    {
        Mix_PlayMusic(this->pImpl->pBgMusic, -1);
    }
}

void GameIO::callKeyCallback(eKeyCode keycode, eKeyDirection direction)
{
    if (this->pKeyCallbacks[keycode].callback != NULL)
    {
        this->pKeyCallbacks[keycode].callback(this->pKeyCallbacks[keycode].context, direction);
    }
}

bool GameIO::PollInputs()
{
    SDL_Event oEvent;

    while(SDL_PollEvent(&oEvent) != 0)
    {
        if (oEvent.type == SDL_QUIT ||
            (oEvent.type == SDL_KEYDOWN && oEvent.key.keysym.sym == SDLK_ESCAPE))
        {
            Mix_HaltMusic();
            return false;
        }
        else if (oEvent.type == SDL_KEYDOWN || oEvent.type == SDL_KEYUP)
        {
            switch (oEvent.key.keysym.sym)
            {
                case SDLK_w:
                case SDLK_UP:
                    this->callKeyCallback(KEYCODE_UP, (oEvent.type == SDL_KEYDOWN) ? IO_KEY_DOWN : IO_KEY_UP);
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    this->callKeyCallback(KEYCODE_DOWN, (oEvent.type == SDL_KEYDOWN) ? IO_KEY_DOWN : IO_KEY_UP);
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    this->callKeyCallback(KEYCODE_LEFT, (oEvent.type == SDL_KEYDOWN) ? IO_KEY_DOWN : IO_KEY_UP);
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    this->callKeyCallback(KEYCODE_RIGHT, (oEvent.type == SDL_KEYDOWN) ? IO_KEY_DOWN : IO_KEY_UP);
                    break;
                default:
                    break;
            }
        }
    }

    return true;
}
