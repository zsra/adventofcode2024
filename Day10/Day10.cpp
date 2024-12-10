#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <complex>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

using Complex = complex<int>;
using Grid = unordered_map<Complex, int>;
using SeenSet = unordered_set<Complex>;

namespace std {
    template<>
    struct hash<Complex> {
        size_t operator()(const Complex& c) const {
            return hash<int>()(c.real()) ^ hash<int>()(c.imag());
        }
    };
}

Grid readGrid(const string& filename) {
    Grid grid;
    ifstream file(filename);
    string line;
    int i = 0;
    while (getline(file, line)) {
        for (size_t j = 0; j < line.size(); ++j) {
            grid[Complex(i, j)] = line[j] - '0';
        }
        ++i;
    }
    return grid;
}

int search(const Complex& pos, SeenSet& seen, const Grid& grid, int height = 0, int part = 1) {
    if (grid.count(pos) && grid.at(pos) == height) {
        if (height < 9 || (part == 1 && seen.count(pos))) {
            int sum = 0;
            vector<Complex> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
            for (const auto& dir : directions) {
                sum += search(pos + dir, seen, grid, height + 1, part);
            }
            return sum;
        }
        seen.insert(pos);
        return 1;
    }
    return 0;
}

int main() {
    Grid grid = readGrid("map.in");

    for (int part = 1; part <= 2; ++part) {
        int result = 0;
        for (const auto& [pos, value] : grid) {
            if (value == 0) {
                SeenSet seen;
                result += search(pos, seen, grid, 0, part);
            }
        }
        cout << result << endl;
    }

    return 0;
}
