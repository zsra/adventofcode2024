#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>

struct Result {
    std::map<int, std::set<int>> rules;
    std::vector<std::vector<int>> pages;
};

static Result readManual(const std::string& fileName) {
    Result result;
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return result;
    }

    std::string line;
    bool readingMatrix = false;

    while (std::getline(file, line)) {
        if (line.empty()) {
            readingMatrix = true;
            continue;
        }

        if (readingMatrix) {
            std::istringstream lineStream(line);
            std::vector<int> row;
            std::string valueStr;

            while (std::getline(lineStream, valueStr, ',')) {
                int value = std::stoi(valueStr);
                row.push_back(value);
            }
            result.pages.push_back(row);
        }
        else {
            std::istringstream lineStream(line);
            std::string keyStr, valueStr;

            if (std::getline(lineStream, keyStr, '|') && std::getline(lineStream, valueStr)) {
                int key = std::stoi(keyStr);
                int value = std::stoi(valueStr);
                result.rules[key].insert(value);
            }
        }
    }

    file.close();
    return result;
}

int main() {
    Result result = readManual("manual.in");
    const auto& rules = result.rules;
    const auto& pages = result.pages;

    unsigned answer1 = 0;
    unsigned answer2 = 0;

    auto comperator = [&rules](int a, int b) { return rules.at(a).count(b) > 0; };
    auto getMidValue = [](const std::vector<int>& v) { return v[(v.size() - 1) / 2]; };

    for (const auto& page : pages) {
        std::vector<int> sorted_page = page;
        std::sort(sorted_page.begin(), sorted_page.end(), comperator);
        
        if (sorted_page == page) {
            answer1 += getMidValue(page);
        }
        else {
            answer2 += getMidValue(sorted_page);
        }
    }

    std::cout << "Answer #1: " << answer1 << "\n";
    std::cout << "Answer #2: " << answer2 << "\n";
}
