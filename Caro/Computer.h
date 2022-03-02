/******************************************************
 * Created by Phuc Le and Hong Trinh
 * Assignment 3
 * Minimax alpha-beta Pruning in Tictactoe game
 * 5 in a row to win
 ******************************************************/

#ifndef GAMECARO_COMPUTER_H
#define GAMECARO_COMPUTER_H

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "tictactoe.h"

class Computer {
private:
    std::unordered_map<std::string, int> hashmap;
public:
    std::vector<int> nextmoveAlBe(game::tictactoe &);
    int minimaxAlBe(game::tictactoe &, int, bool, int, int, int, int);
    int evaluation(game::tictactoe &, bool);
    bool adjacenPlaced(game::tictactoe &, int, int);
    bool checkVisitedBoard(game::tictactoe &);
    int getEvaluation(game::tictactoe &);
    void insertToHash(game::tictactoe &, int);
};


#endif //GAMECARO_COMPUTER_H
