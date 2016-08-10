/**
 * @file PlayState.cpp
 * 
 * @author C. Smith
 * @date Jan 31, 2016
 */

#include "PlayState.hpp"
#include "PauseState.hpp"

PlayState PlayState::pSelf;

static const int scorePerLine[] =
{
        40,   // 1 Line
        100,  // 2 Lines
        300,  // 3 Lines
        1200, // 4 Lines
};

PlayState::PlayState()
{
    this->pGameIO = GameIO::Instance();
    this->pBoard = new Board();
    this->pGameSpeed = 0; // ms between block moves
    this->pLevel = 0;
    this->pScore = 0;
    this->pLinesCleared = 0;
    this->pMoveToPause = false;
    this->pNextTetro = NULL;
    this->pTimer = new Timer();
}

PlayState::~PlayState()
{
    this->Close();

    if (this->pBoard)
    {
        delete this->pBoard;
    }

    if (this->pTimer)
    {
        delete this->pTimer;
    }
}

bool PlayState::Init()
{
    this->pLevel = 0;
    this->pScore = 0;
    this->pLinesCleared = 0;

    this->pMoveToPause = false;

    this->pGameIO->UnregisterKeyCBs();
    this->internalRegisterCBs();

    this->pBoard->Init();
    this->pNextTetro = TetrominoFactory::GetRand();
    this->pNextTetro->Init();
    this->pBoard->AddTetromino(this->pNextTetro);

    this->pGameSpeed = TIME_BETWEEN_MOVES_MS;

    this->pNextTetro = TetrominoFactory::GetRand();
    this->pNextTetro->Init();

    this->pGameIO->PlayBgMusic();

    return true;
}

void PlayState::Close()
{
    this->pGameSpeed = 0; // ms between block moves
    this->pLevel = 0;
    this->pScore = 0;
    this->pLinesCleared = 0;
    this->pMoveToPause = false;
    this->pNextTetro = NULL;
    this->pGameIO->UnregisterKeyCBs();
}

void PlayState::Pause()
{
    this->pGameIO->PauseBgMusic();
    this->pGameIO->UnregisterKeyCBs();
}

void PlayState::Resume()
{
    this->pGameIO->PlayBgMusic();
    this->internalRegisterCBs();
    this->pMoveToPause = false;
}

void PlayState::HandleEvents(Game *game)
{
    if (!this->pGameIO->PollInputs())
    {
        game->SetGameOver();
    }
}

void PlayState::Update(Game *game)
{
    static unsigned int prev_time = 0;
    unsigned int curr_time;

    if (this->pMoveToPause)
    {
        game->PushState(PauseState::Instance());
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

        	if (this->pBoard->IsGameOver())
        	{
        	    game->SetGameOver();
        	}

            this->pNextTetro->Init();
            this->pBoard->AddTetromino(this->pNextTetro);

            this->pNextTetro = TetrominoFactory::GetRand();
            this->pNextTetro->Init();
        }
    }
}

void PlayState::Render(Game * game)
{
	this->pGameIO->ClearScreen();

	this->pGameIO->DrawBorder();

    this->pGameIO->DrawBoard(this->pBoard);

    this->pGameIO->DrawTetromino(this->pBoard->GetTetro());

    this->pGameIO->DrawNextTetromino(this->pNextTetro);

    this->pGameIO->PrintLevel(this->pLevel);

    this->pGameIO->PrintScore(this->pScore);
}

void PlayState::KeyUpCB(void* pThis, eKeyDirection direction)
{
    PlayState* self = static_cast<PlayState*>(pThis);

    if (direction  == IO_KEY_DOWN)
    {
        self->pBoard->Rotate();
    }
}

void PlayState::KeyDownCB(void* pThis, eKeyDirection direction)
{
    PlayState* self = static_cast<PlayState*>(pThis);

    if (direction  == IO_KEY_DOWN)
    {
        self->pGameSpeed = FAST_TIME_BETWEEN_MOVES_MS;
    }
    else
    {
        self->pGameSpeed = TIME_BETWEEN_MOVES_MS - (self->pLevel * 100);
    }
}

void PlayState::KeyLeftCB(void* pThis, eKeyDirection direction)
{
    PlayState* self = static_cast<PlayState*>(pThis);

    if (direction  == IO_KEY_DOWN)
    {
        self->pBoard->MoveLeft();
    }
}

void PlayState::KeyRightCB(void* pThis, eKeyDirection direction)
{
    PlayState* self = static_cast<PlayState*>(pThis);

    if (direction  == IO_KEY_DOWN)
    {
        self->pBoard->MoveRight();
    }
}

void PlayState::KeySpaceCB(void* pThis, eKeyDirection direction)
{
    PlayState* self = static_cast<PlayState*>(pThis);

    if (direction == IO_KEY_DOWN)
    {
        self->pMoveToPause = true;
    }
}

void PlayState::internalRegisterCBs()
{
    this->pGameIO->RegisterKeyCB(PlayState::KeyUpCB, this, KEYCODE_UP);
    this->pGameIO->RegisterKeyCB(PlayState::KeyDownCB, this, KEYCODE_DOWN);
    this->pGameIO->RegisterKeyCB(PlayState::KeyLeftCB, this, KEYCODE_LEFT);
    this->pGameIO->RegisterKeyCB(PlayState::KeyRightCB, this, KEYCODE_RIGHT);
    this->pGameIO->RegisterKeyCB(PlayState::KeySpaceCB, this, KEYCODE_SPACE);
}
