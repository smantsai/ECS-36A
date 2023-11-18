#ifndef PLAY_GAME_H
    #define PLAY_GAME_H

    bool isValidFormat(const int numArgsRead, const int numArgsNeed);
    int getValidInt(int col, int* numArgsRead);
    void display_board(char** board, int row, int col);
    void switch_to_next_player(int *cur_player_turn);
    bool is_between(int value, int lower, int upper);
    bool is_on_board(int out_row, int out_col, int row, int col);
    int find_valid_row(char** board, int row, int out_col);
    bool is_valid_play(int num_args_read, int* out_row, int out_col, char** board, int row, int col, char blank_space);
    void pick_valid_spot_for_play(char** board, int row, int col, char blank_space, int* out_row, int *out_col);
    void current_player_take_turn(char cur_player_piece, char** board, int row, int col, int blank_space, int* latestRow, int* latestCol);
    void play_game(int cur_player_turn, char* player_pieces, char** board, int row, int col, char blank_space, int numWin);
    void announce_game_results(int cur_player_turn, char** board, int latestRow, int latestCol, int row, int col, int numToWin, char playerPiece);


#endif