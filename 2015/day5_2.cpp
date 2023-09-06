#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to check for repeated pairs of characters in a string.
bool hasRepeatedPairs(const string& word) {
    for (size_t i = 0; i < word.size() - 1; ++i) {
        for (size_t j = i + 2; j < word.size() - 1; ++j) {
            if (word[i] == word[j] && word[i + 1] == word[j + 1]) {
                return true;
            }
        }
    }
    return false;
}

// Function to check for overlapping characters in a string (e.g., "aaa").
bool hasOverlappingChars(const string& word) {
    for (size_t i = 0; i < word.size() - 2; ++i) {
        if (word[i] == word[i + 2]) {
            return true;
        }
    }
    return false;
}

// Function to check for pairs of characters with one character in between (e.g., "xyx").
bool hasRepeatingPairWithOneCharInBetween(const string& word) {
    for (size_t i = 0; i < word.size() - 2; ++i) {
        if (word[i] == word[i + 2]) {
            return true;
        }
    }
    return false;
}

int main() {
    int niceCount = 0;
    ifstream inputFile("day5.txt");

    if (!inputFile.is_open()) {
        cerr << "Error opening the input file." << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line)) {
        if (hasRepeatingPairWithOneCharInBetween(line) && hasOverlappingChars(line) && hasRepeatedPairs(line)) {
            niceCount++;
        }
    }

    inputFile.close();

    cout << "Number of nice lines: " << niceCount << endl;

    return 0;
}
