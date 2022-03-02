/******************************************************
 * Created by Phuc Le and Hong Trinh
 * Assignment 3
 * Minimax alpha-beta Pruning in Tictactoe game
 * 5 in a row to win
 ******************************************************/


#ifndef FINAL_GAMEPLAY_H
#define FINAL_GAMEPLAY_H

#include "tictactoe.h"
#include <vector>
#include <stdio.h>

namespace game{
    class gamePlay{
    public:
        gamePlay();
        void playGround();
        char getCurrentSym(int);
        void runGame();

    private:
        tictactoe Tictactoe;
    };
}


#endif //FINAL_GAMEPLAY_H
