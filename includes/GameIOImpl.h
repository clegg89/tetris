/**
 * @file GameIOImpl.h
 * 
 * @author C. Smith
 * @date Jan 13, 2016
 */

#ifndef _GAMEIOIMPL_H_
#define _GAMEIOIMPL_H_

#include "Tetris.h"
#include "Color.h"
#include "Board.h"
#include "Tetromino.h"

typedef enum
{
    HALIGN_LEFT,
    HALIGN_CENTERED,
    HALIGN_RIGHT,
} hAlignment;

typedef enum
{
    VALIGN_TOP,
    VALIGN_CENTERED,
    VALIGN_BOTTOM,
} vAlignment;

struct ioInternals;

class GameIOImpl
{
    public:
        GameIOImpl();
        virtual ~GameIOImpl();

        bool Init(const int windowHeight, const int windowWidth, const Color bgColor);
        void Close();

        void ClearScreen(const Color bgColor);
        void DrawRect(const int x, const int y, const int w, const int h, const Color color);
        void DrawTexture(const int x, const int y, const int w, const int h, const Color color);
        void PrintText(const char* text, const int x, const int y, const hAlignment hAlign, vAlignment vAlign, const Color color);
        void Present();

        void LoadFontFromFile(const char* filename, int size);
        void LoadBgMusicFromFile(const char* filename);

        void PlayBgMusic();
        void PauseBgMusic();

        bool PollInputs(const KeyCallback callbacks[4]);

    protected:
        ioInternals* pInternals;

        void callKeyCallback(eKeyCode keycode, eKeyDirection direction, const KeyCallback callbacks[4]);
};


#endif /* _GAMEIOIMPL_H_ */
