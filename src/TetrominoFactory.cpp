/**
 * @file TetrominoFactory.cpp
 * 
 * @author C. Smith
 * @date Nov 28, 2015
 */

#include "TetrominoFactory.h"

#include <cstdlib>
#include <ctime>

#define RED     { 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE }
#define GREEN   { 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE }
#define BLUE    { 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE }
#define ORANGE  { 0xFF, 0xA5, 0x00, SDL_ALPHA_OPAQUE }
#define CYAN    { 0x00, 0xFF, 0xFF, SDL_ALPHA_OPAQUE }
#define YELLOW  { 0xFF, 0x00, 0xFF, SDL_ALPHA_OPAQUE }
#define MAGENTA { 0xFF, 0xFF, 0x00, SDL_ALPHA_OPAQUE }

static SDL_Color TetroColors[NUM_TETROMINO] =
{
        YELLOW,
        ORANGE,
        RED,
        CYAN,
        BLUE,
        MAGENTA,
        GREEN
};

static int PossibleTetros[NUM_TETROMINO][TETROMINO_ROTATIONS][TETROMINO_BLOCKS][TETROMINO_BLOCKS] =
{
    // Square
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        }
    },
    // I
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {1, 1, 1, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },
    // L
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },
    // L mirrored
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
        }
    },
    // N
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },
    // N mirrored
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },
    // T
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }
    }
};


int PossibleInitialPositions[NUM_TETROMINO][TETROMINO_ROTATIONS][2] =
{
    /* Square */
    {
        {2, -3},
        {2, -3},
        {2, -3},
        {2, -3}
    },
    /* I */
    {
        {2, -2},
        {2, -3},
        {2, -2},
        {2, -3}
    },
    /* L */
    {
        {2, -3},
        {2, -3},
        {2, -3},
        {2, -2}
    },
    /* L mirrored */
    {
        {2, -3},
        {2, -2},
        {2, -3},
        {2, -3}
    },
    /* N */
    {
        {2, -3},
        {2, -3},
        {2, -3},
        {2, -2}
    },
    /* N mirrored */
    {
        {2, -3},
        {2, -3},
        {2, -3},
        {2, -2}
    },
    /* T */
    {
        {2, -3},
        {2, -3},
        {2, -3},
        {2, -2}
    }
};

Tetromino TetrominoFactory::pTetros[] =
{
    /* Square */
    Tetromino(PossibleTetros[0], PossibleInitialPositions[0], &TetroColors[0]),
    /* I */
    Tetromino(PossibleTetros[1], PossibleInitialPositions[1], &TetroColors[1]),
    /* L */
    Tetromino(PossibleTetros[2], PossibleInitialPositions[2], &TetroColors[2]),
    /* L mirrored */
    Tetromino(PossibleTetros[3], PossibleInitialPositions[3], &TetroColors[3]),
    /* N */
    Tetromino(PossibleTetros[4], PossibleInitialPositions[4], &TetroColors[4]),
    /* N mirrored */
    Tetromino(PossibleTetros[5], PossibleInitialPositions[5], &TetroColors[5]),
    /* T */
    Tetromino(PossibleTetros[6], PossibleInitialPositions[6], &TetroColors[6])
};

TetrominoFactory::TetrominoFactory()
{
}

TetrominoFactory::~TetrominoFactory()
{
}

Tetromino* TetrominoFactory::GetRand()
{
    srand(time(NULL));
    int index = rand() % NUM_TETROMINO;

    return &TetrominoFactory::pTetros[index];
}
