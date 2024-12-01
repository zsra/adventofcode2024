#include <set>
#include <unordered_map>

#include "Day1.h"

int getSimilarityScore(std::multiset<int> left, std::multiset<int> right) {
    int similarityScore = 0;

    std::unordered_map<int, int> rightFreq;
    for (const int& value : right) {
        ++rightFreq[value];
    }

    for (const int& leftValue : left) {
        similarityScore += leftValue * rightFreq[leftValue];
    }

    return similarityScore;
}