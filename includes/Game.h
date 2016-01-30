
/**
 * @file Game.h
 * @brief Interface to the Game class.
 * @author Casey Smith
 */

#ifndef _GAME_H_
#define _GAME_H_

#include <vector>

#include "GameIO.h"
#include "Board.h"
#include "Tetromino.h"
#include "Timer.h"

class GameState;

class Game
{
    private:
        static void KeyUpCB(void*, eKeyDirection);
        static void KeyDownCB(void*, eKeyDirection);
        static void KeyRightCB(void*, eKeyDirection);
        static void KeyLeftCB(void*, eKeyDirection);

    protected:
        bool pGameOver;
        GameIO *pGameIO;
        int pGameSpeed, pLevel, pScore, pLinesCleared;
        Tetromino* pNextTetro;
        Timer* pTimer;
        Board* pBoard;
        std::vector<GameState*> pStates;

    public:
        Game();
        virtual ~Game();

        bool Init();
        void Close();

        void ChangeState(GameState* state);
        void PushState(GameState* state);
        void PopState();

        void HandleEvents();
        void Update();
        void Render();

        bool IsGameOver();
};

#endif /* _GAME_H_ */
