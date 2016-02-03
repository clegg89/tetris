/**
 * @file IntroState.h
 * 
 * @author C. Smith
 * @date Feb 2, 2016
 */

#ifndef _INTROSTATE_H_
#define _INTROSTATE_H_

#include "GameState.h"
#include "GameIO.h"

class IntroState : public GameState
{
    public:
        bool Init();
        void Close();

        void Pause();
        void Resume();

        void HandleEvents(Game* game);
        void Update(Game* game);
        void Render(Game* game);

        static IntroState* Instance()
        { return &pSelf; }

    protected:
        IntroState();
        virtual ~IntroState();

        GameIO* pGameIO;
        bool pStarted;
    private:
        static IntroState pSelf;

        static void KeySpaceCB(void*, eKeyDirection);
};

#endif /* _INTROSTATE_H_ */
