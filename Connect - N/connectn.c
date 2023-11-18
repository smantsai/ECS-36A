/* This program allows a user to make a game, connect-n, with their own parameters*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "setting_up.h"
#include "play_game.h"
#include "win.h"

/**
 * gets input from the command line
 * @param argc: the number of arguments in the command line
 * @param argv: an array with the input
 * @param row: a pointer that will contain the # of rows in the game
 * @param col: a pointer that will contain the # of columns in the game
 * @param numPiecesToWin: a pointer that will contain the number of pieces in order to win
 * @return: nothing b/c function is a boolean
 */
void get_dimesions_from_command_line(int argc, char** argv, int *row, int *col, int *numPiecesToWin){
    if(argc < 4){
        printf("Not enough arguments entered\n");
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
        exit(0);
    } else if (argc > 4) {
        printf("Too many arguments entered\n");
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
        exit(0);
    }
    int num_args_read = sscanf(argv[1], " %d", row);
    num_args_read += sscanf(argv[2], " %d", col);
    num_args_read += sscanf(argv[3], " %d", numPiecesToWin);

    if(num_args_read != 3){
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
        exit(0);
    }

    if(*row < 1 || *col < 1 || *numPiecesToWin < 1){
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
        exit(0);
    }

}


int main(int argc, char** argv){
    const char blank_space = '*';
    int cur_player_turn;
    char* player_pieces = (char*)calloc(2, sizeof(char));
    char** board;
    int row;
    int col;
    int numWinningPieces;

    player_pieces[0] = 'X';
    player_pieces[1] = 'O';

    get_dimesions_from_command_line(argc, argv, &row, &col, &numWinningPieces);

    setup_game(row, col, blank_space,
                &cur_player_turn, &board);
    play_game(cur_player_turn, player_pieces, board, row, col, blank_space, numWinningPieces);
    return 0;
}