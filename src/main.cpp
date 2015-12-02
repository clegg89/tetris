/**
 * @file main.cpp
 * 
 * @author C. Smith
 * @date Apr 3, 2015
 */

#include <iostream>

#include "Game.h"

Game* g_pGame;

int main(int argc, char* args[])
{
    g_pGame = new Game();

    if (!g_pGame->Init())
    {
        std::cerr << "Error Initializing Pong" << std::endl;
        return -1;
    }

    if (!g_pGame->Load())
    {
        std::cerr << "Error Loading Pong" << std::endl;
        g_pGame->Close();
        return -2;
    }

    while (!g_pGame->IsGameOver())
    {
        g_pGame->Update();
        g_pGame->Render();
    }

    g_pGame->Close();

    return 0;
}
