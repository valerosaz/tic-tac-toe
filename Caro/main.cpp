/******************************************************
 * Created by Phuc Le and Hong Trinh
 * Assignment 3
 * Minimax alpha-beta Pruning in Tictactoe game
 * 5 in a row to win
 ******************************************************/

#include <iostream>
#include "tictactoe.h"
#include "gamePlay.h"
#include "Computer.h"

int main() {

    std::cout << "Welcome to TicTacToe" << std::endl;
    game::gamePlay tictactoe;
    tictactoe.runGame();
    return 0;
}