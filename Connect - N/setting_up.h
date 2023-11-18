#ifndef SETTING_UP_H
    #define SETTING_UP_H    

    char** create_board(int row, int col, char blank_space);

    void setup_game(int row, int col, char blank_space,
                int *out_starting_player, char** *out_board);

#endif