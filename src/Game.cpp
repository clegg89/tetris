
/**
 * @file Game.cpp
 * @brief Implementation of the Game Class
 * @author Casey Smith
 */

#include "Game.h"
#include "TetrominoFactory.h"
#include "Timer.h"

Game::Game()
{
    this->pGameOver = false;
    this->pGameIO = NULL;
    this->pBoard = NULL;
    this->pGameSpeed = 0;
    this->pNextTetro = NULL;
    this->pTimer = NULL;
}

Game::~Game()
{
    this->Close();
}

bool Game::Init()
{
    this->pGameIO = new GameIO(480, 640, {0, 0, 0, 0xFF}, {0, 0xFF, 0xFF, 0xFF});
    if (!this->pGameIO->Init())
    {
        return false;
    }

    this->pGameIO->RegisterKeyCB(Game::KeyUpCB, this, KEYCODE_UP);
    this->pGameIO->RegisterKeyCB(Game::KeyDownCB, this, KEYCODE_DOWN);
    this->pGameIO->RegisterKeyCB(Game::KeyLeftCB, this, KEYCODE_LEFT);
    this->pGameIO->RegisterKeyCB(Game::KeyRightCB, this, KEYCODE_RIGHT);

    this->pBoard = new Board();

    this->pBoard->Init();
    this->pNextTetro = TetrominoFactory::GetRand();
    this->pNextTetro->SetColor();
    this->pBoard->AddTetromino(this->pNextTetro);

    this->pGameSpeed = TIME_BETWEEN_MOVES_MS;

    this->pNextTetro = TetrominoFactory::GetRand();
    this->pNextTetro->SetColor();

    this->pGameIO->LoadBgMusicFromFile("media/tetris.wav");
    this->pGameIO->PlayBgMusic();

    this->pTimer = new Timer();

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

    if (!this->pGameIO->PollInputs())
    {
        this->pGameOver = true;
        return;
    }

    curr_time = this->pTimer->GetTicks();
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

    if(this->pTimer)
    {
        delete this->pTimer;
    }

    this->pGameIO->Destroy();
}

bool Game::IsGameOver()
{
    return this->pGameOver;
}

void Game::KeyUpCB(void* pThis, eKeyDirection direction)
{
    Game* self = static_cast<Game*>(pThis);

    if (direction  == IO_KEY_DOWN)
    {
        self->pBoard->Rotate();
    }
}

void Game::KeyDownCB(void* pThis, eKeyDirection direction)
{
    Game* self = static_cast<Game*>(pThis);

    if (direction  == IO_KEY_DOWN)
    {
        self->pGameSpeed = TIME_BETWEEN_MOVES_MS / 4;
    }
    else
    {
        self->pGameSpeed = TIME_BETWEEN_MOVES_MS;
    }
}

void Game::KeyLeftCB(void* pThis, eKeyDirection direction)
{
    Game* self = static_cast<Game*>(pThis);

    if (direction  == IO_KEY_DOWN)
    {
        self->pBoard->MoveLeft();
    }
}

void Game::KeyRightCB(void* pThis, eKeyDirection direction)
{
    Game* self = static_cast<Game*>(pThis);

    if (direction  == IO_KEY_DOWN)
    {
        self->pBoard->MoveRight();
    }
}
