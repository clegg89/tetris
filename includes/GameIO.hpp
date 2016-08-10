/**
 * @file GameIO.h
 * 
 * @author C. Smith
 * @date Dec 6, 2015
 */

#ifndef _GAMEIO_H_
#define _GAMEIO_H_

#include "Tetris.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"
#include "GameIOImpl.hpp"

class GameIO
{
    private:
        static GameIO pSelf;
        void internalDrawTetro(Tetromino* tetro, int x, int y, bool isBase);
        void internalDrawBlock(Color color, int x, int y);
        void callKeyCallback(eKeyCode keycode, eKeyDirection direction);

    protected:
        GameIO();
        virtual ~GameIO();

        int pWindowHeight, pWindowWidth;
        GameIOImpl* pImpl;
        KeyCallback pKeyCallbacks[NUM_KEYCODES];

    public:
        bool Init(const int windowHeight, const int windowWidth);
        void Close();

        void UnregisterKeyCBs(void);
        void RegisterKeyCB(tKeyCB callback, void* context, eKeyCode keycode);

        void ClearScreen(const Color bgColor = Color(0x00, 0x00, 0x00, 0xFF));
        void DrawRect(const int x, const int y, const int w, const int h, const Color color);
        void DrawBorder(const Color borderColor = Color(0x00, 0xFF, 0xFF, 0xFF), const Color bgColor = Color(0x00, 0x00, 0x00, 0xFF));
        void DrawBoard(Board* board);
        void DrawTetromino(Tetromino* tetro);
        void DrawNextTetromino(Tetromino* tetro);
        void PrintLevel(int level);
        void PrintScore(int score);
        void Print(const char* text, const int x, const int y, const hAlignment hAlign, vAlignment vAlign, const Color color);
        void Present();

        void LoadFontFromFile(const char* filename, int size);
        void LoadBgMusicFromFile(const char* filename);
        void PlayBgMusic();
        void PauseBgMusic();

        bool PollInputs();

        int GetWindowHeight() { return this->pWindowHeight; }
        int GetWindowWidth() { return this->pWindowWidth; }

        static GameIO* Instance()
        { return &pSelf; }
};



#endif /* _GAMEIO_H_ */
