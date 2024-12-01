#include <set>
#include <iostream>

#include "Day1.h"
#include "DataColumns.h"

int main() {
    DataColumns data;
    data.loadFromFile("distances.in");

    int answer1 = getTotalDistance(data.getLeft(), data.getRight());
    std::cout << "Answer #1: " << answer1 << "\n";

    int answer2 = getSimilarityScore(data.getLeft(), data.getRight());
    std::cout << "Answer #2: " << answer2 << "\n";
}
