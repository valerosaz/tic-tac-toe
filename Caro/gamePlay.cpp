/********************************************************
 * Created by Phuc Le and Hong Trinh
 * Assignment 3
 * Minimax alpha-beta Pruning in Tictactoe game
 * 5 in a row to win
 ********************************************************/
/*********************************************************
 *Gameplay for both computer and player with instructions
 ********************************************************/
#include "gamePlay.h"
#include <iostream>
#include "gamePlay.h"
#include "tictactoe.h"
#include "Computer.h"
#include <vector>

using namespace game;

gamePlay::gamePlay() {// create a new game in case player want to play new game
    Tictactoe.clearBoard();
}

void gamePlay::playGround() {// where to play game, plus with instruction
    Tictactoe.clearBoard();
    Computer computer;
    bool flag = true;
    int current  = 1;// current statement (~player)
    int x = -1, y = -1;
    std::vector<int> vec;
    int selection;

    std::cout << "Please choose your sides, X or O ?" << std::endl;// instruction to pick side (with given symbols)
    std::cout << "1 => X" << std::endl;
    std::cout << "2 => O" << std::endl;
    std::cin >> selection;

    while (selection != 1 && selection != 2){// decide player selection. If pick this, the other symbol will be picked by computer
        std::cout << "Incorrect choice! Enter your choice again. "<<std::endl;
        std::cin >> selection;
        if(selection == 1 || selection == 2){
            break;
        }
    }

    if (selection == 1){
        Tictactoe.setComSym('O');
        Tictactoe.setPlayerSym('X');
    }
    else{
        Tictactoe.setComSym('X');
        Tictactoe.setPlayerSym('O');
    }

    // in case player want to go first
    std::cout << "Player as " << Tictactoe.getPlayerSym() << std::endl;
    std::cout << "Do you want to go first ? Yes or No ?" << std::endl;
    std::cout << "Type y for yes and n for no!" << std::endl;
    char playerGoFirst;
    std::cin >> playerGoFirst;

    if (playerGoFirst == 'Y' || playerGoFirst == 'y'){
        current = 1;// if player goes first, current = 1 ~ player, 2 ~ computer and reverse.
        std::cout << "OK. Player go first!"<< std::endl;
    } else {
        current = 2;
        std::cout << "OK. Computer go first!"<< std::endl;
    }

    Tictactoe.printBoard();
    while(flag){
        std::cout << std::endl;
        if (current == 1){ //get player move
            std::cout <<"Player's turn. (" << getCurrentSym(current)<<" )"<<std::endl;
            std::cout << "Enter X coordinate of your move: ";
            std::cin >> y;
            std::cout << "Enter Y coordinate of your move: ";
            std::cin >> x;
        }
        else{
            vec = computer.nextmoveAlBe(Tictactoe);
            x = vec[0];
            y = vec[1];
        }

        if(!Tictactoe.checkEm(x,y)){// checking for the legal movement in gameplay
            std::cout << std::endl << "Invalid movement, please make the move again!!!" << std::endl;
            continue;// in case there are no illegal movements
        }
        else{// Update the board with legal movements
            Tictactoe.setValue(x,y,getCurrentSym(current));
            Tictactoe.printBoard();
            if(current == 1){
                std::cout << "Player's move is : (" << y << ", " << x<<") "<<std::endl;
            }
            else{
                std::cout << "Computer's move is : (" << y << ", " << x<<") "<<std::endl;
            }
        }

        if(Tictactoe.victory(x,y)){// check if the game is over or not ??
            Tictactoe.printBoard();
            if (current == 1) {
                std::cout << "CONGRATULATIONS! PLAYER WON THIS GAME!"<< std::endl;
            }else {
                std::cout << "PLAYER LOSEEEEEEEEEEE!!!"<< std::endl;
            }
            break;
        }else if (Tictactoe.tie()){
            Tictactoe.printBoard();
            std::cout << "Draw game!"<< std::endl;
            break;
        }else{ // if the game is not over, change current player between the player and the computer
            current = 3 - current;// basically, change state of player and computer in order of turn
        }
    }
}


char gamePlay::getCurrentSym(int current){// current symbol of player and computer in the game
    if (current == 1){
        return Tictactoe.getPlayerSym();
    }else{
        return Tictactoe.getComSym();
    }
}

void gamePlay::runGame() {// start the game
    bool flag = true;
    char x;
    while (flag) {
        playGround();
        std::cout << "Do you want to play another game? y/n" << std::endl;
        std::cin >> x;
        if (x == 'N' || x == 'n') {
            std::cout << "Thanks for playing the game! See you next time! :D " << std::endl;
            flag = false;
        } else {
            std::cout << "------------------------------------------------------" << std::endl;
        }
    }
}