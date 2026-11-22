# Project_Tic_Tac_Toe

**FOCP-I (C Programming) Mini Project**

A two-player, console-based Tic-Tac-Toe game written in C.

## Team Members

| Name | Roll No. | GitHub |
|------|----------|--------|
|Vinay | 26CSU154 |vinee9708|

## Description

Two players take turns placing X and O on a 3x3 board by typing the number (1-9) of an empty cell. The program checks every row, column and diagonal after each move to find a winner. If all nine cells are filled with no winner, the game ends in a draw. Scores are tracked across games until the program is closed.

## Features

- Menu-driven interface (Play, Set Player Names, Scoreboard, How to Play, Exit)
- 3x3 board display with cell numbers shown for easy selection
- Move validation: rejects letters, out-of-range numbers and already-occupied cells
- Win detection (rows, columns, both diagonals) and draw detection
- Custom player names
- Running scoreboard (X wins, O wins, draws)
- Play-again option after every game
- Clear instructions and win/draw messages

## C Concepts Used

2D arrays, user-defined functions, loops, conditional statements, `switch`, strings and character arrays, input validation using `fgets` and `sscanf`.

## How to Compile and Run

Make sure `gcc` is installed, then run these commands in the project folder.

**Windows (PowerShell):**
```
gcc -Wall tictactoe.c -o tictactoe
.\tictactoe.exe
```

**Linux / macOS:**
```
gcc -Wall tictactoe.c -o tictactoe
./tictactoe
```

The program compiles with no warnings under `gcc -Wall`.

## How to Play

1. Choose **Play Game** from the menu.
2. Player 1 is **X** and Player 2 is **O**. Players take turns.
3. On your turn, enter the number of the empty cell where you want to play:

```
 1 | 2 | 3
---+---+---
 4 | 5 | 6
---+---+---
 7 | 8 | 9
```

4. Get three of your symbols in a row, column or diagonal to win.
5. If the board fills up with no winner, the game is a draw.


## Repository Structure

```
Project_Tic_Tac_Toe/
├── README.md
├── tictactoe.c
├── screenshots/
└── docs/
```
