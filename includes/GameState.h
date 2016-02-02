/**
 * @file GameState.h
 * 
 * @author C. Smith
 * @date Jan 30, 2016
 */

#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "Game.h"

class GameState
{
    public:
        virtual bool Init() = 0;
        virtual void Close() = 0;

        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual void HandleEvents(Game* game) = 0;
        virtual void Update(Game* game) = 0;
        virtual void Render(Game* game) = 0;

        void ChangeState(Game* game, GameState* state)
        { game->ChangeState(state); }

    protected:
        GameState() { }
        virtual ~GameState() { };
};



#endif /* _GAMESTATE_H_ */
