/**
 * @file Tetris.h
 * 
 * @author C. Smith
 * @date Nov 28, 2015
 */

#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <iostream>
#include "Config.hpp"

#define NUM_TETROMINO       7
#define TETROMINO_ROTATIONS 4
#define TETROMINO_BLOCKS    5

#define MOVE_SPEED_SLOW     1
#define MOVE_SPEED_NORMAL   1
#define MOVE_SPEED_FAST     1

#define BLOCK_SIZE_PIXELS   30
#define BORDER_SIZE_PIXELS  20
#define BOARD_WIDTH         10
#define BOARD_HEIGHT        16

#define NEXT_TETROMINO_X    13
#define NEXT_TETROMINO_Y    5

#define TIME_BETWEEN_MOVES_MS       1000
#define FAST_TIME_BETWEEN_MOVES_MS  (TIME_BETWEEN_MOVES_MS / 4)

#define LINES_PER_LEVEL     10

typedef enum
{
    IO_KEY_DOWN,
    IO_KEY_UP,
} eKeyDirection;

typedef enum
{
    KEYCODE_UP,
    KEYCODE_DOWN,
    KEYCODE_RIGHT,
    KEYCODE_LEFT,
    KEYCODE_SPACE,

    /* Add all Keycodes above this line */
    NUM_KEYCODES,
} eKeyCode;

typedef void (*tKeyCB)(void*, eKeyDirection);

typedef struct
{
        tKeyCB callback;
        void* context;
} KeyCallback;

#endif /* _TETRIS_H_ */
