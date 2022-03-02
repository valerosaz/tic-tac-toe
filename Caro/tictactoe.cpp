/********************************************************
 * Created by Phuc Le and Hong Trinh
 * Assignment 3
 * Minimax alpha-beta Pruning in Tictactoe game
 * 5 in a row to win
 ********************************************************/
/********************************************************
 *Initializing and drawing the board (for play console),
 * defining and checking game status (win, draw, lose)
 ********************************************************/

#include "tictactoe.h"
#include <iostream>
#include <string>

using namespace game;

void tictactoe::clearBoard() {// make a new board for a new game
    for (int i = 0; i < B; i++){
        for(int j = 0; j < B; j++){
            _gameBoard[i][j] = '_';
        }
    }
    counter = 0;
}

tictactoe::tictactoe() {// Default constructor / create a new board
    clearBoard();
}



void tictactoe::printBoard(){// print out the board

    std::cout <<"   ";
    for (int i = 0 ; i < B; i++){
        std::string s = i < 10?"  ":" ";
        std::cout << i <<s;
    }
    std::cout <<std::endl;
    for (int i = 0; i < B; i++){
        std::string s = i < 10?"  ":" ";
        std::cout << i<<s;
        for (int j = 0; j < B; j++){
            std::cout << _gameBoard[i][j]<<"  ";
        }
        std::cout <<i;
        std::cout <<std::endl<<std::endl;
    }
    std::cout <<"   ";
    for (int i = 0 ; i < B; i++){
        std::string s = i < 10?"  ":" ";
        std::cout << i <<s;
    }
    std::cout <<std::endl;
}

bool tictactoe::checkEm(int x, int y) {//check that the position x and y are valid or not ?
    if (x >= 0 && x <= B-1 && y >= 0 && y <= B-1 && _gameBoard[x][y] == '_'){
        return true;
    }
    return false;
}

void tictactoe::setValue(int x, int y, char c) {
    _gameBoard[x][y] = c;
    if (c == '_'){
        counter --;
    }
    else{
        counter ++;
    }
    return;
}

bool tictactoe::victory(int x, int y) {// if the game play meet one of these 4 condition, the game is over with a winner
    return fiveInRow(x,y) || fiveInColumn(x,y) || fiveInDiagonal(x,y) || fiveInReverseDiagonal(x,y);
}


bool tictactoe::fiveInRow(int x, int y) {//wining with 5 same symbols in a row
    int temporary = 1;
    int i = 1;
    while (x - i >= 0 && _gameBoard[x - i][y] == _gameBoard[x][y]){
        temporary ++;
        i ++;
    }
    i = 1;
    while (x + i >= 0 && _gameBoard[x + i][y] == _gameBoard[x][y]) {
        temporary++;
        i++;
    }
    return (temporary >= R);
}

bool tictactoe::fiveInColumn(int x, int y) {//wining with 5 same symbols in a column
    int temporary = 1;
    int i = 1;
    while (y - i >= 0 && _gameBoard[x][y - i] == _gameBoard[x][y]){
        temporary ++;
        i ++;
    }
    i = 1;
    while (y + i >= 0 && _gameBoard[x][y + i] == _gameBoard[x][y]) {
        temporary++;
        i++;
    }
    return (temporary >= R);
}

bool tictactoe::fiveInDiagonal(int x, int y) {//wining with 5 same symbols in Diagonal dimension
    int temporary = 1;
    int i = 1;
    while (x - i && y - i >= 0 && _gameBoard[x - i][y - i] == _gameBoard[x][y]){
        temporary ++;
        i ++;
    }
    i = 1;
    while (x + i && y + i >= 0 && _gameBoard[x + i][y + i] == _gameBoard[x][y]) {
        temporary++;
        i++;
    }
    return (temporary >= R);
}

bool tictactoe::fiveInReverseDiagonal(int x, int y) {//wining with 5 same symbols in Diagonal dimension
    int temporary = 1;
    int i = 1;
    while (x - i && y + i >= 0 && _gameBoard[x - i][y + i] == _gameBoard[x][y]){
        temporary ++;
        i ++;
    }
    i = 1;
    while (x + i && y - i >= 0 && _gameBoard[x + i][y - i] == _gameBoard[x][y]) {
        temporary++;
        i++;
    }
    return (temporary >= R);
}



bool tictactoe::tie() {// check if the game is a draw game or not ?
    if(counter == B*B){// no space to make any addition moves ~ calculation of area of a square
        return true;
    }
    return false;
}

char tictactoe::getValue(int i, int j) {//return the value of the current position (i,j)
    return _gameBoard[i][j];
}

int tictactoe::getCounter() {//return number of the position with placed move of X or O
    return counter;
}

std::string tictactoe::toString() {
    std::string str = "";
    for (int i = 0; i < B; i++){
        for(int j = 0; j < B; j++){
            str += getValue(i,j);
        }
    }
    return str;
}



