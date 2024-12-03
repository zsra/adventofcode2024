#include <string>
#include <regex>

#include "Day3.h"

int getResultFromInstructions(const std::string& instructions) {
	int calulatedValueFromInstructions = 0;
	
	std::regex pattern(R"(mul\(([-+]?\d*\.?\d+),([-+]?\d*\.?\d+)\))");
	std::smatch matches;
	auto begin = std::sregex_iterator(instructions.begin(), instructions.end(), pattern);
	auto end = std::sregex_iterator();

	for (std::sregex_iterator i = begin; i != end; ++i) {
		std::smatch match = *i;

		int firstNumber = std::stoi(match[1].str());
		int secondNumber = std::stoi(match[2].str());

		calulatedValueFromInstructions += (firstNumber * secondNumber);
	}

	return calulatedValueFromInstructions;
}