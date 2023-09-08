#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream input("day8.txt");
    string line;
    int totalCodeChars = 0;
    int totalMemoryChars = 0;

    while (getline(input, line)) {
        totalCodeChars += line.size();

        int memoryChars = 0;
        for (int i = 1; i < line.size() - 1; i++) {
            if (line[i] == '\\') {
                if (line[i + 1] == '\\' || line[i + 1] == '"') {
                    memoryChars++;
                    i++;
                } else if (line[i + 1] == 'x') {
                    memoryChars++;
                    i += 3; 
                }
            } else {
                memoryChars++;
            }
        }

        totalMemoryChars += memoryChars;
    }

    int result = totalCodeChars - totalMemoryChars;
    cout << "Result: " << result << endl;

    input.close();
    return 0;
}