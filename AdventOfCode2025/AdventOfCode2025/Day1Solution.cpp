#include "Day1Solution.h"

#include <charconv>

using namespace std;

string Day1Solution::solve1(vector<string> input)
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

string Day1Solution::solve2(vector<string> input)
{
	int rotationValue = 50;
	int numberOfTimesThatZero = 0;
	bool prevWasZero = false;
	for (string line : input) {
		int newRotationValue = 0;

		from_chars(line.data() + 1, line.data() + line.size(), newRotationValue);

		if (line[0] == 'L') {
			rotationValue -= newRotationValue;
		} else {
			rotationValue += newRotationValue;
		}

		if (rotationValue > 100) {
			numberOfTimesThatZero += rotationValue / 100;
		} else if (rotationValue < 0) {
			numberOfTimesThatZero += rotationValue / 100 + (prevWasZero ? 0 : 1);
		}

		rotationValue = (rotationValue % 100 + 100) % 100;
		if (rotationValue == 0) {
			numberOfTimesThatZero++;
			prevWasZero = true;
		} else {
			prevWasZero = false;
		}
	}
	return to_string(numberOfTimesThatZero);
}
