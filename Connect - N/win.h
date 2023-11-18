#ifndef WIN_H
    #define WIN_H

    bool hasNum(char* board, int row, int col, int numToWin, char playerPiece);
    char* get_column(int column_index, char** board, int row, int col);
    bool someone_won_horizontally(char** board, int playerRow, int row, int col, int numToWin, char playerPiece);
    bool someone_won_vertically(char** board, int playerCol, int row, int col, int numToWin, char playerPiece);
    bool someone_won_on_left_diagonal(char** board, int row, int col, int numToWin, char playerPiece);
    bool someone_won_on_right_diagonal(char** board, int row, int col, int numToWin, char playerPiece);
    bool someone_won_diagonally(char** board, int row, int col, int numToWin, char playerPiece);
    bool someone_won(char** board, int out_row, int out_col, int row, int col, int numToWin, char playerPiece);
    bool tie(char** board, int row, int col);
    bool is_game_over(char** board, int out_row, int out_col, int row, int col, int numToWin, char playerPiece);

#endif