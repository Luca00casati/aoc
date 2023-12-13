#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int registerA = 0;
int registerB = 0;
vector<string> instructions;
string line;

bool programFinished = false;
int instructionCount = 0;

void half(char Register) {
	if (Register == 'a') {
		registerA = registerA / 2;
	}
	else if (Register == 'b') {
		registerB = registerB / 2;
	}
}

void triple(char Register) {
	if (Register == 'a') {
		registerA = registerA * 3;
	}
	else if (Register == 'b') {
		registerB = registerB * 3;
	}
}

void increment(char Register) {
	if (Register == 'a') {
		registerA += 1;
	}
	else if (Register == 'b') {
		registerB += 1;
	}
}

void jumpIfEven(char Register, int offset) {
	if (Register == 'a') {
		if (registerA % 2 == 0) {
			instructionCount += offset;
		}
		else {
			instructionCount++;
		}
	}
	else if (Register == 'b') {
		if (registerB % 2 == 0) {
			instructionCount += offset;
		}
		else {
			instructionCount++;
		}
	}
}

void jumpIfOne(char Register, int offset) {
	if (Register == 'a') {
		if (registerA == 1) {
			instructionCount += offset;
		}
		else {
			instructionCount++;
		}
	}
	else if (Register == 'b') {
		if (registerB == 1) {
			instructionCount += offset;
		}
		else {
			instructionCount++;
		}
	}
}

void readFile(string filename) {
	ifstream myFile(filename);

	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{
			instructions.push_back(line);
		}
		myFile.close();
	}
	else
	{
		cout << "Unable to open file";
	}
}

int main() {
	readFile("day23.txt");

	while (!programFinished) {
		string instruction = instructions[instructionCount].substr(0, 3);
		if (instruction == "hlf") {
			char Register = instructions[instructionCount].at(4);
			half(Register);
			instructionCount++;
		}
		else if (instruction == "tpl") {
			char Register = instructions[instructionCount].at(4);
			triple(Register);
			instructionCount++;
		}
		else if (instruction == "inc") {
			char Register = instructions[instructionCount].at(4);
			increment(Register);
			instructionCount++;
		}
		else if (instruction == "jmp") {
			int jumpValue = stoi(instructions[instructionCount].substr(4, 3));
			instructionCount += jumpValue;
		}
		else if (instruction == "jie") {
			char Register = instructions[instructionCount].at(4);
			int jumpValue = stoi(instructions[instructionCount].substr(7, 3));
			jumpIfEven(Register, jumpValue);
		}
		else if (instruction == "jio") {
			char Register = instructions[instructionCount].at(4);
			int jumpValue = stoi(instructions[instructionCount].substr(7, 3));
			jumpIfOne(Register, jumpValue);
		}

		if (instructionCount == instructions.size()) {
			programFinished = true;
		}
	}

	cout << "Register A: " << registerA << endl;
	cout << "Register B: " << registerB << endl;
}