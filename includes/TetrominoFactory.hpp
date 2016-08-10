/**
 * @file TetrominoFactory.h
 * 
 * @author C. Smith
 * @date Nov 27, 2015
 */

#ifndef _TETROMINOFACTORY_H_
#define _TETROMINOFACTORY_H_

#include "Tetromino.hpp"

class TetrominoFactory
{
    private:
        static Tetromino pTetros[];

    public:
        TetrominoFactory();
        virtual ~TetrominoFactory();

        static Tetromino* GetRand();
};



#endif /* _TETROMINOFACTORY_H_ */
