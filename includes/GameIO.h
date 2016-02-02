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
        static GameIO pSelf;
        void internalDrawTetro(Tetromino* tetro, int x, int y);
        void internalDrawBlock(Color* color, int x, int y);
        void callKeyCallback(eKeyCode keycode, eKeyDirection direction);

    protected:
        int pWindowHeight, pWindowWidth;
        Color pBgColor, pBorderColor;
        GameIOImpl* pImpl;
        KeyCallback pKeyCallbacks[NUM_KEYCODES];

    public:
        GameIO();
        virtual ~GameIO();

        static GameIO* Instance()
        { return &pSelf; }

        bool Init(const int windowHeight, const int windowWidth, const Color bgColor, const Color borderColor);
        void Destroy();

        void UnregisterKeyCBs(void);
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
        void PauseBgMusic();

        bool PollInputs();
};



#endif /* _GAMEIO_H_ */
