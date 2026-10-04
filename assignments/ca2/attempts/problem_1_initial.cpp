// In the name of God
// SMani24

#include <iostream>
using namespace std;

namespace SudokuConsts {
    const int TABLE_SIZE = 9;
    const int EMPTY_CELL = 0;
}

class SudokuTable {
private:
    int tableSize = SudokuConsts::TABLE_SIZE;
    int boxSize = 3;
    int table[9][9];
    bool isValid(int row, int col, int number);

public:
    void readTable();
    bool backTrackingSolve();
    void printTable();
};

bool SudokuTable::isValid(int row, int col, int number) {
    for (int i = 0; i < tableSize; i++) {
        if (table[row][i] == number) return false;
        if (table[i][col] == number) return false;
    }
    int boxRowStart = (row / boxSize) * boxSize;
    int boxColStart = (col / boxSize) * boxSize;
    for (int i = 0; i < boxSize; i++) {
        for (int j = 0; j < boxSize; j++) {
            if (table[boxRowStart + i][boxColStart + j] == number) return false;
        }
    }
    return true;
}

bool SudokuTable::backTrackingSolve() {
    for (int row = 0; row < tableSize; row++) {
        for (int col = 0; col < tableSize; col++) {
            if (table[row][col] == SudokuConsts::EMPTY_CELL) {
                for (int number = 1; number <= tableSize; number++) {
                    if (isValid(row, col, number)) {
                        table[row][col] = number;
                        if (backTrackingSolve()) {
                            return true;
                        }
                        table[row][col] = SudokuConsts::EMPTY_CELL;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void SudokuTable::readTable() {
    for (int row = 0; row < tableSize; row++) {
        for (int col = 0; col < tableSize; col++) {
            std::cin >> table[row][col];
        }
    }
}

void SudokuTable::printTable() {
    for (int row = 0; row < tableSize; row++) {
        for (int col = 0; col < tableSize; col++) {
            std::cout << table[row][col];
            if (col < tableSize - 1) std::cout << " ";
        }
        std::cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    SudokuTable sudokuTable;
    sudokuTable.readTable();
    
    if (sudokuTable.backTrackingSolve()) {
        sudokuTable.printTable();
    } else {
        std::cout << "No solution exists\n";
    }
    
    return 0;
}