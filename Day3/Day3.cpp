#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Day3.h"

static std::string readInstructions(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Failed to open the file." << std::endl;
        return "";
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();

    file.close();

    return buffer.str();
}

int main()
{
    std::string insturctions = readInstructions("instructions.in");

    int answer1 = getResultFromInstructions(insturctions);
    std::cout << "Answer #1: " << answer1 << "\n";

    int answer2 = getEnabledResultFromInstructions(insturctions);
    std::cout << "Answer #2: " << answer2 << "\n";
}
