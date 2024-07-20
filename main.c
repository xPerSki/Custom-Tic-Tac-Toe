#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define BOARD_ROWS 3
#define BOARD_COLUMNS 3

#define MAX_LENGTH 8  // Should be the length of the longest PLAYER string
#define PLAYER1 "USER"
#define PLAYER2 "COMPUTER"

#define EMPTY_SIGN '-'
#define PLAYER1_SIGN 'O'
#define PLAYER2_SIGN 'X'


char search_for_sign(char entity[MAX_LENGTH]) {
    return (strcmp(entity, PLAYER1) == 0) ? PLAYER1_SIGN : PLAYER2_SIGN;
}

void make_move(char entity[MAX_LENGTH], char board_arr[BOARD_ROWS][BOARD_COLUMNS], int x, int y) {
    // If USER makes a move, his number on the board will be 1
    char sign = search_for_sign(entity);
    board_arr[x][y] = sign;
}

void show_board(char board_arr[BOARD_ROWS][BOARD_COLUMNS]) {
    int i, j;
    for (i = 0; i < BOARD_ROWS; i++) {
        for (j = 0; j < BOARD_COLUMNS; j++) {
                printf("%c ", board_arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void end_game(bool playing,  bool bot_move, char winner[MAX_LENGTH]) {
    playing = false;
    bot_move = false;
    if (strcmp(winner, "TIE") == 0) {
        printf("That's a Tie!\n");
        exit(0);
    }
    else {
        printf("%s wins!\n", winner);
        exit(0);
    }
}

bool check_empty_field(char board_arr[BOARD_ROWS][BOARD_COLUMNS], int x, int y) {
    return (board_arr[x][y] == EMPTY_SIGN);
}

bool check_win_horizontally(char board_arr[BOARD_ROWS][BOARD_COLUMNS], char entity[MAX_LENGTH], int column) {
    char search_sign = search_for_sign(entity);

    for (int i = 0; i < BOARD_COLUMNS; i++) {
        if (board_arr[i][column] != search_sign) {
            return false;
        }
    }
    return true;
}

bool check_win_vertically(char board_arr[BOARD_ROWS][BOARD_COLUMNS], char entity[MAX_LENGTH], int row) {
    char search_sign = search_for_sign(entity);

    for (int i = 0; i < BOARD_ROWS; i++) {
        if (board_arr[row][i] != search_sign) {
            return false;
        }
    }
    return true;
}

bool check_win_l_axis(char board_arr[BOARD_ROWS][BOARD_COLUMNS], char entity[MAX_LENGTH]) {
    char search_sign = search_for_sign(entity);
    int row = 0;

    for (int col = 0; col < BOARD_COLUMNS; col++) {
        if (board_arr[row][col] != search_sign) {
            return false;
        }
        if (row < BOARD_ROWS - 1) {
            row++;
        }
    }
    return true;
}

bool check_win_r_axis(char board_arr[BOARD_ROWS][BOARD_COLUMNS],  char entity[MAX_LENGTH]) {
    char search_sign = search_for_sign(entity);
    int col = BOARD_COLUMNS - 1;

    for (int row = 0; row < BOARD_ROWS; row++) {
        if (board_arr[row][col] != search_sign) {
            return false;
        }
        if (col > 0) {
            col--;
        }
    }
    return true;
}

bool check_win_diagonally(char board_arr[BOARD_ROWS][BOARD_COLUMNS], char entity[MAX_LENGTH]) {
    return (check_win_l_axis(board_arr, entity) == true || check_win_r_axis(board_arr, entity) == true);
}

bool check_win(char board_arr[BOARD_ROWS][BOARD_COLUMNS], char entity[MAX_LENGTH], int row, int column) {
    return (check_win_horizontally(board_arr, entity, column) == true \
    || check_win_vertically(board_arr, entity, row) == true) \
    || check_win_diagonally(board_arr, entity);
}


int main() {

    // Initialize board and print it
    char board[BOARD_ROWS][BOARD_COLUMNS];
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLUMNS; j++) {
            board[i][j] = EMPTY_SIGN;
        }
    }

    show_board(board);

    bool playing = true;
    bool bot_can_move = true;
    int moves = 0;

    while (playing) {

        // Allow user to make a move
        bool correctly_typed = false;

        int user_row;
        int user_col;

        while (!correctly_typed) {

            printf("Enter row:");
            scanf("%d", &user_row);

            printf("Enter column:");
            scanf("%d", &user_col);

            user_row--;
            user_col--;

            if (check_empty_field(board, user_row, user_col)) {
                correctly_typed = true;

                // User makes move
                make_move(PLAYER1, board, user_row, user_col);
                moves++;

                // No empty fields
                if (moves >= BOARD_ROWS * BOARD_COLUMNS) {
                    end_game(playing, bot_can_move, "TIE");
                }

                // Check if User won
                if (check_win(board, PLAYER1, user_row, user_col)) {
                    show_board(board);
                    end_game(playing, bot_can_move, PLAYER1);
                }
            }

            else {
                printf("This field is already taken! Try another one.\n");
            }
        }

        // Computer makes move
        srand(time(0));
        while (bot_can_move) {

            int r_computer_row = rand() % BOARD_ROWS;
            int r_computer_column = rand() % BOARD_COLUMNS;

            if (check_empty_field(board, r_computer_row, r_computer_column)) {
                make_move(PLAYER2, board, r_computer_row, r_computer_column);
                moves++;

                // Show new board
                show_board(board);

                // No empty fields
                if (moves >= BOARD_ROWS * BOARD_COLUMNS) {
                    end_game(playing, bot_can_move, "TIE");
                }

                if (check_win(board, PLAYER2, r_computer_row, r_computer_column)) {
                    end_game(playing, bot_can_move, PLAYER2);
                }

                break;
            }
        }
    }

    return 0;
}
