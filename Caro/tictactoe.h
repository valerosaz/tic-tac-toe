/********************************************************
 * Created by Phuc Le and Hong Trinh
 * Assignment 3
 * Minimax alpha-beta Pruning in Tictactoe game
 * 5 in a row to win
 ********************************************************/
#ifndef GAMECARO_TICTACTOE_H
#define GAMECARO_TICTACTOE_H

#include <iostream>
#include <stdio.h>
#include <string>

namespace game {

    const int B = 15; //length and width of board is 10 x 10
    const int R = 5; // 5 in a row to get a win

    class tictactoe {
    public:
        tictactoe();
        void clearBoard();
        void printBoard();
        bool checkEm(int, int);
        bool victory(int, int);
        bool tie();
        char getValue(int, int);
        void setValue(int, int, char);
        int getCounter();

        char getPlayerSym(){
            return _playerSym;
        }
        void setPlayerSym(char c){
            _playerSym = c;
        }
        char getComSym(){
            return _comSym;
        }
        void setComSym(char c){
            _comSym = c;
        }

        bool fiveInRow(int,int);
        bool fiveInColumn(int,int);
        bool fiveInDiagonal(int,int);
        bool fiveInReverseDiagonal(int,int);

        std::string toString();

    private:
        char _gameBoard[B][B];
        char _playerSym;
        char _comSym;
        int counter;
    };
}


#endif //GAMECARO_TICTACTOE_H
