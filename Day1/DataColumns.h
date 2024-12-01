#ifndef DATACOLUMNS_H
#define DATACOLUMNS_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>

class DataColumns {
private:
    std::multiset<int> left;
    std::multiset<int> right;

public:
    bool loadFromFile(const std::string& filename);
    const std::multiset<int>& getLeft() const;
    const std::multiset<int>& getRight() const;
};

#endif // DATACOLUMNS_H
