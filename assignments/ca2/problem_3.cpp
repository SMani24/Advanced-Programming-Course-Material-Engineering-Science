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
#include <string>
#include <vector>

using namespace std;

const char EMPTY = '.';
const char WALL = '*';
const char QUEEN = 'Q';

class NQueensSolver {
private:
    int n = 8;
    vector<vector<char>> board;
    vector<int> queens;
    int solutionNum = 0;
    bool isValid(int row, int col);
    bool threaten(int q1Row, int q1Col, int q2Row, int q2Col);

public:
    void readBoard();
    void solve();
    int getSolutionNum() {return solutionNum;}
};
bool NQueensSolver::threaten(
    int q1Row, 
    int q1Col, 
    int q2Row, 
    int q2Col
) {
    if (
        q1Row == q2Row || 
        q1Col == q2Col ||
        abs(q1Col - q2Col) == abs(q1Row - q2Row)
    )
        return true;

    return false;
}

bool NQueensSolver::isValid(int row, int col) {
    if (board[row][col] == WALL)
        return false;

    for (int queenCol = 0; queenCol < queens.size(); queenCol++)
        if (threaten(row, col, queens[queenCol], queenCol))
            return false;

    return true;
}

void NQueensSolver::solve() {
    if (queens.size() == n) {
        solutionNum++;
        return;
    }

    for (int queenRow = 0; queenRow < n; queenRow++) {
        if (!isValid(queenRow, queens.size()))
            continue;
        
        queens.push_back(queenRow);
        solve();
        queens.pop_back();
    }
}

void NQueensSolver::readBoard() {
    for (int row = 0; row < n; row++) {
        string line;
        cin >> line;
        board.push_back({});

        for (int col = 0; col < n; col++)
            board[row].push_back(line[col]);
    }
}

int main() {
    NQueensSolver nQueensSolver;
    nQueensSolver.readBoard();
    nQueensSolver.solve();
    cout << nQueensSolver.getSolutionNum() << endl;

    return 0;
}