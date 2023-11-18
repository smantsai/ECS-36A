#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "win.h"

/**
 * checks if an array has N number of 1 player's pieces in a row, where N is the amount of pieces to win
 * @param board: an array with pieces in the same row / column
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param numToWin: the amount of pieces in a row needed to win
 * @param playerPiece: the character representing the current player's move
 * @return: true if the array does have N number of pieces in a row, false otherwise
 */
bool hasNum(char* board, int row, int col, int numToWin, char playerPiece) {
    int numInRow = 0;

    for (int i = 0; i < col; i++) {
        if (board[i] == playerPiece) {
            numInRow++;
            if (numInRow >= numToWin) {
                return true;
            }
        } else {
            numInRow = 0;
        }
    }

        numInRow = 0;
        for (int j = 0; j < row; j++) {
            if (board[j] == playerPiece) {
                numInRow++;
                if (numInRow >= numToWin) {
                    return true;
                }
            } else {
                numInRow = 0;
            }
        }

    return numInRow == numToWin;
}

/**
 * makes an array of a single column
 * @param column_index: the column that the player just made a move in
 * @param board: the board that the players will make a move on
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @return: an array of characters
 */
char* get_column(int column_index, char** board, int row, int col){
    char* column = (char*)calloc(row, sizeof(char));
    for(int i = 0; i < row; ++i){
        column[i] = board[i][column_index];
    }
    return column;
}

/**
 * checks if a someone has won with their pieces placed horizontally
 * @param board: the board that the players will make a move on
 * @param playerRow: the row that the player just made a move on
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param numToWin: the # of pieces in a row needed to win
 * @param playerPiece: the character used to represent the player that just made a move
 * @return: true if someone did win
 */
bool someone_won_horizontally(char** board, int playerRow, int row, int col, int numToWin, char playerPiece){
    for(int i = 0; i < col; ++i){
        if(hasNum(board[playerRow], row, col, numToWin, playerPiece)){
            return true;
        }
    }
    return false;
}

/**
 * checks if a someone has won with their pieces placed vertically
 * @param board: the board that the players will make a move on
 * @param playerCol: the column that the player just made a move on
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param numToWin: the # of pieces in a row needed to win
 * @param playerPiece: the character used to represent the player that just made a move
 * @return: true if someone did win
 */
bool someone_won_vertically(char** board, int playerCol, int row, int col, int numToWin, char playerPiece){
    for(int i = 0; i < col; ++i){
        char* column = get_column(playerCol, board, row, col);
        if(hasNum(column, row, col, numToWin, playerPiece)){
            free(column);
            return true;
        }
        free(column);
    }
    return false;
}

/**
 * checks if a someone has won with their pieces placed diagonally, from top left to bottom right
 * @param board: the board that the players will make a move on
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param numToWin: the # of pieces in a row needed to win
 * @param playerPiece: the character used to represent the player that just made a move
 * @return: true if someone did win
 */
bool someone_won_on_left_diagonal(char** board, int row, int col, int numToWin, char playerPiece){
    /* Checking for a win on the main diagonal that looks like this
        top left to bottom right
        X
          X
            X
    */
    for (int i = 0; i <= row - numToWin; i++) {
        for (int j = 0; j <= col - numToWin; j++) {
            bool containsPiece = true;
            for (int x = 0; x < numToWin; x++) {
                if (board[i + x][j + x] != playerPiece) {
                    containsPiece = false;
                    break;
                }
            }
            if (containsPiece == true) { // checks at the end of each diagonal
                return true;
            }
        }
    }

    return false;
}

/**
 * checks if a someone has won with their pieces placed diagonally, from top right to bottom left
 * @param board: the board that the players will make a move on
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param numToWin: the # of pieces in a row needed to win
 * @param playerPiece: the character used to represent the player that just made a move
 * @return: true if someone did win
 */
bool someone_won_on_right_diagonal(char** board, int row, int col, int numToWin, char playerPiece){
    /* Checking for a win on the main diagonal that looks like this
        top right to bottom left
            X
          X
        X
    */
    for (int i = 0; i <= row - numToWin; i++) {
        for (int j = numToWin - 1; j < col; j++) {
            bool containsPiece = true;
            for (int x = 0; x < numToWin; x++) {
                if (board[i + x][j - x] != playerPiece) {
                    containsPiece = false;
                    break;
                }
            }
            if (containsPiece == true) { // checks at the end of each diagonal
                return true;
            }
        }
    }

    return false;
}

/**
 * checks if a someone has won with their pieces placed diagonally, from any direction
 * @param board: the board that the players will make a move on
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param numToWin: the # of pieces in a row needed to win
 * @param playerPiece: the character used to represent the player that just made a move
 * @return: true if someone did win
 */
bool someone_won_diagonally(char** board, int row, int col, int numToWin, char playerPiece){
    return someone_won_on_left_diagonal(board, row, col, numToWin, playerPiece)|| 
    someone_won_on_right_diagonal(board, row, col, numToWin, playerPiece);
}

/**
 * checks if a someone has won with their pieces, from all 3 methods
 * @param board: the board that the players will make a move on
 * @param out_row: the row the player just put their piece in
 * @param out_col: the column the player just put their piece in
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param numToWin: the # of pieces in a row needed to win
 * @param playerPiece: the character used to represent the player that just made a move
 * @return: true if someone did win
 */
bool someone_won(char** board, int out_row, int out_col, int row, int col, int numToWin, char playerPiece){
    return someone_won_horizontally(board, out_row, row, col, numToWin, playerPiece) ||
           someone_won_vertically(board, out_col, row, col, numToWin, playerPiece)|| 
           someone_won_diagonally(board, row, col, numToWin, playerPiece);
}

/**
 * checks if the game ended in a tie
 * @param board: the board that the players made a move on
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @return: true if the game is a tie
 */
bool tie(char** board, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == '*') {
                return false;
            } 
        }
    }
    return true;
}

/**
 * checks if the game is over, from someone winning or a tie
 * @param board: the board that the players will make a move on
 * @param out_row: the row the player just put their piece in
 * @param out_col: the column the player just put their piece in
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param numToWin: the # of pieces in a row needed to win
 * @param playerPiece: the character used to represent the player that just made a move
 * @return: true if the game is over
 */
bool is_game_over(char** board, int out_row, int out_col, int row, int col, int numToWin, char playerPiece){
    return someone_won(board, out_row, out_col, row, col, numToWin, playerPiece) || 
    tie(board, row, col);
}
