#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

struct Coord {
    int r, c;

    Coord(int row, int col) : r(row), c(col) {}

    Coord relative(const Coord& direction) const {
        return { r + direction.r, c + direction.c };
    }

    Coord distance(const Coord& other) const {
        return { other.r - r, other.c - c };
    }

    bool operator<(const Coord& other) const {
        return tie(r, c) < tie(other.r, other.c);
    }
};

class Grid {
private:
    vector<string> grid;

public:
    explicit Grid(const vector<string>& input) : grid(input) {}

    char get(int r, int c) const {
        return grid[r][c];
    }

    bool isValid(const Coord& coord) const {
        return coord.r >= 0 && coord.r < (int)grid.size() &&
            coord.c >= 0 && coord.c < (int)grid[0].size();
    }

    int getHeight() const {
        return grid.size();
    }

    int getWidth() const {
        return grid[0].size();
    }
};

static vector<string> readInput(const string& filename) {
    ifstream file(filename);
    vector<string> input;
    string line;
    while (getline(file, line)) {
        input.push_back(line);
    }
    return input;
}

int main() {
    vector<string> input = readInput("map.in");
    Grid grid(input);

    map<char, vector<Coord>> antennae;
    for (int r = 0; r < grid.getHeight(); r++) {
        for (int c = 0; c < grid.getWidth(); c++) {
            char a = grid.get(r, c);
            if (a != '.') {
                antennae[a].emplace_back(r, c);
            }
        }
    }

    set<Coord> antinodes, full;
    for (const auto& [character, matching] : antennae) {
        for (size_t i = 0; i < matching.size(); i++) {
            for (size_t j = 0; j < matching.size(); j++) {
                if (i == j) continue;

                Coord d = matching[i].distance(matching[j]);
                if (grid.isValid(matching[j].relative(d))) {
                    antinodes.insert(matching[j].relative(d));
                }

                Coord curr = matching[i];
                while (grid.isValid(curr.relative(d))) {
                    full.insert(curr.relative(d));
                    curr = curr.relative(d);
                }
            }
        }
    }

    cout << "Answer #1: " << antinodes.size() << endl;
    cout << "Answer #2: " << full.size() << endl;

    return 0;
}
