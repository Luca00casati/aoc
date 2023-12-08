#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int input = 29000000;

void partOne() {
	vector<int> houses(input / 10 + 1);

	for (int elf = 1; elf < input / 10; elf++) {
		for (int house = elf; house < input / 10; house += elf) {
			houses[house] += elf * 10;
		}
	}

	for (int house = 1; house < input / 10; house++) {
		if (houses[house] >= input) {
			cout << "Part 1: " << house << endl;
			break;
		}
	}	
}

void partTwo() {
	vector<int> housesTwo(input / 11 + 1);

	for (int elf = 1; elf < input / 11; elf++) {
		for (int house = elf, houseCount = 0; house < input / 11 && houseCount < 50; house += elf, houseCount++) {
			housesTwo[house] += elf * 11;
		}
	}

	for (int house = 1; house < input / 11; house++) {
		if (housesTwo[house] >= input) {
			cout << "Part 2: " << house << endl;
			break;
		}
	}
}

int main() {
	partOne();
	partTwo();
}