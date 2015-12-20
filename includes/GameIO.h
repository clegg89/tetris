/**
 * @file GameIO.h
 * 
 * @author C. Smith
 * @date Dec 6, 2015
 */

#ifndef _GAMEIO_H_
#define _GAMEIO_H_

#include <SDL.h>

#include "Tetris.h"
#include "Board.h"
#include "Tetromino.h"

#define IO_KEY_DOWN 0
#define IO_KEY_UP   1

typedef void (*tKeyCB)(SDL_Keycode, void*);

typedef struct
{
        tKeyCB callback;
        void* context;
} KeyCallback;

class GameIO
{
    private:
        void internalDrawTetro(Tetromino* tetro, int x, int y);
        void internalDrawBlock(SDL_Color* color, int x, int y);

    protected:
        const int pWindowHeight, pWindowWidth;
        const SDL_Color pBgColor, pBorderColor;
        SDL_Window*   pWindow;
        SDL_Renderer* pRenderer;
        SDL_Texture* pBlockTexture;
        KeyCallback pKeyCallbacks[2];

    public:
        GameIO(const int windowHeight, const int windowWidth, const SDL_Color bgColor, const SDL_Color borderCOlor);
        virtual ~GameIO();

        bool Init();
        void Destroy();

        void RegisterKeyCB(tKeyCB callback, void* context, int keyDirection);

        void ClearScreen();
        void DrawBorder();
        void DrawBoard(Board* board);
        void DrawTetromino(Tetromino* tetro);
        void DrawNextTetromino(Tetromino* tetro);
        void Present();

        bool PollInputs();
};



#endif /* _GAMEIO_H_ */
