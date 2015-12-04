/**
 * @file Tetromino.cpp
 * 
 * @author C. Smith
 * @date Nov 28, 2015
 */

#include "Tetromino.h"

Tetromino::Tetromino(int (&blocks)[TETROMINO_ROTATIONS][TETROMINO_BLOCKS][TETROMINO_BLOCKS], int (&offset)[TETROMINO_ROTATIONS][2]) : pBlocks (blocks), pOffset (offset)
{
    //this->pBlocks = blocks;
    //this->pOffset = offset;
    this->pRotationIndex = 0;
    this->pXPos = 0;
    this->pYPos = 0;
}

Tetromino::~Tetromino()
{
}

void Tetromino::Init()
{
    this->pXPos = this->pOffset[this->pRotationIndex][0];
    this->pYPos = this->pOffset[this->pRotationIndex][1];
}

void Tetromino::RotateClockwise()
{
    this->pRotationIndex++;

    if (this->pRotationIndex >= TETROMINO_ROTATIONS)
    {
        this->pRotationIndex = 0;
    }
}

void Tetromino::RotateCounterClockwise()
{
    this->pRotationIndex--;

    if (this->pRotationIndex < 0)
    {
        this->pRotationIndex = TETROMINO_ROTATIONS - 1;
    }
}

int Tetromino::GetX()
{
    return this->pXPos;
}

int Tetromino::GetY()
{
    return this->pYPos;
}

void Tetromino::SetX(int x)
{
    this->pXPos = x;
}

void Tetromino::SetY(int y)
{
    this->pYPos = y;
}

bool Tetromino::IsBlockFilled(int x, int y)
{
    if (this->pBlocks[this->pRotationIndex][x][y] != 0)
    {
        return true;
    }

    return false;
}