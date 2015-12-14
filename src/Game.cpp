
/**
 * @file Game.cpp
 * @brief Implementation of the Game Class
 * @author Casey Smith
 */

#include <SDL.h>
#include "Game.h"
#include "TetrominoFactory.h"

Game::Game()
{
    this->pGameOver = false;
    this->pGameIO = NULL;
    this->pWindow = NULL;
    this->pRenderer = NULL;
    this->pBoard = NULL;
    this->pGameSpeed = 0;
    this->pNextTetro = NULL;
}

Game::~Game()
{
    this->Close();
}

bool Game::Init()
{
    this->pGameIO = new GameIO(480, 640, {0, 0, 0, SDL_ALPHA_OPAQUE}, {0, 0xFF, 0xFF, SDL_ALPHA_OPAQUE});
    if (!this->pGameIO->Init())
    {
        return false;
    }

    this->pGameIO->RegisterKeyCB(Game::KeyDownCB, this, IO_KEY_DOWN);
    this->pGameIO->RegisterKeyCB(Game::KeyUpCB, this, IO_KEY_UP);

    this->pBoard = new Board();

    this->pBoard->Init();
    this->pNextTetro = TetrominoFactory::GetRand();
    this->pNextTetro->SetColor();
    this->pBoard->AddTetromino(this->pNextTetro);

    this->pGameSpeed = TIME_BETWEEN_MOVES_MS;

    this->pNextTetro = TetrominoFactory::GetRand();
    this->pNextTetro->SetColor();

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

    this->pGameIO->PollInputs();

    curr_time = SDL_GetTicks();
    if (curr_time > prev_time + this->pGameSpeed)
    {
        prev_time = curr_time;
        this->pBoard->MoveDown();

        if (this->pBoard->IsTetrominoDead())
        {
        	this->pBoard->StoreTetromino();
            this->pBoard->EraseLines();
            this->pGameOver = this->pBoard->IsGameOver();

            this->pBoard->AddTetromino(this->pNextTetro);

            this->pNextTetro = TetrominoFactory::GetRand();
            this->pNextTetro->SetColor();
        }
    }
}

void Game::Render()
{
	this->pGameIO->ClearScreen();

	this->pGameIO->DrawBorder();

    this->pGameIO->DrawBoard(this->pBoard);

    this->pGameIO->DrawTetromino(this->pBoard->GetTetro());

    this->pGameIO->DrawNextTetromino(this->pNextTetro);

    this->pGameIO->Present();
}

void Game::Close()
{
    if(this->pBoard)
    {
        delete this->pBoard;
    }

    this->pGameIO->Destroy();
}

bool Game::IsGameOver()
{
    return this->pGameOver;
}

void Game::KeyUpCB(SDL_Keycode keycode, void* pThis)
{
    Game* self = static_cast<Game*>(pThis);

    switch (keycode)
    {
        case SDLK_s:
        case SDLK_DOWN:
            self->pGameSpeed = TIME_BETWEEN_MOVES_MS;
            break;
    }
}

void Game::KeyDownCB(SDL_Keycode keycode, void* pThis)
{
    Game* self = static_cast<Game*>(pThis);

    switch (keycode)
    {
        case SDLK_ESCAPE:
            self->pGameOver = true;
            break;
        case SDLK_w:
        case SDLK_UP:
            self->pBoard->Rotate();
            break;
        case SDLK_s:
        case SDLK_DOWN:
            self->pGameSpeed = TIME_BETWEEN_MOVES_MS / 4;
            break;
        case SDLK_a:
        case SDLK_LEFT:
            self->pBoard->MoveLeft();
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            self->pBoard->MoveRight();
            break;
        default:
            break;
    }
}
