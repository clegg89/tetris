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
#include "GameIOImpl.h"

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
        void PrintLevel(int level);
        void PrintScore(int score);
        void Present();

        void LoadFontFromFile(const char* filename, int size);
        void LoadBgMusicFromFile(const char* filename);
        void PlayBgMusic();

        bool PollInputs();
};



#endif /* _GAMEIO_H_ */
