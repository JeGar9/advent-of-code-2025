#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Day1/Day1Solution.h"
#include "Day2/Day2Solution.h"
#include "Day3/Day3Solution.h"
#include "Day4/Day4Solution.h"
#include "Day5/Day5Solution.h"


std::vector<std::string> readFileLines(const std::string &filename) {
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
            result1 = Day1::solve1(fileLines);
            result2 = Day1::solve2(fileLines);
            break;
        case 2:
            result1 = Day2::solve1(fileLines);
            result2 = Day2::solve2(fileLines);
            break;
        case 3:
            result1 = Day3::solve1(fileLines);
            result2 = Day3::solve2(fileLines);
            break;
        case 4:
            result1 = Day4::solve1(fileLines);
            result2 = Day4::solve2(fileLines);
            break;
        case 5:
            result1 = Day5::solve1(fileLines);
            result2 = Day5::solve2(fileLines);
            break;
        default:
            break;
    }

    std::cout << "Part 1: " << result1 << std::endl;
    std::cout << "Part 2: " << result2 << std::endl;
}
