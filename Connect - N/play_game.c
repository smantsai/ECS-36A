#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "play_game.h"
#include "win.h"

/**
 * checks the formatting of the user's input
 * @param numsArgsRead: the number of inputs the user put in and was read by the program
 * @param numArgsNeed: the number of inputs the program needs
 * @return: true if the formatting correct, otherwise false
 */
bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
    bool formatIsGood = numArgsRead == numArgsNeed;
    char character;
    do{
        scanf("%c", &character);
            if(!isspace(character)){ 
                formatIsGood = false;
            }
        }while(character != '\n');
    return formatIsGood;
}

/**
 * gets an integer input from the user
 * @param col: the number of columns in the board, used for the prompt
 * @param numArgsRead: the number of inputs the program reads
 * @return: an integer that is valid for the program
 */
int getValidInt(int col, int* numArgsRead){
    int num;
    const int numArgsNeeded = 1;
    do{
        printf("Enter a column between 0 and %d to play in: ", col - 1);
        *numArgsRead = scanf(" %d", &num);
    }while(!isValidFormat(*numArgsRead, numArgsNeeded));

  return num;
}

/**
 * prints out each piece of the board
 * @param board: the board that is being printed
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @return: nothing because the function is void
 */
void display_board(char** board, int row, int col) {
    int k = 0;
    for (int i = row - 1; i >= 0; i--) {
        printf("%d ", i);
        for (int j = 0; j < col; j++) {
            printf("%c ", board[k][j]);
        }
        k++;
        printf("\n");
    }

    printf("  ");
    for (int x = 0; x < col; x++) {
        printf("%d ", x);
    }
    printf("\n");
}

/**
 * switches the player that is making a turn
 * @param cur_player_turn: the last player that made a turn
 * @return: nothing because function is void
 */
void switch_to_next_player(int *cur_player_turn){
    if(*cur_player_turn == 0){
        *cur_player_turn = 1;
    }else{
        *cur_player_turn = 0;
    }

}

/**
 * checks if a value is between a lower and upper value
 * @param value: the user's number to be checked
 * @param lower: the lower bound
 * @param upper: the upper bound
 * @return: true if the value is between the lower & upper bound
 */
bool is_between(int value, int lower, int upper){
    return value >= lower && value <= upper;
}

/**
 * checks if the user's input is on the board
 * @param out_row: the row that the piece will be placed in
 * @param out_col: the column that the piece will be placed in (the user's choice)
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @return: true if the piece is in the board, false if not
 */
bool is_on_board(int out_row, int out_col, int row, int col){
    return is_between(out_row, 0, row - 1) && is_between(out_col, 0, col - 1);
}

/**
 * finds out which row the piece will be placed in
 * @param board: the board that will be modified, used to check which spot is free
 * @param row: the # of rows in the board
 * @param out_col: the column that user wants to put a piece in
 * @return: an int that contains which row the piece will be in, -1 if the entire column is full
 */
int find_valid_row(char** board, int row, int out_col) {
    for (int i = row - 1; i >= 0; i--) {
        if (board[i][out_col] == '*') {
            return i;
        }
    }

    return -1;
}

/**
 * checks if the user's move is valid or not
 * @param numsArgsRead: the number of inputs the user put in and was read by the program
 * @param out_row: the row the piece will be placed in
 * @param out_col: the column the piece will be placed in
 * @param board: the board that the players make a move on
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param blank_space: the character that is used to represent a free space on the board
 * @return: true if the piece can be placed there, false if not
 */
bool is_valid_play(int num_args_read, int* out_row, int out_col, char** board, int row, int col, char blank_space){
    *out_row = find_valid_row(board, row, out_col);
    
    return is_on_board(*out_row, out_col, row, col) && board[*out_row][out_col] == blank_space;
}

/**
 * lets the user pick a column to place their piece in
 * @param board: the board that the players make a move on
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param blank_space: the character that is used to represent a free space on the board
 * @param out_row: the row the piece will be placed in
 * @param out_col: the column the piece will be placed in
 * @return: nothing because function is void
 */
void pick_valid_spot_for_play(char** board, int row, int col, char blank_space, int* out_row, int *out_col){
    int num_args_read;
    do{
        *out_col = getValidInt(col, &num_args_read);
    }while(!is_valid_play(num_args_read, out_row, *out_col, board, row, col, blank_space));
}

/**
 * allows the current player to make a turn / place their piece
 * @param cur_player_piece: the piece that represents the current player's move / turn
 * @param board: the board that the players will make a move on
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param blank_space: the character that is used to represent a free space on the board
 * @param latestRow: the row the piece will be placed in
 * @param latestCol: the column the piece will be placed in
 * @return: nothing because function is void
 */
void current_player_take_turn(char cur_player_piece, char** board, int row, int col, int blank_space, int* latestRow, int* latestCol){
    int playMoveCol;
    int playMoveRow;
    display_board(board, row, col);
    pick_valid_spot_for_play(board, row, col, blank_space, &playMoveRow, &playMoveCol);
    board[playMoveRow][playMoveCol] = cur_player_piece;
    *latestRow = playMoveRow;
    *latestCol = playMoveCol;
}

/**
 * says if the game was won by a player or a tie
 * @param cur_player_turn: the last player who made a move
 * @param board: the board that the players will make a move on
 * @param latestRow: the row the piece will be placed in
 * @param latestCol: the column the piece will be placed in
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param numToWin: the # of pieces in a row to win
 * @param playerPiece: the character that represents the player who just made a move
 * @return: nothing because function is void
 */
void announce_game_results(int cur_player_turn, char** board, int latestRow, int latestCol, int row, int col, int numToWin, char playerPiece){
    if(someone_won(board, latestRow, latestCol, row, col, numToWin, playerPiece)){
        display_board(board, row, col);
        printf("Player %d Won!\n", cur_player_turn + 1);
    } else if (tie(board, row, col)) {     // else if tie game, else do nothing
        display_board(board, row, col);
        printf("Tie game!\n");
    }
}

/**
 * starts the game
 * @param cur_player_turn: the last player who made a move
 * @param player_pieces: an array with characters that represent each player
 * @param board: the board that the players will make a move on
 * @param row: the # of rows in the board
 * @param col: the # of columns in the board
 * @param blank_space: the character that represents a free space
 * @param numWin: the # of pieces in a row to win
 * @return: nothing because function is void
 */
void play_game(int cur_player_turn, char* player_pieces, char** board, int row, int col, char blank_space, int numWin){
    do{
        int latestRow = -1;
        int latestCol = -1;
        current_player_take_turn(player_pieces[cur_player_turn], board, row, col, blank_space, &latestRow, &latestCol);
        if(is_game_over(board, latestRow, latestCol, row, col, numWin, player_pieces[cur_player_turn])){
            announce_game_results(cur_player_turn, board, latestRow, latestCol, row, col, numWin, player_pieces[cur_player_turn]);
            break;
        }
        switch_to_next_player(&cur_player_turn);
    }while(true);

}