#include <string>

#include "Day4.h"

static bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

int countAllXmasWordsFromPuzzle(const std::vector<std::vector<char>>& puzzle) {
    int count = 0;
    int rows = puzzle.size();
    int cols = puzzle[0].size();

    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (puzzle[i][j] == 'X') {
                for (const auto& dir : directions) {
                    int dx = dir.first;
                    int dy = dir.second;

                    int x1 = i + dx, y1 = j + dy;
                    int x2 = i + 2 * dx, y2 = j + 2 * dy;
                    int x3 = i + 3 * dx, y3 = j + 3 * dy;

                    if (isValid(x1, y1, rows, cols) && puzzle[x1][y1] == 'M' &&
                        isValid(x2, y2, rows, cols) && puzzle[x2][y2] == 'A' &&
                        isValid(x3, y3, rows, cols) && puzzle[x3][y3] == 'S') {
                        ++count;
                    }
                }
            }
        }
    }

    return count;
}