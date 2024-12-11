#include <unordered_map>

#include "Day11.h"

static long long blink(const string& stone, long long blinks, unordered_map<string, long long>& memo) {
    if (blinks == 75) {
        return 1;
    }

    string memoKey = stone + "." + to_string(blinks);
    if (memo.find(memoKey) != memo.end()) {
        return memo[memoKey];
    }

    if (stone == "0") {
        memo[memoKey] = blink("1", blinks + 1, memo);
        return memo[memoKey];
    }

    if (stone.length() % 2 == 0) {
        string left = stone.substr(0, stone.length() / 2);
        string right = to_string(stoll(stone.substr(stone.length() / 2)));

        memo[memoKey] = blink(left, blinks + 1, memo) + blink(right, blinks + 1, memo);
        return memo[memoKey];
    }

    memo[memoKey] = blink(to_string(stoll(stone) * 2024), blinks + 1, memo);
    return memo[memoKey];
}

long long GetStones(vector<string> stones) {
    long long numStones = 0;
    unordered_map<string, long long> memo;

    for (const string& stone : stones) {
        numStones += blink(stone, 0, memo);
    }

    return numStones;
}