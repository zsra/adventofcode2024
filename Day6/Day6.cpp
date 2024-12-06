#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS

struct Index {
    int r, c;

    bool operator==(const Index& other) const {
        return r == other.r && c == other.c;
    }

    bool operator<(const Index& other) const {
        if (r == other.r) return c < other.c;
        return r < other.r;
    }
};
std::vector<std::vector<char>> parseInput(const std::string& fileName, Index& startIndex) {
    std::ifstream file(fileName);
    std::vector<std::vector<char>> grid;
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    while (std::getline(file, line)) {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
        auto it = std::find(row.begin(), row.end(), '^');
        if (it != row.end()) {
            startIndex = { static_cast<int>(grid.size() - 1), static_cast<int>(it - row.begin()) };
            grid[startIndex.r][startIndex.c] = '.';
        }
    }

    return grid;
}

bool isValidIndex(const Index& idx, int maxRow, int maxCol) {
    return idx.r >= 0 && idx.c >= 0 && idx.r < maxRow && idx.c < maxCol;
}

std::pair<std::vector<Index>, int> partOne(std::vector<std::vector<char>>& grid, const Index& startIndex) {
    std::vector<Index> directions = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
    int maxRow = grid.size();
    int maxCol = grid[0].size();
    std::map<Index, bool> visited;

    Index at = startIndex;
    int facing = 0;

    while (isValidIndex(at, maxRow, maxCol)) {
        if (grid[at.r][at.c] == '#') {
            at.r -= directions[facing].r;
            at.c -= directions[facing].c;
            facing = (facing + 1) % directions.size();
            continue;
        }
        visited[at] = true;
        grid[at.r][at.c] = 'X';
        at.r += directions[facing].r;
        at.c += directions[facing].c;
    }

    std::vector<Index> visitedIndices;
    for (const auto& kv : visited) {
        visitedIndices.push_back(kv.first);
    }

    return { visitedIndices, static_cast<int>(visitedIndices.size()) };
}

bool hasCycle(std::vector<std::vector<char>>& grid, const Index& startIndex) {
    std::map<Index, Index> visited;
    std::vector<Index> directions = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
    int maxRow = grid.size();
    int maxCol = grid[0].size();

    Index at = startIndex;
    int facing = 0;

    while (isValidIndex(at, maxRow, maxCol)) {
        if (visited[at] == directions[facing]) {
            return true;
        }

        visited[at] = directions[facing];

        if (grid[at.r][at.c] == '#') {
            at.r -= directions[facing].r;
            at.c -= directions[facing].c;
            facing = (facing + 1) % directions.size();
            continue;
        }

        grid[at.r][at.c] = 'X';
        at.r += directions[facing].r;
        at.c += directions[facing].c;
    }

    return false;
}

int partTwo(std::vector<std::vector<char>>& grid, const Index& startIndex, const std::vector<Index>& visitedIndices) {
    int cycleCount = 0;
    for (const auto& idx : visitedIndices) {
        if (idx == startIndex || grid[idx.r][idx.c] == '#') {
            continue;
        }
        grid[idx.r][idx.c] = '#';
        if (hasCycle(grid, startIndex)) {
            cycleCount++;
        }
        grid[idx.r][idx.c] = '.';
    }

    return cycleCount;
}

int main() {
    try {
        Index startIndex;
        auto puzzleInput = parseInput("lab.in", startIndex);
        auto [visitedIndices, res] = partOne(puzzleInput, startIndex);
        std::cout << "Part One: " << res << std::endl;
        std::cout << "Part Two: " << partTwo(puzzleInput, startIndex, visitedIndices) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
