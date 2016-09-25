/**
 * @file main.cpp
 * 
 * @author C. Smith
 * @date Apr 3, 2015
 */

#include <iostream>
#include <boost/filesystem.hpp>

#include "Game.hpp"
#include "IntroState.hpp"

namespace bfs = boost::filesystem;

Game* g_pGame;

int main(int argc, char* args[])
{
  bfs::path exeFile = bfs::path(args[0]);
    g_pGame = new Game();

    if (!g_pGame->Init(exeFile.parent_path().string()))
    {
        std::cerr << "Error Initializing Game" << std::endl;
        return -1;
    }

    g_pGame->ChangeState(IntroState::Instance());

    while (!g_pGame->IsGameOver())
    {
        g_pGame->HandleEvents();
        g_pGame->Update();
        g_pGame->Render();
    }

    g_pGame->Close();

    return 0;
}
