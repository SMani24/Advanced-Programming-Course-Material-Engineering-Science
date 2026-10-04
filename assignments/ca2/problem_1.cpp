// In the name of God
// SMani24

/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include <iostream>
#include <vector>

using namespace std;

void readBoard(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
        }
    }
}

void printBoard(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j];
            if (j < 8) {
                cout << " ";
            }
        }
        cout << "\n";
    }
}

bool isValid(int board[9][9], int row, int col, int num) {
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }
    
    for (int x = 0; x < 9; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }
    
    int startRow = row - (row % 3);
    int startCol = col - (col % 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    
    return true;
}

bool solveHelper(int board[9][9], const vector<pair<int, int>>& emptyCells, int index) {
    if (index == emptyCells.size()) {
        return true;
    }

    int row = emptyCells[index].first;
    int col = emptyCells[index].second;

    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            
            if (solveHelper(board, emptyCells, index + 1)) {
                return true;
            }
            
            board[row][col] = 0;
        }
    }
    
    return false;
}

bool solve(int board[9][9]) {
    vector<pair<int, int>> emptyCells;
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != 0) {
                int temp = board[i][j];
                board[i][j] = 0;
                if (!isValid(board, i, j, temp)) {
                    board[i][j] = temp;
                    return false;
                }
                board[i][j] = temp;
            } else {
                emptyCells.push_back({i, j});
            }
        }
    }
    
    return solveHelper(board, emptyCells, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int board[9][9];
    readBoard(board);
    
    if (solve(board)) {
        printBoard(board);
    } else {
        cout << "No solution exists\n";
    }
    
    return 0;
}