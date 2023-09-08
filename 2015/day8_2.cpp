#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream input("day8.txt");
    string line;
    int totalCodeChars = 0;
    int totalEncodedChars = 0;

    while (getline(input, line)) {
        totalCodeChars += line.size();

        int encodedChars = 2;
        for (char c : line) {
            if (c == '\\' || c == '"') {
                encodedChars += 2;
            } else {
                encodedChars++;
            }
        }

        totalEncodedChars += encodedChars;
    }

    int result = totalEncodedChars - totalCodeChars;
    cout << "Result: " << result << endl;

    input.close();
    return 0;
}
