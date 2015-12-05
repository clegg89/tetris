/**
 * @file Board.cpp
 * 
 * @author C. Smith
 * @date Nov 28, 2015
 */

#include <iostream>
#include "Board.h"


Board::Board()
{
    this->pTetro = NULL;
    this->pIsTetroDead = true;
}

Board::~Board()
{
    this->pTetro = NULL;
}

void Board::Init()
{
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        for (int j = 0; j < BOARD_HEIGHT; ++j)
        {
            this->pBoard[i][j] = false;
        }
    }
}

void Board::AddTetromino(Tetromino *tetro)
{
    this->pTetro = tetro;

    this->pTetro->Init();
    this->pIsTetroDead = false;
}

bool Board::IsTetrominoDead()
{
    return this->pIsTetroDead;
}

void Board::EraseLine(int posY)
{
    for (int j = posY; j > 0; --j)
    {
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            this->pBoard[i][j] = this->pBoard[i][j-1];
        }
    }
}

void Board::EraseLines()
{
    for (int j = 0; j < BOARD_HEIGHT; ++j)
    {
        int i = 0;
        while (i < BOARD_WIDTH)
        {
            if (!this->pBoard[i][j]) { break; }
            i++;
        }

        if (i == BOARD_WIDTH) { this->EraseLine(j); }
    }
}

bool Board::IsFilled(int x, int y)
{
	if (x < 0 || y < 0 ||
	    x >= BOARD_WIDTH || y >= BOARD_HEIGHT)
		return false;

    return this->pBoard[x][y];
}

void Board::Rotate()
{
    this->pTetro->RotateClockwise();

    if (!this->IsMovePossible(this->pTetro->GetX(), this->pTetro->GetY()))
    {
        this->pTetro->RotateCounterClockwise();
    }
}

void Board::MoveLeft()
{
    int tetroX = this->pTetro->GetX() - 1;

    if (this->IsMovePossible(tetroX, this->pTetro->GetY()))
    {
        this->pTetro->SetX(tetroX);
    }
}

void Board::MoveRight()
{
    int tetroX = this->pTetro->GetX() + 1;

    if (this->IsMovePossible(tetroX, this->pTetro->GetY()))
    {
        this->pTetro->SetX(tetroX);
    }
}

void Board::MoveDown()
{
    if (this->pIsTetroDead)
    {
        return;
    }

    // Get the current position
    int tetroY = this->pTetro->GetY();

    // Increment the Y value
    tetroY++;

    // Check for collisions
    if (this->IsMovePossible(this->pTetro->GetX(), tetroY))
    {
        this->pTetro->SetY(tetroY);
    }
    else
    {
        this->pIsTetroDead = true;
    }
}

bool Board::IsMovePossible(int tetroX, int tetroY)
{
    for (int i = 0; i < TETROMINO_BLOCKS; ++i)
    {
        for (int j = 0; j < TETROMINO_BLOCKS; ++j)
        {
            // Check if the tetromino is outside the limits of the board
            if ( tetroX + i < 0             ||
                 tetroX + i > BOARD_WIDTH - 1    ||
                 tetroY + j > BOARD_HEIGHT - 1
                )
            {
                // Location is outside the board, see if the block is filled.
                if (this->pTetro->IsBlockFilled(i, j))
                {
                    return false;
                }
            }

            if (tetroY + j >= 0)
            {
                if (this->pTetro->IsBlockFilled(i, j) && this->IsFilled(tetroX + i, tetroY + j))
                {
                    return false;
                }
            }
        }
    }
    // no collision
    return true;
}

void Board::StoreTetromino()
{
    int tetroX = this->pTetro->GetX();
    int tetroY = this->pTetro->GetY();

    for (int i = 0; i < TETROMINO_BLOCKS; ++i)
    {
        int boardX = i + tetroX;
        for (int j = 0; j < TETROMINO_BLOCKS; ++j)
        {
            int boardY = j + tetroY;

            if (boardX >= 0 && boardY >= 0 &&
                boardX < BOARD_WIDTH && boardY < BOARD_HEIGHT &&
                !(this->IsFilled(boardX, boardY)))
            {
                this->pBoard[boardX][boardY] = this->pTetro->IsBlockFilled(i, j);
            }
        }
    }
}
