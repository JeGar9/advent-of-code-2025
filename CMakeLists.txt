cmake_minimum_required(VERSION 4.0)
project(AdventOfCode_2025)

set(CMAKE_CXX_STANDARD 14)

include_directories(AdventOfCode2025/Day1)
include_directories(AdventOfCode2025/Day2)

add_executable(AdventOfCode_2025
        AdventOfCode2025/Day1/Day1Solution.cpp
        AdventOfCode2025/Day2/Day2Solution.cpp
        AdventOfCode2025/Program.cpp
        AdventOfCode2025/util/ULongTrie.cpp
        AdventOfCode2025/Day3/Day3Solution.cpp
        AdventOfCode2025/Day4/Day4Solution.cpp
        AdventOfCode2025/Day5/Day5Solution.cpp)

target_include_directories(AdventOfCode_2025 PRIVATE AdventOfCode2025/util)

