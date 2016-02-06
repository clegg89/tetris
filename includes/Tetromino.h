/**
 * @file Tetromino.h
 * 
 * @author C. Smith
 * @date Nov 27, 2015
 */

#ifndef _TETROMINO_H_
#define _TETROMINO_H_

#include "Tetris.h"
#include "Color.h"

class Tetromino
{
    protected:
        int (&pBlocks)[TETROMINO_ROTATIONS][TETROMINO_BLOCKS][TETROMINO_BLOCKS];
        int (&pOffset)[TETROMINO_ROTATIONS][2];
        int pRotationIndex;
        int pXPos;
        int pYPos;
        Color* pColor;

    public:
        Tetromino(int (&blocks)[TETROMINO_ROTATIONS][TETROMINO_BLOCKS][TETROMINO_BLOCKS], int (&offset)[TETROMINO_ROTATIONS][2], Color* pColor);
        virtual ~Tetromino();

        void Init();
        void RotateClockwise();
        void RotateCounterClockwise();
        int GetX();
        int GetY();
        void SetX(int x);
        void SetY(int y);
        bool IsBlockFilled(int x, int y, bool baseTetro = false);
        Color *GetColor();
};



#endif /* _TETROMINO_H_ */
