/**
 * @file GameIO.cpp
 * 
 * @author C. Smith
 * @date Dec 6, 2015
 */


#include "GameIO.h"

GameIO::GameIO(const int windowHeight, const int windowWidth, const SDL_Color bgColor) : pWindowHeight( windowHeight ), pWindowWidth( windowWidth ), pBgColor( bgColor )
{
    this->pWindow = NULL;
    this->pRenderer = NULL;

    this->pKeyCallbacks[0] = { NULL, NULL };
    this->pKeyCallbacks[1] = { NULL, NULL };
}

GameIO::~GameIO()
{
    this->Destroy();
}

bool GameIO::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("SDL ERROR: %s", SDL_GetError());
        return false;
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

    return true;
}

void GameIO::Destroy()
{
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

void GameIO::DrawBoard(Board* board)
{
	SDL_Rect filledSquare;
	SDL_Color* squareColor;

	filledSquare.w = BLOCK_SIZE_PIXELS - 2;
	filledSquare.h = BLOCK_SIZE_PIXELS - 2;

    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        for (int j = 0; j < BOARD_HEIGHT; ++j)
        {
            squareColor = board->GetBlockColor(i, j);

            filledSquare.x = (i * BLOCK_SIZE_PIXELS) + 2;
            filledSquare.y = (j * BLOCK_SIZE_PIXELS) + 2;

            SDL_SetRenderDrawColor(this->pRenderer, squareColor->r, squareColor->g, squareColor->b, squareColor->a);
            SDL_RenderFillRect(this->pRenderer, &filledSquare);
        }
    }
}

void GameIO::DrawTetromino(Tetromino* tetro)
{
	SDL_Rect filledSquare;
	SDL_Color* squareColor;

	filledSquare.w = BLOCK_SIZE_PIXELS - 2;
	filledSquare.h = BLOCK_SIZE_PIXELS - 2;

    squareColor = tetro->GetColor();

    for (int i = 0; i < TETROMINO_BLOCKS; ++i)
    {
    	for (int j = 0; j < TETROMINO_BLOCKS; ++j)
    	{
    		if (tetro->IsBlockFilled(i, j))
    		{
    			filledSquare.x = ((i + tetro->GetX()) * BLOCK_SIZE_PIXELS) + 2;
    			filledSquare.y = ((j + tetro->GetY()) * BLOCK_SIZE_PIXELS) + 2;

                SDL_SetRenderDrawColor(this->pRenderer, squareColor->r, squareColor->g, squareColor->b, squareColor->a);
                SDL_RenderFillRect(this->pRenderer, &filledSquare);
    		}
		}
	}
}

void GameIO::Present()
{
    SDL_RenderPresent(this->pRenderer);
}

bool GameIO::PollInputs()
{
    SDL_Event oEvent;

    while(SDL_PollEvent(&oEvent) != 0)
    {
        if (oEvent.type == SDL_QUIT)
        {
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
