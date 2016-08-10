/**
 * @file PlayState.h
 * 
 * @author C. Smith
 * @date Jan 31, 2016
 */

#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

#include "GameState.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"
#include "TetrominoFactory.hpp"
#include "Timer.hpp"

class PlayState : public GameState
{
    public:
        bool Init();
        void Close();

        void Pause();
        void Resume();

        void HandleEvents(Game* game);
        void Update(Game* game);
        void Render(Game* game);

        static PlayState* Instance()
        { return &pSelf; }

    protected:
        PlayState();
        virtual ~PlayState();

        unsigned int pGameSpeed, pLevel, pScore, pLinesCleared;
        bool pMoveToPause;
        Tetromino* pNextTetro;
        Timer* pTimer;
        Board* pBoard;
        GameIO* pGameIO;

    private:
        static PlayState pSelf;

        static void KeyUpCB(void*, eKeyDirection);
        static void KeyDownCB(void*, eKeyDirection);
        static void KeyRightCB(void*, eKeyDirection);
        static void KeyLeftCB(void*, eKeyDirection);
        static void KeySpaceCB(void*, eKeyDirection);

        void internalRegisterCBs(void);
};


#endif /* _PLAYSTATE_H_ */
