#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "Day2.h"

static std::vector<std::vector<int>> readReports(const std::string& filename) {
    std::ifstream infile(filename);
    std::vector<std::vector<int>> matrix;

    if (!infile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return matrix;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::vector<int> row;
        std::istringstream rowStream(line);
        int value;

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
    std::vector<std::vector<int>> reports = readReports("reports.in");
    
    int answer1 = getSafeReportsNumber(reports);
    std::cout << "Answer #1: " << answer1 << "\n";

    int answer2 = getAdjustedSafeReportsNumber(reports);
    std::cout << "Answer #2: " << answer2 << "\n";
}