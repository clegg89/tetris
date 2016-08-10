/**
 * @file Board.h
 * 
 * @author C. Smith
 * @date Nov 27, 2015
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "Tetris.hpp"
#include "Tetromino.hpp"
#include "Color.hpp"

class Board
{
    private:
        void EraseLine(int posY);
        bool IsMovePossible(int tetroX, int tetroY);

    protected:
        Color* pBoard[BOARD_WIDTH][BOARD_HEIGHT];
        Tetromino* pTetro;
        bool pIsTetroDead;

    public:
        Board();
        virtual ~Board();

        Tetromino* GetTetro() { return this->pTetro; }

        void Init();
        void AddTetromino(Tetromino *tetro);
        bool IsTetrominoDead();
        void StoreTetromino();
        int EraseLines();
        bool IsFilled(int x, int y);
        Color* GetBlockColor(int x, int y);
        bool IsGameOver();

        void Rotate();
        void MoveLeft();
        void MoveRight();
        void MoveDown();
};


#endif /* _BOARD_H_ */
