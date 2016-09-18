
/**
 * @file Game.cpp
 * @brief Implementation of the Game Class
 * @author Casey Smith
 */

#include "Game.hpp"
#include "GameState.hpp"

Game::Game()
{
    this->pGameOver = false;
    this->pGameIO = GameIO::Instance();
}

Game::~Game()
{
}

bool Game::Init(const std::string& exePath)
{
  std::string mediaPath = exePath + "/../" + RESOURCE_PREFIX + "/media/";
  std::string fontFile = mediaPath + "Rupee_Foradian.ttf";
  std::string musicFile = mediaPath + "tetris.wav";
  std::string blockFile = mediaPath + "block.bmp";

    if (!this->pGameIO->Init(blockFile, 480, 640))
    {
        return false;
    }

    this->pGameIO->LoadFontFromFile(fontFile.c_str(), 22);
    this->pGameIO->LoadBgMusicFromFile(musicFile.c_str());

    return true;
}

void Game::Close()
{
    while (!this->pStates.empty())
    {
        this->pStates.back()->Close();
        this->pStates.pop_back();
    }

    this->pGameIO->Close();
}

void Game::ChangeState(GameState* state)
{
    // cleanup the current state
    if (!this->pStates.empty())
    {
        this->pStates.back()->Close();
        this->pStates.pop_back();
    }

    // store and init the new state
    this->pStates.push_back(state);
    this->pStates.back()->Init();
}

void Game::PushState(GameState* state)
{
    // pause current state
    if (!this->pStates.empty())
    {
        this->pStates.back()->Pause();
    }

    // store and init the new state
    this->pStates.push_back(state);
    this->pStates.back()->Init();
}

void Game::PopState()
{
    // cleanup the current state
    if (!this->pStates.empty())
    {
        this->pStates.back()->Close();
        this->pStates.pop_back();
    }

    // resume the previous state
    if (!this->pStates.empty())
    {
        this->pStates.back()->Resume();
    }
}

void Game::HandleEvents()
{
    this->pStates.back()->HandleEvents(this);
}

void Game::Update()
{
    this->pStates.back()->Update(this);
}

void Game::Render()
{
    this->pStates.back()->Render(this);
    this->pGameIO->Present();
}

bool Game::IsGameOver()
{
    return this->pGameOver;
}

void Game::SetGameOver()
{
    this->pGameOver = true;
}
