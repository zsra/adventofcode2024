#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

vector<string> readLines(const string& filename) {
    vector<string> lines;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        // Remove trailing spaces
        line.erase(line.find_last_not_of(" \n\r\t") + 1);
        lines.push_back(line);
    }

    return lines;
}

void solve(int part, const vector<string>& lines) {
    long long tokens = 0;
    long long add = (part == 2) ? 10000000000000LL : 0;

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    for (const string& line : lines) {
        if (line.rfind("Button", 0) == 0) {
            stringstream ss(line);
            string word, a;
            vector<string> parts;

            while (ss >> word) {
                parts.push_back(word);
            }

            a = parts[1].substr(0, parts[1].find(":"));

            if (a == "A") {
                x1 = stoi(parts[2].substr(2, parts[2].size() - 3));
                y1 = stoi(parts[3].substr(2));
            }
            else {
                x2 = stoi(parts[2].substr(2, parts[2].size() - 3));
                y2 = stoi(parts[3].substr(2));
            }

        }
        else if (line.rfind("Prize", 0) == 0) {
            stringstream ss(line);
            string word;
            vector<string> parts;

            while (ss >> word) {
                parts.push_back(word);
            }

            long long c = stoll(parts[1].substr(2, parts[1].size() - 3)) + add;
            long long d = stoll(parts[2].substr(2)) + add;

            double a = (double)(c * y2 - d * x2) / (x1 * y2 - y1 * x2);
            double b = (double)(d * x1 - c * y1) / (x1 * y2 - y1 * x2);

            if (a == floor(a) && b == floor(b)) {
                tokens += (long long)(3 * a + b);
            }
        }
    }

    cout << tokens << endl;
}

int main() {
    vector<string> lines = readLines("tokens.in");

    solve(1, lines);
    solve(2, lines);

    return 0;
}
