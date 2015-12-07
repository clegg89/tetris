
/**
 * @file Game.h
 * @brief Interface to the Game class.
 * @author Casey Smith
 */

#include <SDL.h>
#include "GameIO.h"
#include "Board.h"
#include "Tetromino.h"

class Game
{
    private:
        static void KeyUpCB(SDL_Keycode, void*);
        static void KeyDownCB(SDL_Keycode, void*);

    protected:
        bool pGameOver;
        GameIO *pGameIO;
        SDL_Window*   pWindow;
        SDL_Renderer* pRenderer;
        int pGameSpeed;

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
