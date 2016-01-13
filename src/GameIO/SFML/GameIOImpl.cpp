/**
 * @file GameIOImpl.cpp
 * 
 * @author C. Smith
 * @date Jan 13, 2016
 */

#include "GameIOImpl.h"

struct ioInternals
{
};

GameIOImpl::GameIOImpl()
{
    this->pInternals = new ioInternals;
}

GameIOImpl::~GameIOImpl()
{
    this->Destroy();

    delete this->pInternals;
}

bool GameIOImpl::Init(const int windowHeight, const int windowWidth, const Color* bgColor)
{
    return true;
}

void GameIOImpl::Destroy()
{
}

void GameIOImpl::ClearScreen(const Color* bgColor)
{
}

void GameIOImpl::DrawRect(const int x, const int y, const int w, const int h, const Color* color)
{
}

void GameIOImpl::DrawTexture(const int x, const int y, const int w, const int h, const Color* color)
{
}

void GameIOImpl::Present()
{
}

void GameIOImpl::LoadBgMusicFromFile(const char* filename)
{
}

void GameIOImpl::PlayBgMusic()
{
}

void GameIOImpl::callKeyCallback(eKeyCode keycode, eKeyDirection direction, const KeyCallback callbacks[4])
{
    if (callbacks[keycode].callback != NULL)
    {
        callbacks[keycode].callback(callbacks[keycode].context, direction);
    }
}

bool GameIOImpl::PollInputs(const KeyCallback callbacks[4])
{
    return true;
}


