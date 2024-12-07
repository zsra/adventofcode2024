#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<unsigned long long> results;
vector<vector<unsigned long long>> terms;

static void readData(const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        istringstream ss(line);
        string part;
        getline(ss, part, ':');
        results.push_back(stoull(part));

        vector<unsigned long long> term;
        while (ss >> part) {
            term.push_back(stoull(part));
        }
        terms.push_back(term);
    }

    file.close();
}

static bool dfs(const vector<unsigned long long>& numbers, unsigned long long i, unsigned long long current_sum, unsigned long long result) {
    if (i == numbers.size()) {
        return current_sum == result;
    }
    else {
        unsigned long long op1 = current_sum + numbers[i];
        unsigned long long op2 = current_sum * numbers[i];
        return dfs(numbers, i + 1, op1, result) || dfs(numbers, i + 1, op2, result);
    }
}

static bool dfsPart2(const vector<unsigned long long>& numbers, unsigned long long i, unsigned long long current_sum, unsigned long long result) {
    if (i == numbers.size()) {
        return current_sum == result;
    }
    else {
        unsigned long long op1 = current_sum + numbers[i];
        unsigned long long op2 = current_sum * numbers[i];
        unsigned long long op3 = stoull(to_string(current_sum) + to_string(numbers[i]));
        return dfsPart2(numbers, i + 1, op1, result) || dfsPart2(numbers, i + 1, op2, result) || dfsPart2(numbers, i + 1, op3, result);
    }
}

int main() {
    readData("calibration.in");

    unsigned long long sum = 0;
    for (unsigned long long i = 0; i < results.size(); ++i) {
        if (dfs(terms[i], 0, 0, results[i])) {
            sum += results[i];
        }
    }
    cout << "Answer #1: " << sum << endl;

    sum = 0;
    for (unsigned long long i = 0; i < results.size(); ++i) {
        if (dfsPart2(terms[i], 0, 0, results[i])) {
            sum += results[i];
        }
    }
    cout << "Answer #2: " << sum << endl;

    return 0;
}
