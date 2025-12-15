#include "Day6Solution.h"

#include <iostream>
#include <ostream>
#include <sstream>
#include <bits/locale_facets_nonio.h>

using namespace std;

namespace Day6 {

    void readLines(const vector<string>& lines, vector<vector<int>>& numbers, vector<char>& symbols) {
        for (int i = 0; i < lines.size(); i++) {
            const string& line = lines[i];
            istringstream iss(line);
            if (line[0] == '+'|| line[0] == '*') {
                char symbol;
                while (iss >> symbol) {
                    symbols.push_back(symbol);
                }
            } else {
                int number;
                while (iss >> number) {
                    numbers[i].push_back(number);
                }
            }
        }
    }

    long long add(long long a, long long b) {
        return a + b;
    }

    long long mul(long long a, long long b) {
        return a * b;
    }

    string solve1(const vector<string>& input) {
        vector<vector<int>> numbers(input.size() - 1, vector<int>());
        vector<char> symbols;
        readLines(input, numbers, symbols);
        long long sum = 0;
        for (int i = 0; i < symbols.size(); i++) {
            long long auxSum;
            char symbol = symbols[i];
            long long (*op)(long long, long long);
            switch (symbol) {
                case '+':
                    op = add;
                    auxSum = 0;
                    break;
                case '*':
                    op = mul;
                    auxSum = 1;
                    break;
                default:
                    throw runtime_error("Unrecognized symbol '" + string(1, symbol) + "'");
            }
            for (int j = 0; j < numbers.size(); j++) {
                auxSum = op(auxSum, numbers[j][i]);
            }
            sum += auxSum;
        }
        return to_string(sum);
    }

    string solve2(const vector<string>& input) {
        vector<vector<int>> numbers(input.size() - 1, vector<int>());
        vector<char> symbols;
        readLines(input, numbers, symbols);
        long long sum = 0;
        for (int i = 0; i < symbols.size(); i++) {
            long long auxSum;
            char symbol = symbols[i];
            long long (*op)(long long, long long);
            switch (symbol) {
                case '+':
                    op = add;
                    auxSum = 0;
                    break;
                case '*':
                    op = mul;
                    auxSum = 1;
                    break;
                default:
                    throw runtime_error("Unrecognized symbol '" + string(1, symbol) + "'");
            }
            for (int j = 0; j < numbers.size(); j++) {
                auxSum = op(auxSum, numbers[j][i]);
            }
            sum += auxSum;
        }
        return to_string(sum);
    }
}