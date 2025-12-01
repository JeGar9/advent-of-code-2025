#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Day1Solution.h"


std::vector<std::string> readFileLines(const std::string& filename) {
	std::ifstream file(filename);
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(file, line)) {
		lines.push_back(line);
	}
	return lines;
}

int main(int argc, char *argv[]) {

	int problem = atoi(argv[1]);
	std::string result1;
	std::string result2;

	std::vector<std::string> fileLines = readFileLines(argv[2]);

	switch (problem) {
	case 1:
		Day1Solution solution;
		result1 = solution.solve1(fileLines);
		result2 = solution.solve2(fileLines);
		break;
	default:
		break;
	}

	std::cout << "Part 1: " << result1 << std::endl;
	std::cout << "Part 2: " << result2 << std::endl;
}