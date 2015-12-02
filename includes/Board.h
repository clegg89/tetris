/**
 * @file Board.h
 * 
 * @author C. Smith
 * @date Nov 27, 2015
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "Tetris.h"
#include "Tetromino.h"

class Board
{
    private:
        void EraseLine(int posY);
        bool IsMovePossible(int tetroX, int tetroY);
        void FillBlocks();

    protected:
        bool pBoard[BOARD_WIDTH][BOARD_HEIGHT];
        Tetromino* pTetro;
        int pTetroSpeed;
        bool pIsTetroDead;

    public:
        Board();
        virtual ~Board();

        void Init();
        void AddTetromino(Tetromino *tetro);
        bool IsTetrominoDead();
        void EraseLines();
        bool IsFilled(int x, int y);

        void Rotate();
        void SetSpeed(int speed);
        void MoveLeft();
        void MoveRight();
        void MoveDown();
};


#endif /* _BOARD_H_ */
