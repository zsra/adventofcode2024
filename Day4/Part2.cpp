#include <string>

#include "Day4.h"

const std::string MAS = "MAS";
const std::string SAM = "SAM";

int countAllMasXWordsFromPuzzle(const std::vector<std::vector<char>>& puzzle) {
    int count = 0;
    int rows = puzzle.size();
    int cols = puzzle[0].size();

    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {      
            if (puzzle[i][j] == 'A') {

                std::string cross1 = std::string("") + puzzle[i - 1][j - 1] + puzzle[i][j] + puzzle[i + 1][j + 1];
                std::string cross2 = std::string("") + puzzle[i - 1][j + 1] + puzzle[i][j] + puzzle[i + 1][j - 1];

                if (cross1 == MAS || cross1 == SAM) {
                    if (cross2 == MAS || cross2 == SAM) {
                        count++;
                    }
                }         
            }
        }
    }

    return count;
}