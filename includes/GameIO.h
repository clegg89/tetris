/**
 * @file GameIO.h
 * 
 * @author C. Smith
 * @date Dec 6, 2015
 */

#ifndef _GAMEIO_H_
#define _GAMEIO_H_

#include "Tetris.h"
#include "Color.h"
#include "Board.h"
#include "Tetromino.h"

typedef enum
{
    IO_KEY_DOWN,
    IO_KEY_UP,
} eKeyDirection;

typedef enum
{
    KEYCODE_UP    = 0,
    KEYCODE_DOWN  = 1,
    KEYCODE_RIGHT = 2,
    KEYCODE_LEFT  = 3,
} eKeyCode;

typedef void (*tKeyCB)(void*, eKeyDirection);

typedef struct
{
        tKeyCB callback;
        void* context;
} KeyCallback;

class GameIOImpl;

class GameIO
{
    private:
        void internalDrawTetro(Tetromino* tetro, int x, int y);
        void internalDrawBlock(Color* color, int x, int y);
        void callKeyCallback(eKeyCode keycode, eKeyDirection direction);

    protected:
        const int pWindowHeight, pWindowWidth;
        const Color pBgColor, pBorderColor;
        GameIOImpl* pImpl;
        KeyCallback pKeyCallbacks[4];

    public:
        GameIO(const int windowHeight, const int windowWidth, const Color bgColor, const Color borderColor);
        virtual ~GameIO();

        bool Init();
        void Destroy();

        void RegisterKeyCB(tKeyCB callback, void* context, eKeyCode keycode);

        void ClearScreen();
        void DrawBorder();
        void DrawBoard(Board* board);
        void DrawTetromino(Tetromino* tetro);
        void DrawNextTetromino(Tetromino* tetro);
        void Present();

        void LoadBgMusicFromFile(const char* filename);
        void PlayBgMusic();

        bool PollInputs();
};



#endif /* _GAMEIO_H_ */
