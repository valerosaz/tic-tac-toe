/******************************************************
 * Created by Phuc Le and Hong Trinh
 * Assignment 3
 * Minimax alpha-beta Pruning in Tictactoe game
 * 5 in a row to win
 ******************************************************/
/******************************************************
 * Declaring and implementing the Minimax algorithm
 * plus evaluating the best move for computer gameplay.
 ******************************************************/

#include "Computer.h"
#include "tictactoe.h"
#include <iostream>
#include <vector>

using namespace game;

//find next move with the help of alpha-beta
//want to maximize the evaluation function. It's good for the computer
std::vector<int> Computer::nextmoveAlBe(tictactoe & board) {
    std::vector<int> vec = {0,0};
    int M = INT_MIN, x= -1, y= -1;
    for(int i = 0; i <= B-1;i++){
        for(int j=0;j<=B-1;j++){
            if(board.getValue(i,j) == '_' && adjacenPlaced(board,i,j)){
                int temp = minimaxAlBe(board,2, true,INT_MIN,INT_MAX,i,j);
                if (M < temp){
                    M = temp;
                    x = i;
                    y = j;
                }

            }
        }
    }
    if (x == -1 && y == -1){
        x = B/2;
        y = B/2;
    }
    vec[0] = x;
    vec[1] = y;
    return vec;
}


//minimaxAlphaBeta algorithm with alpha-beta to help determine the next move for the computer
//Use evaluation function with depth here.
//higher score is good for computer, lower score is good for player
int Computer::minimaxAlBe(tictactoe & board, int depth, bool isMax, int al, int be, int x, int y) {
    char im = isMax ? board.getComSym() : board.getPlayerSym();
    board.setValue(x,y,im);
    if(board.victory(x,y)){
        board.setValue(x,y,'_');
        if(isMax) {//computer wins
            return INT_MAX;//chose the way that computer win
        }else{
            return INT_MIN;//player wins. Need to minimize score so computer will not choose this path
        }
    }else if (board.tie()){
        board.setValue(x,y,'_');
        return 0;
    }
    if (depth == 0){
        int value = 0;
        if(checkVisitedBoard(board) == true){
            value = getEvaluation(board); //evaluation of board was already stored
        }else{
            value = evaluation(board,isMax);
            insertToHash(board,value);
        }
    board.setValue(x,y,'_');
    return value;
    }
    //save the X positions of available cells into firstCoord, Y positions of available cells into secondCoord
    std::vector<int> firstCoord;// store the value of x axis
    std::vector<int> secondCoord;// store the value of y axis
    for (int i = 0; i < B; i++){
        for (int j = 0; j<B; j++){
            if (board.getValue(i,j) == '_' && adjacenPlaced(board, i, j)){
                firstCoord.push_back(i);
                secondCoord.push_back(j);
            }
        }
    }
    int length = (int) firstCoord.size();
    if(isMax == true){// try to minimize because now is player's turn
        int m = INT_MAX;
        for(int i=0; i< length;i++){
            int temp = minimaxAlBe(board,depth - 1, false,al,be,firstCoord[i],secondCoord[i]);
            if(m>temp){
                m = temp;
            }
            if(be > m){
                be = m;
            }
            if(al >=be){
                break;
            }
        }
        board.setValue(x,y,'_');
        return m;
    } else{//try to maximize
        int M = INT_MIN;
        for (int i = 0; i < length; i++){
            int temp = minimaxAlBe(board, depth - 1, true, al, be, firstCoord[i], secondCoord[i]);
            if (M < temp){
                M = temp;
            }
            if (al < M){
                al = M;
            }
            if (al >= be){
                break;
            }
        }
        board.setValue(x,y,'_');
        return M;
    }
}

int Computer::evaluation(tictactoe &board, bool) {//if isMax is true, computer make the move at (x,y)
    int sum = 0;
    std::vector<int> computerPattern(R+1,0);
    std::vector<int> playerPattern(R+1,0);

    for (int  i = 0 ; i < B; i++){
        for (int j = 0; j < B ; j++){
            if (board.getValue(i,j) != '_'){
                //count patterns in columns
                char val = board.getValue(i,j);
                bool needMax = val == board.getComSym();

                int sameSym = 1; // count same symbols in columns
                int k = 1;
                while (i- k >= 0 && board.getValue(i-k, j)  == val){
                    sameSym++;
                    k++;
                }
                //consider value at i - k later to see if it's blocked or not
                int l = 1;
                while (i + l <= B-1 && board.getValue(i+l, j) == val){
                    sameSym++;
                    l++;
                }

                if (sameSym >= R){
                    if (needMax) computerPattern[R]++;
                    else playerPattern[R]++;
                }else if (sameSym == R - 1 && (board.checkEm(i-k,j) || board.checkEm(i+l,j))){
                    if (needMax) computerPattern[R-1]++;
                    else playerPattern[R-1]++;
                }else if (sameSym == R - 2 && (board.checkEm(i-k,j) || board.checkEm(i+l,j))){
                    if (needMax) computerPattern[R-2]++;
                    else playerPattern[R-2]++;
                }else if (sameSym == R - 2 && (board.checkEm(i-k,j) && board.checkEm(i+l,j))){
                    if (needMax) computerPattern[R-3]++;
                    else playerPattern[R-3]++;
                }else if (sameSym == R - 3 && board.checkEm(i-k,j) && board.checkEm(i+l,j)){
                    if (needMax) computerPattern[R-4]++;
                    else playerPattern[R-4]++;
                }


                //-------------------------------------------------------------------------------
                sameSym = 1; // count same symbols in rows
                k = 1;
                while (j - k >= 0 && board.getValue(i, j-k)  == val){
                    sameSym++;
                    k++;
                }

                //consider value at i - k later to see if it's blocked or not
                l = 1;
                while (j + l <= B-1 && board.getValue(i, j+l) == val){
                    sameSym++;
                    l++;
                }

                if (sameSym >= R){
                    if (needMax) computerPattern[R]++;
                    else playerPattern[R]++;
                }else if (sameSym == R - 1 && (board.checkEm(i,j-k) || board.checkEm(i,j+l))){
                    if (needMax) computerPattern[R-1]++;
                    else playerPattern[R-1]++;
                }else if (sameSym == R - 2 && (board.checkEm(i,j-k) || board.checkEm(i,j+l))){
                    if (needMax) computerPattern[R-2]++;
                    else playerPattern[R-2]++;
                }else if (sameSym == R - 2 && (board.checkEm(i,j-k) && board.checkEm(i,j+l))){
                    if (needMax) computerPattern[R-3]++;
                    else playerPattern[R-3]++;
                }else if (sameSym == R - 3 && board.checkEm(i,j-k) && board.checkEm(i,j+l)){
                    if (needMax) computerPattern[R-4]++;
                    else playerPattern[R-4]++;
                }

                //--------------------------------------------------------------

                sameSym = 1;// count same symbols in main diagnol
                k = 1;
                while (i - k >= 0 && j - k >= 0 && board.getValue(i-k, j- k)  == val){
                    sameSym++;
                    k++;
                }


                //consider value at i - k later to see if it's blocked or not
                l = 1;
                while (i + l <= B-1 && j + l <= B-1 && board.getValue(i+l, j+l ) == val){
                    sameSym++;
                    l++;
                }

                if (sameSym >= R){
                    if (needMax) computerPattern[R]++;
                    else playerPattern[R]++;
                }else if (sameSym == R - 1 && (board.checkEm(i-k,j-k) || board.checkEm(i+l,j+l))){
                    if (needMax) computerPattern[R-1]++;
                    else playerPattern[R-1]++;
                }else if (sameSym == R - 2 && (board.checkEm(i-k,j-k) || board.checkEm(i+l,j+l))){
                    if (needMax) computerPattern[R-2]++;
                    else playerPattern[R-2]++;
                }else if (sameSym == R - 2 && (board.checkEm(i-k,j-k) && board.checkEm(i+l,j+l))){
                    if (needMax) computerPattern[R-3]++;
                    else playerPattern[R-3]++;
                }else if (sameSym == R - 3 && board.checkEm(i-k,j-k) && board.checkEm(i+l,j+l)){
                    if (needMax) computerPattern[R-4]++;
                    else playerPattern[R-4]++;
                }



                //-----------------------------------------------------------------------


                sameSym = 1;// count same symbols in reverse diagnols
                k = 1;
                while (i - k >= 0 && j + k <= B-1 && board.getValue(i-k, j+ k)  == val){
                    sameSym++;
                    k++;
                }


                //consider value at i - k later to see if it's blocked or not
                l = 1;
                while (i + l <= B-1 && j - l >= 0 && board.getValue(i+l, j-l ) == val){
                    sameSym++;
                    l++;
                }

                if (sameSym >= R){
                    if (needMax) computerPattern[R]++;
                    else playerPattern[R]++;
                }else if (sameSym == R - 1 && (board.checkEm(i-k,j+k) || board.checkEm(i+l,j-l))){
                    if (needMax) computerPattern[R-1]++;
                    else playerPattern[R-1]++;
                }else if (sameSym == R - 2 && (board.checkEm(i-k,j+k) || board.checkEm(i+l,j-l))){
                    if (needMax) computerPattern[R-2]++;
                    else playerPattern[R-2]++;
                }else if (sameSym == R - 2 && (board.checkEm(i-k,j+k) && board.checkEm(i+l,j-l))){
                    if (needMax) computerPattern[R-3]++;
                    else playerPattern[R-3]++;
                }else if (sameSym == R - 3 && board.checkEm(i-k,j+k) && board.checkEm(i+l,j-l)){
                    if (needMax) computerPattern[R-4]++;
                    else playerPattern[R-4]++;
                }


            }
        }
    }
    if (computerPattern[R] > 0) return INT_MAX;
    if (playerPattern[R] > 0) return INT_MIN;
    int x = 1;
    sum += computerPattern[1];
    sum -= playerPattern[1]*5;
    for (int i = 2 ; i < R ; i++){
        x *= 100;
        sum += computerPattern[i] * x;
        sum -= playerPattern[i] * x * 10;
    }
    return sum;
}

bool Computer::adjacenPlaced(tictactoe &board, int x, int y) {
    bool value = false;
    if (board.getValue(x,y) != '_') return false;
    std::vector<std::vector<int>> adjacent = {{-1,-1},{-1,0}, {-1,1},{0,1},{0,-1},{1,-1},{1,0},{1,1}};
    for (auto ad:adjacent){
        if (x+ad[0] >=0 && y+ad[1]>=0 && x+ad[0] <= B-1 && y + ad[1] <= B-1){
            value = value || (board.getValue(x+ad[0],y+ad[1]) != '_');
        }
    }
    return value;
}

//check if the evaluation function of a particular board is already in the memory or not
bool Computer::checkVisitedBoard(tictactoe &board) {
    std::string s = board.toString();
    if (hashmap.find(s) != hashmap.end()){
        return true;
    }
    return false;
}

//if the evaluation function of a board is already in the memory, just need to take it out.
// this will save time computing the evaluation function of the board.
int Computer::getEvaluation(tictactoe &board) {
    if (checkVisitedBoard(board)){
        return hashmap[board.toString()];
    }
    return -1;
}

//insert values to hash map
void Computer::insertToHash(tictactoe &board, int eval) {
    std::string s = board.toString();
    hashmap[s] = eval;
    return;
}
