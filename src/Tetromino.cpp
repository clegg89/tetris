/**
 * @file Tetromino.cpp
 * 
 * @author C. Smith
 * @date Nov 28, 2015
 */

#include "Tetromino.h"

#include <cstdlib>
#include <ctime>

static SDL_Color tetromino_colors[] =
{
        { 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE },
        { 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE },
        { 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE },
};

static const int num_tetromino_colors = sizeof(tetromino_colors)/sizeof(tetromino_colors[0]);

SDL_Color* Tetromino::getRandColor()
{
    int i;

    srand(time(NULL));

    i = rand() % num_tetromino_colors;

    return &tetromino_colors[i];
}

Tetromino::Tetromino(int (&blocks)[TETROMINO_ROTATIONS][TETROMINO_BLOCKS][TETROMINO_BLOCKS], int (&offset)[TETROMINO_ROTATIONS][2]) : pBlocks (blocks), pOffset (offset)
{
    this->pRotationIndex = 0;
    this->pXPos = 0;
    this->pYPos = 0;
    this->pColor = NULL;
}

Tetromino::~Tetromino()
{
}

void Tetromino::Init()
{
    this->pXPos = this->pOffset[this->pRotationIndex][0];
    this->pYPos = this->pOffset[this->pRotationIndex][1];
    this->pColor = this->getRandColor();
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

SDL_Color* Tetromino::GetColor()
{
    return this->pColor;
}
