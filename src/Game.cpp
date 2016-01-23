
/**
 * @file Game.cpp
 * @brief Implementation of the Game Class
 * @author Casey Smith
 */

#include "Game.h"
#include "TetrominoFactory.h"
#include "Timer.h"

static const int scorePerLine[] =
{
        40,   // 1 Line
        100,  // 2 Lines
        300,  // 3 Lines
        1200, // 4 Lines
};

Game::Game()
{
    this->pGameOver = false;
    this->pGameIO = NULL;
    this->pBoard = NULL;
    this->pGameSpeed = 0; // ms between block moves
    this->pLevel = 0;
    this->pScore = 0;
    this->pLinesCleared = 0;
    this->pNextTetro = NULL;
    this->pTimer = NULL;
}

Game::~Game()
{
    this->Close();
}

bool Game::Init()
{
    this->pLevel = 0;
    this->pScore = 0;
    this->pLinesCleared = 0;

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

    this->pGameIO->LoadFontFromFile("media/Rupee_Foradian.ttf", 22);
    this->pTimer = new Timer();

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

    curr_time = this->pTimer->GetMilliSec();
    if ((curr_time - prev_time) >= this->pGameSpeed)
    {
        prev_time = curr_time;
        this->pBoard->MoveDown();

        if (this->pBoard->IsTetrominoDead())
        {
            int linesCleared;
        	this->pBoard->StoreTetromino();
        	linesCleared = this->pBoard->EraseLines();
        	if (linesCleared > 0)
        	{
                this->pScore += scorePerLine[linesCleared-1] * (this->pLevel + 1);
                this->pLinesCleared += linesCleared;
                if (this->pLinesCleared >= LINES_PER_LEVEL)
                {
                    this->pLevel++;
                    this->pGameSpeed = TIME_BETWEEN_MOVES_MS - (this->pLevel * 100); // TODO Improve equation, will be negative after 10 levels
                    this->pLinesCleared -= LINES_PER_LEVEL;
                }
        	}
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

    this->pGameIO->PrintLevel(this->pLevel);

    this->pGameIO->PrintScore(this->pScore);

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
        self->pGameSpeed = FAST_TIME_BETWEEN_MOVES_MS;
    }
    else
    {
        self->pGameSpeed = TIME_BETWEEN_MOVES_MS - (self->pLevel * 100);
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
