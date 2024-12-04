#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Day4.h"

static std::vector<std::vector<char>> readPuzzle(const std::string& filename) {
    std::ifstream infile(filename);
    std::vector<std::vector<char>> matrix;

    if (!infile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return matrix;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::vector<char> row;
        std::istringstream rowStream(line);
        char value;

        while (rowStream >> value) {
            row.push_back(value);
        }

        matrix.push_back(row);
    }

    infile.close();
    return matrix;
}

int main()
{
    std::vector<std::vector<char>> puzzle = readPuzzle("puzzle.in");

    int answer1 = countAllXmasWordsFromPuzzle(puzzle);
    std::cout << "Answer #1: " << answer1 << "\n";

    int answer2 = countAllMasXWordsFromPuzzle(puzzle);
    std::cout << "Answer #2: " << answer2 << "\n";
}
