
/**
 * @file Game.h
 * @brief Interface to the Game class.
 * @author Casey Smith
 */

#include "GameIO.h"
#include "Board.h"
#include "Tetromino.h"
#include "Timer.h"

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

    public:
        Game();
        virtual ~Game();

        bool Init();
        void Update();
        void Render();
        void Close();
        bool IsGameOver();
};
