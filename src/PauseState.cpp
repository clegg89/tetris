/**
 * @file PauseState.cpp
 * 
 * @author C. Smith
 * @date Feb 3, 2016
 */

#include "PauseState.h"
#include "Tetris.h"

PauseState PauseState::pSelf;

PauseState::PauseState()
{
    this->pUnpause = false;
}

PauseState::~PauseState()
{
}


bool PauseState::Init()
{
    GameIO* io = GameIO::Instance();

    io->UnregisterKeyCBs();
    io->RegisterKeyCB(PauseState::KeySpaceCB, this, KEYCODE_SPACE);

    this->pUnpause = false;

    return true;
}

void PauseState::Close()
{
    GameIO* io = GameIO::Instance();

    io->UnregisterKeyCBs();
}

void PauseState::Pause()
{
    GameIO* io = GameIO::Instance();

    io->UnregisterKeyCBs();
}

void PauseState::Resume()
{
    GameIO* io = GameIO::Instance();

    io->RegisterKeyCB(PauseState::KeySpaceCB, this, KEYCODE_SPACE);
}

void PauseState::HandleEvents(Game* game)
{
    GameIO* io = GameIO::Instance();

    if (!io->PollInputs())
    {
        game->SetGameOver();
    }
}

void PauseState::Update(Game* game)
{
    if (this->pUnpause)
    {
        game->PopState();
    }
}

void PauseState::Render(Game* game)
{
    PlayState* play = PlayState::Instance();
    GameIO* io = GameIO::Instance();
    Color bgColor(0x00, 0x00, 0x00, 0x80);
    int x = io->GetWindowWidth() / 2;
    int y = io->GetWindowHeight() / 2;

    play->Render(game);

    io->ClearScreen(bgColor);
    io->Print("Press Space to Continue", x, y, HALIGN_CENTERED, VALIGN_CENTERED, Color(0xFF, 0xFF, 0xFF, 0xFF));
}

void PauseState::KeySpaceCB(void* pThis, eKeyDirection direction)
{
    PauseState *self = static_cast<PauseState*>(pThis);

    if (direction == IO_KEY_DOWN)
    {
        self->pUnpause = true;
    }
}
