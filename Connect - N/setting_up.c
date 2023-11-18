#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "setting_up.h"

/**
 * creates and initalizes a board for the game
 * @param row: the number of rows of the user's choosing
 * @param col: the number of columns of the user's choosing
 * @param blank_space: the character representing a free space
 * @return: a 2D array with empty spaces
 */
char** create_board(int row, int col, char blank_space){
    /*
        create an empty row X col board filled with blank spaces
    */

    char** board = (char**)calloc(row, sizeof(char*));
    for(int i = 0; i < row; ++i){
        board[i] = (char*)calloc(col, sizeof(char));
        for(int j = 0; j < col; ++j){
            board[i][j] = blank_space;
         }
    }
    return board;
}

/**
 * sets up the game board
 * @param row: the number of rows of the user's choosing
 * @param col: the number of columns of the user's choosing
 * @param blank_space: the character representing a free space
 * @param out_starting_player: an integer representing the first player that will go
 * @param out_board: the board that the program will use to play the game
 * @return: nothing b/c function is a boolean
 */
void setup_game(int row, int col, char blank_space,
                int *out_starting_player, char** *out_board){
    *out_board = create_board(row, col, blank_space);
    *out_starting_player = 0;
}