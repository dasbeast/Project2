#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <chrono>
#include <sys/resource.h>

using namespace std;

bool checkWinner(char symbol);
bool checkWinner2(char symbol);
bool checkWinner3(char symbol);
bool checkWinner4(char symbol);
constexpr int BOARD_SIZE = 3;
char board[BOARD_SIZE][BOARD_SIZE];
char PLAYER = 'X';
char COMPUTER = 'O';
int compEval = 0;
int playerEval = 0;
int nodesCreated1 = 0;
int nodesCreated2 = 0;
long long playerTime = 0;
long long computerTime = 0;
int evalArray[4] = {0, 0, 0, 0};
bool (*functions[])(char) = {checkWinner, checkWinner2, checkWinner3, checkWinner4};

long long getMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}
void printBoard() {
    cout << "  0 1 2" << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isValidMove(int x, int y) {
    return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && board[x][y] == ' ');
}

bool getUserMove(int& x, int& y) {
    // No user input in AI vs AI mode, so this function is not needed
    return false;
}


// checkWinner uses a straightforward approach to check for three in a row.
bool checkWinner(char symbol) {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol) {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return true;
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return true;
    }

    return false;
}

// checkWinner2 uses a magic square approach to check for a winner.

bool checkWinner2(char symbol)
{
    int counter = 0;
    int magicSquare[3][3] = {
            {8,3,4}, {1,5,9}, {6,7,2}
    };
    //checks rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == symbol) {
            counter = counter + magicSquare[i][0];
        }
        if (board[i][1] == symbol) {
            counter = counter + magicSquare[i][1];
        }
        if (board[i][2] == symbol) {
            counter = counter + magicSquare[i][2];
        }
        if(counter == 15)
        {
            return true;
        }
        counter = 0;
    }


    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == symbol) {
            counter = counter + magicSquare[0][j];
        }
        if (board[1][j] == symbol) {
            counter = counter + magicSquare[1][j];
        }
        if (board[2][j] == symbol) {
            counter = counter + magicSquare[2][j];
        }
        if(counter == 15)
        {
            return true;
        }
        counter = 0;
    }

    //Check Diagonals
    if (board[0][0] == symbol) {
        counter = counter + magicSquare[0][0];
    }
    if (board[1][1] == symbol) {
        counter = counter + magicSquare[1][1];
    }
    if (board[2][2] == symbol) {
        counter = counter + magicSquare[2][2];
    }
    if(counter == 15)
    {
        return true;
    }
    counter = 0;
    if (board[0][2] == symbol) {
        counter = counter + magicSquare[0][2];
    }
    if (board[1][1] == symbol) {
        counter = counter + magicSquare[1][1];
    }
    if (board[2][0] == symbol) {
        counter = counter + magicSquare[2][0];
    }
    if(counter == 15)
    {
        return true;
    }
    return false;

}

// checkWinner3 uses bitwise operations to check for a winner.
bool checkWinner3(char player) {
    int mask = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == player) {
                mask |= (1 << (i * 3 + j));
            }
        }
    }

    // Check rows
    for (int i = 0; i < 3; i++) {
        if ((mask & 0b111 << (i * 3)) == 0b111 << (i * 3)) {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if ((mask & 0b100100100) == 0b100100100 << i) {
            return true;
        }
    }

    // Check diagonals
    if ((mask & 0b100010001) == 0b100010001) {
        return true;
    }
    if ((mask & 0b001010100) == 0b001010100) {
        return true;
    }
    return false;
}


// checkWinner4 assigns scores based on potential winning moves and checks if the given symbol has the maximum possible score.
bool checkWinner4(char symbol) {
    int opponent = (symbol == PLAYER) ? COMPUTER : PLAYER;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        int rowScore = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == symbol) {
                rowScore += 1;
            } else if (board[i][j] == opponent) {
                rowScore -= 1;
            }
        }
        if (rowScore == BOARD_SIZE) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        int colScore = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i][j] == symbol) {
                colScore += 1;
            } else if (board[i][j] == opponent) {
                colScore -= 1;
            }
        }
        if (colScore == BOARD_SIZE) {
            return true;
        }
    }

    // Check diagonals
    int diag1Score = 0;
    int diag2Score = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][i] == symbol) {
            diag1Score += 1;
        } else if (board[i][i] == opponent) {
            diag1Score -= 1;
        }

        if (board[i][BOARD_SIZE - i - 1] == symbol) {
            diag2Score += 1;
        } else if (board[i][BOARD_SIZE - i - 1] == opponent) {
            diag2Score -= 1;
        }
    }
    if (diag1Score == BOARD_SIZE || diag2Score == BOARD_SIZE) {
        return true;
    }

    return false;
}

int minimax(char player, int depth, int alpha, int beta) {
    // Check for a winner
    auto start = chrono::high_resolution_clock::now();
    if(player == COMPUTER)
    {
        nodesCreated2++;
    }
    if(player == PLAYER)
    {
        nodesCreated1++;
    }


    if (functions[compEval-1](COMPUTER)) {
        return 1;
    } else if (functions[playerEval-1](PLAYER)) {
        return -1;
    }

    // Check for a tie
    bool tie = true;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                tie = false;
                break;
            }
        }
    }
    if (tie) {
        return 0;
    }

    int bestScore;
    if (player == COMPUTER) {
        bestScore = numeric_limits<int>::min();
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = COMPUTER;
                    int score = minimax(PLAYER, depth + 1, alpha, beta);
                    board[i][j] = ' ';
                    bestScore = max(bestScore, score);
                    alpha = max(alpha, score);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
    } else {
        bestScore = numeric_limits<int>::max();
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    int score = minimax(COMPUTER, depth + 1, alpha, beta);
                    board[i][j] = ' ';
                    bestScore = min(bestScore, score);
                    beta = min(beta, score);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    if (player == COMPUTER) {
        computerTime += duration;
    } else {
        playerTime += duration;
    }
    return bestScore;
}

void computerMove() {
    int bestScore = numeric_limits<int>::min();
    int bestX, bestY;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                int score = minimax(PLAYER, 0, numeric_limits<int>::min(), numeric_limits<int>::max());
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestX = i;
                    bestY = j;
                }
            }
        }
    }
    board[bestX][bestY] = COMPUTER;
}
void computerMove1() {
    int bestScore = numeric_limits<int>::min();
    int bestX, bestY;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = PLAYER;
                int score = minimax(COMPUTER, 0, numeric_limits<int>::min(), numeric_limits<int>::max());
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestX = i;
                    bestY = j;
                }
            }
        }
    }
    board[bestX][bestY] = PLAYER;
}

void playGame() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "Which evaluation functions do you want to use? (1-4)" << endl;
    cout << "Eval Function for player: ";
    cin >> playerEval;
    cout << endl;
    cout << "Eval Function for Computer: ";
    cin >> compEval;
    cout << endl;
    while (playerEval < 1 || playerEval > 4) {
        cout << "Invalid choice" << endl;
        cout << "Eval Function for Player: ";
        cin >> playerEval;
    }
    while (compEval < 1 || compEval > 4) {
        cout << "Invalid choice" << endl;
        cout << "Eval Function for Computer: ";
        cin >> compEval;
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    srand(time(nullptr));
    int x = rand() % BOARD_SIZE;
    int y = rand() % BOARD_SIZE;

    // Assign 'X' to the randomly chosen square
    board[x][y] = 'X';

    while (true) {
        printBoard();

        // User's move (Removed for AI vs AI)
        /*int x, y;
        while (true) {
            if (getUserMove(x, y)) {
                board[x][y] = PLAYER;
                break;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        }*/
        computerMove1();
        if (functions[playerEval-1](PLAYER)) {
            printBoard();
            cout << "Computer 1 wins!" << endl;
            evalArray[compEval-1]++;
            return;
        }



        // Check for a tie



        // Computer's move
        computerMove();

        if (functions[compEval-1](COMPUTER)) {
            printBoard();
            cout << "Computer 2 wins!" << endl;
            evalArray[compEval-1]++;
            return;
        }

        bool tie = true;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    tie = false;
                    break;
                }
            }
        }
        if (tie) {
            printBoard();
            cout << "It's a tie!" << endl;
            cout << endl;
            return;
        }

    }
}

int main() {
    bool flag = true;
    int choice;
    while (flag) {
        playGame();
        printf("Nodes created by eval %d: %d vs eval %d: %d\n", playerEval, nodesCreated1, compEval, nodesCreated2);
        printf("Execution time for eval %d: %lld microseconds vs eval %d: %lld microseconds\n", playerEval, playerTime,
               compEval, computerTime);
        printf("Memory usage: %lld bytes\n", getMemoryUsage());
        for (int i = 0; i < 4; i++) {
            printf("Eval Function %d wins: %d\n", (i + 1), evalArray[i]);
        }
        printf("\nEnter any number to play again or Exit (0) \n");
        cin >> choice;
        if (choice == 0) {
            flag = false;
        }
        nodesCreated1 = 0;
        nodesCreated2 = 0;
    }
    return 0;
}