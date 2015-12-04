
/**
 * @file Game.h
 * @brief Interface to the Game class.
 * @author Casey Smith
 */

#include <SDL.h>
#include "Board.h"
#include "Tetromino.h"

class Game
{
    private:
        const SDL_Color pBgColor;
        const SDL_Color pTetroColor;
        const int pWindowWidth;
        const int pWindowHeight;

    protected:
        bool pGameOver;
        SDL_Window*   pWindow;
        SDL_Renderer* pRenderer;

        Board* pBoard;

    public:
        Game();
        virtual ~Game();

        bool Init();
        bool Load();
        void Update();
        void Render();
        void Close();
        bool IsGameOver();
};
