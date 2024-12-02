#include "Day2.h"

static bool areLevelsSafe(const std::vector<int>& levels) {
    bool isIncreasing = levels[1] > levels[0];

    for (int index = 1; index < levels.size(); index++) {
        int diff = levels.at(index) - levels.at(index - 1);

        if (std::abs(diff) < 1 || std::abs(diff) > 3) {
            return false;
        }

        if ((isIncreasing && diff < 0) || (!isIncreasing && diff > 0)) {
            return false;
        }
    }

    return true;
}

int getSafeReportsNumber(std::vector<std::vector<int>> reports) {
    int numberOfSaveReports = 0;

    for (const auto& levels : reports) {

        if (areLevelsSafe(levels)) {
            numberOfSaveReports++;
        }
    }

    return numberOfSaveReports;
}
