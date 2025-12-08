#include "Day1Solution.h"

#include <charconv>
#include <iostream>

using namespace std;

namespace Day1 {

	string solve1(const vector<string>& input)
	{
		int rotationValue = 50;
		int numberOfTimesThatZero = 0;

		for (string line : input) {
			int newRotationValue = 0;
			from_chars(line.data() + 1, line.data() + line.size(), newRotationValue);
			if (line[0] == 'L') {
				rotationValue -= newRotationValue;
			} else {
				rotationValue += newRotationValue;
			}
			rotationValue = (rotationValue % 100 + 100) % 100;
			if (rotationValue == 0) {
				numberOfTimesThatZero++;
			}
		}
		return to_string(numberOfTimesThatZero);
	}

	string solve2(const vector<string>& input)
	{
		int rotationValue = 50;
		int numberOfTimesThatZero = 0;
		bool prevWasZero = false;
		cout << "Dial:" << rotationValue << " Zeros:" << numberOfTimesThatZero << endl;
		for (string line : input) {
			int newRotationValue = 0;
			from_chars(line.data() + 1, line.data() + line.size(), newRotationValue);
			if (line[0] == 'L') {
				rotationValue -= newRotationValue;
			} else {
				rotationValue += newRotationValue;
			}

			if (rotationValue > 99) {
				numberOfTimesThatZero += rotationValue / 100;
			} else if (rotationValue < 0) {
				numberOfTimesThatZero += (-rotationValue) / 100 + (prevWasZero ? 0 : 1);
			} else if (rotationValue == 0) {
				numberOfTimesThatZero++;
			}

			rotationValue = (rotationValue % 100 + 100) % 100;
			if (rotationValue == 0) {
				prevWasZero = true;
			} else {
				prevWasZero = false;
			}
			cout << "Dial:" << line << " Rotation:" << rotationValue << " Zeros:" << numberOfTimesThatZero << endl;
		}
		return to_string(numberOfTimesThatZero);
	}

}