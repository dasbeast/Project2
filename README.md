# Tic-Tac-Toe Game-Playing Program with MinMax-AB Algorithm

This program implements the Tic-Tac-Toe game using the MinMax-AB algorithm with alpha-beta pruning. The program allows you to select different evaluation functions for the computer and the player, and it plays the game in an AI vs. AI mode.

## Requirements

- C++ compiler (e.g., g++)

## Compilation

To compile the program, navigate to the directory containing the source code files and run the following command:

g++ -o tictactoe project2.cpp

This will create an executable file named `tictactoe`.

## Usage

To run the program, execute the `tictactoe` executable:

./tictactoe

The program will prompt you to select the evaluation functions for the player and the computer. Enter the corresponding numbers (1-4) for each evaluation function:

1. `checkWinner`
2. `checkWinner2`
3. `checkWinner3`
4. `checkWinner4`

After selecting the evaluation functions, the game will start, and the program will display the game board after each move. The game will continue until a winner is determined or the game ends in a tie.

## Output

The program will display the following information after each game:

- The final game board
- The winner or the result (tie)
- The number of nodes created by the player and the computer during the search
- The execution time for the player and the computer
- The memory usage of the program
- The winning statistics for each evaluation function

You can choose to play another game by entering any number, or exit the program by entering 0.



## Note

This program is designed for educational purposes and demonstrates the implementation of the MinMax-AB algorithm with alpha-beta pruning and different evaluation functions for the Tic-Tac-Toe game.
