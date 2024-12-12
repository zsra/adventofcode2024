#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>
#include <string>

using namespace std;

using Grid = map<pair<int, int>, char>;

vector<pair<int, int>> diffs = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

pair<int, int> evaluate(const Grid& grid, int sy, int sx, set<pair<int, int>>& region) {
    int area = 0, perimeter = 0;
    vector<pair<int, int>> border = { {sy, sx} };

    while (!border.empty()) {
        auto [y, x] = border.back();
        border.pop_back();
        if (region.count({ y, x })) continue;
        region.insert({ y, x });
        area++;

        for (const auto& [dy, dx] : diffs) {
            int ny = y + dy, nx = x + dx;
            if (grid.count({ ny, nx }) && grid.at({ ny, nx }) == grid.at({ y, x })) {
                border.push_back({ ny, nx });
            }
            else {
                perimeter++;
            }
        }
    }
    return { area, perimeter };
}

int find_sides(const set<pair<int, int>>& region) {
    set<pair<int, int>> corners;
    int double_edges = 0;

    set<int> xs, ys;
    for (const auto& [y, x] : region) {
        xs.insert(x);
        ys.insert(y);
    }

    for (int y = *ys.begin() - 1; y <= *ys.rbegin() + 1; ++y) {
        for (int x = *xs.begin() - 1; x <= *xs.rbegin() + 1; ++x) {
            int index = 0;
            index += region.count({ y - 1, x - 1 }) * 1;
            index += region.count({ y - 1, x }) * 2;
            index += region.count({ y, x - 1 }) * 4;
            index += region.count({ y, x }) * 8;

            if (index != 0 && index != 3 && index != 5 && index != 10 && index != 12 && index != 15) {
                corners.insert({ y, x });
            }
            if (index == 6 || index == 9) {
                double_edges++;
            }
        }
    }

    return corners.size() + double_edges;
}

int main() {
    ifstream file("region.in");
    vector<string> data;
    string line;

    while (getline(file, line)) {
        data.push_back(line);
    }

    int H = data.size();
    int W = data[0].size();

    Grid grid;
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            grid[{y, x}] = data[y][x];
        }
    }

    set<pair<int, int>> seen;
    int p1 = 0, p2 = 0;

    for (const auto& [key, value] : grid) {
        auto [y, x] = key;
        if (!seen.count({ y, x })) {
            set<pair<int, int>> region;
            auto [area, perimeter] = evaluate(grid, y, x, region);
            seen.insert(region.begin(), region.end());
            p1 += area * perimeter;
            p2 += area * find_sides(region);
        }
    }

    cout << "Answer #1: " << p1 << endl;
    cout << "Answer #2: " << p2 << endl;

    return 0;
}