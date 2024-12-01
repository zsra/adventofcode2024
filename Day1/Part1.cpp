#include <set>
#include <cstdlib>

#include "Day1.h"

int getTotalDistance(std::multiset<int> left, std::multiset<int> right) {
	int distance = 0;

	std::multiset<int>::iterator leftIterator = left.begin();
	std::multiset<int>::iterator rightIterator = right.begin();

    while (leftIterator != left.end() || rightIterator != right.end()) {
        int leftValue = 0;
        if (leftIterator != left.end()) {
            leftValue = *leftIterator;
            ++leftIterator;
        }

        int rightValue = 0;
        if (rightIterator != right.end()) {
            rightValue = *rightIterator;
            ++rightIterator;
        }

        distance += std::abs(leftValue - rightValue);
    }

	return distance;
}