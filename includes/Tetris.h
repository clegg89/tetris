/**
 * @file Tetris.h
 * 
 * @author C. Smith
 * @date Nov 28, 2015
 */

#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <iostream>

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

#define TIME_BETWEEN_MOVES_MS 1000

#endif /* _TETRIS_H_ */
