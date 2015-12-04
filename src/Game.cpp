
/**
 * @file Game.cpp
 * @brief Implementation of the Game Class
 * @author Casey Smith
 */

#include <SDL.h>
#include "Game.h"
#include "TetrominoFactory.h"

Game::Game() : pBgColor( {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE} ), pTetroColor( {0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE} ), pWindowWidth(640), pWindowHeight(480)
{
    this->pGameOver = false;
    this->pWindow = NULL;
    this->pRenderer = NULL;
    this->pBoard = NULL;
}

Game::~Game()
{
    this->Close();
}

bool Game::Init()
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

    this->pBoard = new Board();

    this->pBoard->Init();
    this->pBoard->AddTetromino(TetrominoFactory::GetRand());

    return true;
}

bool Game::Load()
{
    return true;
}

void Game::Update()
{
    static unsigned int prev_time = 0;
    unsigned int curr_time;
    SDL_Event oEvent;

    while(SDL_PollEvent(&oEvent) != 0)
    {
        if (oEvent.type == SDL_QUIT)
        {
            this->pGameOver = true;
        }
        else if (oEvent.type == SDL_KEYDOWN)
        {
            switch (oEvent.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    this->pGameOver = true;
                    break;
                case SDLK_w:
                case SDLK_UP:
                    this->pBoard->Rotate();
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    this->pBoard->MoveLeft();
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    this->pBoard->MoveRight();
                    break;
                default:
                    break;
            }
        }
        else if (oEvent.type == SDL_KEYUP)
        {
            switch (oEvent.key.keysym.sym)
            {
                case SDLK_s:
                case SDLK_DOWN:
                    break;
            }
        }
    }

    curr_time = SDL_GetTicks();
    if (curr_time > prev_time + TIME_BETWEEN_MOVES_MS)
    {
        prev_time = curr_time;
        this->pBoard->MoveDown();

        if (this->pBoard->IsTetrominoDead())
        {
        	this->pBoard->StoreTetromino();
            this->pBoard->EraseLines();

            this->pBoard->AddTetromino(TetrominoFactory::GetRand());
        }
    }
}

void Game::Render()
{
	Tetromino* currentTetro;

	SDL_Rect filledSquare;
	filledSquare.w = BLOCK_SIZE_PIXELS;
	filledSquare.h = BLOCK_SIZE_PIXELS;

    /* Clear the Screen */
    SDL_SetRenderDrawColor(this->pRenderer, this->pBgColor.r, this->pBgColor.g, this->pBgColor.b, this->pBgColor.a);
    SDL_RenderClear(this->pRenderer);

    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        for (int j = 0; j < BOARD_HEIGHT; ++j)
        {
            if (this->pBoard->IsFilled(i, j))
            {
                //Draw Rect
                filledSquare.x = i * BLOCK_SIZE_PIXELS;
                filledSquare.y = j * BLOCK_SIZE_PIXELS;

                SDL_SetRenderDrawColor(this->pRenderer, this->pTetroColor.r, this->pTetroColor.g, this->pTetroColor.b, this->pTetroColor.a);
                SDL_RenderFillRect(this->pRenderer, &filledSquare);
            }
        }
    }

    currentTetro = this->pBoard->GetTetro();

    for (int i = 0; i < TETROMINO_BLOCKS; ++i)
    {
    	for (int j = 0; j < TETROMINO_BLOCKS; ++j)
    	{
    		if (currentTetro->IsBlockFilled(i, j))
    		{
    			filledSquare.x = (i + currentTetro->GetX()) * BLOCK_SIZE_PIXELS;
    			filledSquare.y = (j + currentTetro->GetY()) * BLOCK_SIZE_PIXELS;

                SDL_SetRenderDrawColor(this->pRenderer, this->pTetroColor.r, this->pTetroColor.g, this->pTetroColor.b, this->pTetroColor.a);
                SDL_RenderFillRect(this->pRenderer, &filledSquare);
    		}
		}
	}

    SDL_RenderPresent(this->pRenderer);
}

void Game::Close()
{
    if(this->pBoard)
    {
        delete this->pBoard;
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

    SDL_Quit();
}

bool Game::IsGameOver()
{
    return this->pGameOver;
}
