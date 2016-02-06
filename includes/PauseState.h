/**
 * @file PauseState.h
 * 
 * @author C. Smith
 * @date Feb 3, 2016
 */

#ifndef _PAUSESTATE_H_
#define _PAUSESTATE_H_

#include "GameState.h"
#include "PlayState.h"

class PauseState : public GameState
{
    public:
        bool Init();
        void Close();

        void Pause();
        void Resume();

        void HandleEvents(Game* game);
        void Update(Game* game);
        void Render(Game* game);

        static PauseState* Instance()
        { return &pSelf; }

    protected:
        PauseState();
        virtual ~PauseState();

        bool pUnpause;

    private:
        static PauseState pSelf;

        static void KeySpaceCB(void*, eKeyDirection);

};

#endif /* _PAUSESTATE_H_ */
