#include <iostream>
#include <fstream>
#include <sstream>

#include "Day11.h"

template<typename Out>
void split(const string& s, char delimiter, Out result) {
    istringstream iss(s);
    string item;
    while (getline(iss, item, delimiter)) {
        *result++ = item;
    }
}

static vector<string> split(const string& s) {
    vector<string> elements;
    split(s, ' ', back_inserter(elements));
    return elements;
}


int main() {
    ifstream inputFile("blinking.in");
    if (!inputFile) {
        cerr << "Error opening the file" << endl;
        return 1;
    }

    std::vector<long long> numbers;
    std::string line;

    while (getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            numbers.push_back(std::stoll(word));
        }
    }

    for (int step = 0; step < 25; ++step) {
        std::vector<long long> new_numbers;
        for (long long number : numbers) {
            if (number == 0) {
                new_numbers.push_back(1);
                continue;
            }

            std::string word = std::to_string(number);
            if (word.length() % 2 == 0) {
                long long half_length = word.length() / 2;
                new_numbers.push_back(stoll(word.substr(0, half_length)));
                new_numbers.push_back(stoll(word.substr(half_length)));
            }
            else {
                new_numbers.push_back(number * 2024);
            }
        }
        numbers = new_numbers;
    }

    cout << "Answer #1: " << numbers.size() << endl;

    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    string fileContent((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    vector<string> stones = split(fileContent);

    inputFile.close();

    cout << "Answer #2: " << GetStones(stones) << endl;

    return 0;
}
