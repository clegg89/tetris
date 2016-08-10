/**
 * @file IntroState.cpp
 * 
 * @author C. Smith
 * @date Feb 2, 2016
 */

#include "IntroState.hpp"
#include "PlayState.hpp"

IntroState IntroState::pSelf;

IntroState::IntroState()
{
    this->pGameIO = GameIO::Instance();
    this->pStarted = false;
}

IntroState::~IntroState()
{
    this->pGameIO = NULL;
}

bool IntroState::Init()
{
    this->pGameIO->UnregisterKeyCBs();
    this->pGameIO->RegisterKeyCB(IntroState::KeySpaceCB, this, KEYCODE_SPACE);
    this->pStarted = false;
    return true;
}

void IntroState::Close()
{
    this->pGameIO->UnregisterKeyCBs();
}

void IntroState::Pause()
{
    this->pGameIO->UnregisterKeyCBs();
}

void IntroState::Resume()
{
    this->pGameIO->RegisterKeyCB(IntroState::KeySpaceCB, this, KEYCODE_SPACE);
}

void IntroState::HandleEvents(Game *game)
{
    if (!this->pGameIO->PollInputs())
    {
        game->SetGameOver();
    }
}

void IntroState::Update(Game *game)
{
    if (this->pStarted)
    {
        game->ChangeState(PlayState::Instance());
    }
}

void IntroState::Render(Game *game)
{
    int x,y;
    Color color_white(0xFF, 0xFF, 0xFF, 0xFF);

    x = this->pGameIO->GetWindowWidth() / 2;
    y = this->pGameIO->GetWindowHeight() / 2;

    this->pGameIO->ClearScreen();

    this->pGameIO->Print("Press Space to Start", x, y, HALIGN_CENTERED, VALIGN_CENTERED, color_white);
}

void IntroState::KeySpaceCB(void* pThis, eKeyDirection direction)
{
    IntroState *self = static_cast<IntroState*>(pThis);

    if (direction  == IO_KEY_DOWN)
    {
        self->pStarted = true;
    }
}


