#include "DataColumns.h"

bool DataColumns::loadFromFile(const std::string& filename) {
    ifstream infile(filename);

    if (!infile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::size_t pos = line.find("   "); // Find the 3-space delimiter
        if (pos != std::string::npos) {
            try {
                // Extract and convert columns to numbers
                int col1 = std::stod(line.substr(0, pos)); // First column
                int col2 = std::stod(line.substr(pos + 3)); // Second column (skip 3 spaces)

                // Store numbers into the vectors
                left.insert(col1);
                right.insert(col2);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid number format in line: " << line << std::endl;
            }
        }
    }

    infile.close();
    return true;
}

const std::multiset<int>& DataColumns::getLeft() const {
    return left;
}

const std::multiset<int>& DataColumns::getRight() const {
    return right;
}