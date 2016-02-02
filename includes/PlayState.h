/**
 * @file PlayState.h
 * 
 * @author C. Smith
 * @date Jan 31, 2016
 */

#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

#include "GameState.h"
#include "Board.h"
#include "Tetromino.h"
#include "TetrominoFactory.h"
#include "Timer.h"

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

        int pGameSpeed, pLevel, pScore, pLinesCleared;
        Tetromino* pNextTetro;
        Timer* pTimer;
        Board* pBoard;

    private:
        static PlayState pSelf;
        GameIO* pGameIO;

        static void KeyUpCB(void*, eKeyDirection);
        static void KeyDownCB(void*, eKeyDirection);
        static void KeyRightCB(void*, eKeyDirection);
        static void KeyLeftCB(void*, eKeyDirection);

        void internalRegisterCBs(void);
};


#endif /* _PLAYSTATE_H_ */
