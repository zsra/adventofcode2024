#include <string>
#include <regex>

#include "Day3.h"

int getEnabledResultFromInstructions(const std::string& instructions) {
    int calulatedValueFromInstructions = 0;
    bool shouldProcess = true;

    std::regex pattern(R"((do\(\)|don't\(\))|mul\(([-+]?\d+)\s*,\s*([-+]?\d+)\))");
    std::smatch matches;
    std::sregex_iterator begin = std::sregex_iterator(instructions.begin(), instructions.end(), pattern);
    std::sregex_iterator end = std::sregex_iterator();

    for (std::sregex_iterator& index = begin; index != end; index++) {
        std::smatch match = *index;

        if (match[1].matched) {
            shouldProcess = (match[1].str() == "do()");
            continue;
        }

        if (shouldProcess) {
            int firstNumber = std::stoi(match[2].str());
            int secondNumber = std::stoi(match[3].str());

            calulatedValueFromInstructions += firstNumber * secondNumber;
        }
    }

    return calulatedValueFromInstructions;
}