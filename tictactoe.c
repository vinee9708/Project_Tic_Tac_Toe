/*
 * Tic-Tac-Toe - Two Player Console Game
 * FOCP-I (C Programming) Mini Project
 *
 * Concepts used: 2D arrays, functions, loops, conditional statements,
 *                switch, strings, input validation
 *
 * Compile: gcc -Wall tictactoe.c -o tictactoe
 * Run:     ./tictactoe
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3
#define NAME_LEN 30

/* ---------- Function prototypes ---------- */
void showMenu(void);
void showInstructions(void);
void initBoard(char board[SIZE][SIZE]);
void displayBoard(char board[SIZE][SIZE]);
int  readNumber(const char *prompt, int low, int high);
void readName(const char *prompt, char name[]);
int  makeMove(char board[SIZE][SIZE], int position, char symbol);
int  checkWinner(char board[SIZE][SIZE], char symbol);
int  isDraw(char board[SIZE][SIZE]);
void playGame(char name1[], char name2[], int scores[]);
void showScores(char name1[], char name2[], int scores[]);

/* ---------- main: menu-driven loop ---------- */
int main(void)
{
    char name1[NAME_LEN] = "Player 1";
    char name2[NAME_LEN] = "Player 2";
    int scores[3] = {0, 0, 0};   /* [0] = P1 wins, [1] = P2 wins, [2] = draws */
    int choice;

    printf("=====================================\n");
    printf("      WELCOME TO TIC-TAC-TOE!\n");
    printf("=====================================\n");

    do {
        showMenu();
        choice = readNumber("Enter your choice (1-5): ", 1, 5);

        switch (choice) {
            case 1:
                playGame(name1, name2, scores);
                break;
            case 2:
                readName("Enter name for Player 1 (X): ", name1);
                readName("Enter name for Player 2 (O): ", name2);
                printf("Names saved: %s (X) vs %s (O)\n", name1, name2);
                break;
            case 3:
                showScores(name1, name2, scores);
                break;
            case 4:
                showInstructions();
                break;
            case 5:
                printf("\nThanks for playing. Goodbye!\n");
                break;
        }
    } while (choice != 5);

    return 0;
}

/* Prints the main menu */
void showMenu(void)
{
    printf("\n------------- MAIN MENU -------------\n");
    printf("1. Play Game\n");
    printf("2. Set Player Names\n");
    printf("3. View Scoreboard\n");
    printf("4. How to Play\n");
    printf("5. Exit\n");
    printf("-------------------------------------\n");
}

/* Prints the game rules */
void showInstructions(void)
{
    printf("\n--------------- HOW TO PLAY ---------------\n");
    printf("1. The game is played on a 3x3 board.\n");
    printf("2. Player 1 is X and Player 2 is O.\n");
    printf("3. Players take turns. On your turn, type the number\n");
    printf("   (1-9) of the empty cell where you want to play:\n\n");
    printf("         1 | 2 | 3\n");
    printf("        ---+---+---\n");
    printf("         4 | 5 | 6\n");
    printf("        ---+---+---\n");
    printf("         7 | 8 | 9\n\n");
    printf("4. Get 3 of your symbols in a row, column or diagonal to win.\n");
    printf("5. If all 9 cells are filled and nobody wins, it is a draw.\n");
    printf("-------------------------------------------\n");
}

/* Fills the board with '1'..'9' so players can see cell numbers */
void initBoard(char board[SIZE][SIZE])
{
    int i, j;
    char c = '1';

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            board[i][j] = c;
            c++;
        }
    }
}

/* Draws the current board on screen */
void displayBoard(char board[SIZE][SIZE])
{
    int i;

    printf("\n");
    for (i = 0; i < SIZE; i++) {
        printf("     %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < SIZE - 1) {
            printf("    ---+---+---\n");
        }
    }
    printf("\n");
}

/*
 * Reads a whole line and accepts it only if it is a single integer
 * between low and high. Keeps asking until the input is valid.
 * This stops the program from breaking on letters or junk input.
 */
int readNumber(const char *prompt, int low, int high)
{
    char line[100];
    int value;
    char extra;

    while (1) {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            /* Input closed (e.g. Ctrl+D): exit safely */
            printf("\nInput ended. Exiting.\n");
            exit(0);
        }

        /* sscanf returns 1 only if exactly one integer and nothing else */
        if (sscanf(line, "%d %c", &value, &extra) == 1 &&
            value >= low && value <= high) {
            return value;
        }
        printf("Invalid input! Please enter a number from %d to %d.\n",
               low, high);
    }
}

/* Reads a player name (spaces allowed, empty name not allowed) */
void readName(const char *prompt, char name[])
{
    char line[100];

    while (1) {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nInput ended. Exiting.\n");
            exit(0);
        }

        line[strcspn(line, "\n")] = '\0';   /* remove newline */

        if (strlen(line) == 0) {
            printf("Name cannot be empty.\n");
        } else if (strlen(line) >= NAME_LEN) {
            printf("Name too long (max %d characters).\n", NAME_LEN - 1);
        } else {
            strcpy(name, line);
            return;
        }
    }
}

/*
 * Places the symbol at the given position (1-9).
 * Returns 1 if the move was made, 0 if the cell is already taken.
 */
int makeMove(char board[SIZE][SIZE], int position, char symbol)
{
    int row = (position - 1) / SIZE;
    int col = (position - 1) % SIZE;

    if (board[row][col] == 'X' || board[row][col] == 'O') {
        return 0;   /* cell already occupied */
    }
    board[row][col] = symbol;
    return 1;
}

/* Returns 1 if the given symbol has three in a row, column or diagonal */
int checkWinner(char board[SIZE][SIZE], char symbol)
{
    int i;

    for (i = 0; i < SIZE; i++) {
        /* check row i */
        if (board[i][0] == symbol && board[i][1] == symbol &&
            board[i][2] == symbol) {
            return 1;
        }
        /* check column i */
        if (board[0][i] == symbol && board[1][i] == symbol &&
            board[2][i] == symbol) {
            return 1;
        }
    }

    /* main diagonal */
    if (board[0][0] == symbol && board[1][1] == symbol &&
        board[2][2] == symbol) {
        return 1;
    }
    /* anti-diagonal */
    if (board[0][2] == symbol && board[1][1] == symbol &&
        board[2][0] == symbol) {
        return 1;
    }

    return 0;
}

/* Returns 1 if every cell is filled (used after checking for a winner) */
int isDraw(char board[SIZE][SIZE])
{
    int i, j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0;   /* an empty cell exists */
            }
        }
    }
    return 1;
}

/* Runs one full game, with a play-again option */
void playGame(char name1[], char name2[], int scores[])
{
    char board[SIZE][SIZE];
    int again = 1;

    while (again == 1) {
        int turn = 0;        /* 0 = Player 1 (X), 1 = Player 2 (O) */
        int gameOver = 0;
        int moves = 0;

        initBoard(board);
        printf("\n%s (X) vs %s (O) - Let's begin!\n", name1, name2);

        while (!gameOver) {
            char symbol = (turn == 0) ? 'X' : 'O';
            char *currentName = (turn == 0) ? name1 : name2;
            int position;
            char prompt[80];

            displayBoard(board);
            sprintf(prompt, "%s (%c), choose a cell (1-9): ", currentName, symbol);

            /* keep asking until a valid, empty cell is chosen */
            while (1) {
                position = readNumber(prompt, 1, 9);
                if (makeMove(board, position, symbol)) {
                    break;
                }
                printf("That cell is already taken. Try another one.\n");
            }
            moves++;

            if (checkWinner(board, symbol)) {
                displayBoard(board);
                printf("*** %s (%c) WINS! Congratulations! ***\n",
                       currentName, symbol);
                scores[turn]++;
                gameOver = 1;
            } else if (isDraw(board)) {
                displayBoard(board);
                printf("*** It's a DRAW after %d moves! ***\n", moves);
                scores[2]++;
                gameOver = 1;
            } else {
                turn = 1 - turn;   /* switch player */
            }
        }

        showScores(name1, name2, scores);
        printf("\nPlay again?\n1. Yes\n2. No (back to menu)\n");
        again = (readNumber("Enter choice (1-2): ", 1, 2) == 1);
    }
}

/* Prints the running scoreboard */
void showScores(char name1[], char name2[], int scores[])
{
    printf("\n------------- SCOREBOARD -------------\n");
    printf("%-20s (X) : %d wins\n", name1, scores[0]);
    printf("%-20s (O) : %d wins\n", name2, scores[1]);
    printf("%-24s : %d\n", "Draws", scores[2]);
    printf("--------------------------------------\n");
}
