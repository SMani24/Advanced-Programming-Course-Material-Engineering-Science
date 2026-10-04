// In the name of God
// SMani24

#include <iostream>

using namespace std;

const int emptyCell = 0;
const int tableSize = 9;
const int boxSize = 3;

void readBoard(int board[tableSize][tableSize]) {
    for (int row = 0; row < tableSize; row++) {
        for (int col = 0; col < tableSize; col++) {
            std::cin >> board[row][col];
        }
    }
}

void printBoard(int board[9][9]) {
    for (int row = 0; row < tableSize; row++) {
        for (int col = 0; col < tableSize; col++) {
            std::cout << board[row][col];
            if (col < tableSize - 1) std::cout << " ";
        }
        std::cout << '\n';
    }
}

bool isValid(int board[9][9], int row, int col, int number) {
    for (int i = 0; i < tableSize; i++) {
        if (board[row][i] == number) return false;
        if (board[i][col] == number) return false;
    }
    int boxRowStart = (row / boxSize) * boxSize;
    int boxColStart = (col / boxSize) * boxSize;
    for (int i = 0; i < boxSize; i++)
        for (int j = 0; j < boxSize; j++)
            if (board[boxRowStart + i][boxColStart + j] == number) return false;

    return true;
}

bool solve(int board[9][9], int row=0, int col=0) {
    for (int i = row; i < tableSize; i++) {
        for (int j = 0; j < tableSize; j++) {
            if (board[i][j] == emptyCell) {
                for (int number = 1; number <= tableSize; number++) {
                    if (isValid(board, i, j, number)) {
                        board[i][j] = number;
                        if (solve(board, i, j)) {
                            return true;
                        }
                        board[i][j] = emptyCell;
                    }
                }
                return false;
            }
        }
    }
    return true;
}
int main() {
    int board[9][9];
    readBoard(board);
    
    if (solve(board))
        printBoard(board);
    else
        cout << "No solution exists" << endl;
    
    return 0;
}