#include "Day3Solution.h"

using namespace std;



namespace Day3 {

    int getMaxValueFromCharacters(const string & str) {
        const char* cstr = str.c_str();
        size_t size = str.size();
        char maxFirstChar = '0';
        int maxIndex = 0;
        for (int i = 0; i < size - 1; i++) {
            char currentChar = cstr[i];
            if (currentChar > maxFirstChar) {
                maxFirstChar = currentChar;
                maxIndex = i;
            }
        }
        char maxSecondChar = '0';
        for (int i = maxIndex + 1; i < size; i++) {
            char currentChar = cstr[i];
            if (currentChar > maxSecondChar) {
                maxSecondChar = currentChar;
            }
        }
        return (maxFirstChar - '0') * 10 + (maxSecondChar - '0');
    }

    std::string solve1(const std::vector<std::string>& input) {
        int counter = 0;
        for (auto& str : input) {
            counter += getMaxValueFromCharacters(str);
        }
        return to_string(counter);
    }

    long long getMaxValueFrom12Characters(const string & str) {
        const int NUM_C = 12;

        const char* cstr = str.c_str();
        size_t size = str.size();

        char maxChar[NUM_C] = { 0 };
        int prevIndex = -1;

        for (int c = NUM_C - 1; c >= 0; c--) {
            for (int i = prevIndex + 1; i < size - c; i++) {
                char currentChar = cstr[i];
                if (currentChar > maxChar[c]) {
                    maxChar[c] = currentChar;
                    prevIndex = i;
                }
            }
        }
        long long value = 0;
        for (int c = NUM_C - 1; c >= 0; c--) {
            value *= 10;
            value += maxChar[c] - '0';
        }
        return value;
    }


    std::string solve2(const std::vector<std::string>& input) {
        long long counter = 0;
        for (auto& str : input) {
            counter += getMaxValueFrom12Characters(str);
        }
        return to_string(counter);
    }
}