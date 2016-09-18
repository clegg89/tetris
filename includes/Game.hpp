
/**
 * @file Game.h
 * @brief Interface to the Game class.
 * @author Casey Smith
 */

#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <string>

#include "GameIO.hpp"

class GameState;

class Game
{
    protected:
        bool pGameOver;
        GameIO *pGameIO;
        std::vector<GameState*> pStates;

    public:
        Game();
        virtual ~Game();

        bool Init(const std::string& exePath);
        void Close();

        void ChangeState(GameState* state);
        void PushState(GameState* state);
        void PopState();

        void HandleEvents();
        void Update();
        void Render();

        bool IsGameOver();
        void SetGameOver();
};

#endif /* _GAME_H_ */
