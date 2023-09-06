#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Initialize a 1000x1000 grid with all lights turned off (0 means off, 1 means on).
    vector<vector<int>> grid(1000, vector<int>(1000, 0));

    // Read the instructions from the "day6.txt" file.
    ifstream input("day6.txt");
    string instruction;

    while (getline(input, instruction)) {
        // Process each instruction one by one.
        size_t pos = 0;
        if ((pos = instruction.find("toggle")) != string::npos) {
            int start_x, start_y, end_x, end_y;
            sscanf(instruction.c_str(), "toggle %d,%d through %d,%d", &start_x, &start_y, &end_x, &end_y);
            for (int x = start_x; x <= end_x; x++) {
                for (int y = start_y; y <= end_y; y++) {
                    grid[x][y] = 1 - grid[x][y]; // Toggle the lights.
                }
            }
        } else if ((pos = instruction.find("turn on")) != string::npos) {
            int start_x, start_y, end_x, end_y;
            sscanf(instruction.c_str(), "turn on %d,%d through %d,%d", &start_x, &start_y, &end_x, &end_y);
            for (int x = start_x; x <= end_x; x++) {
                for (int y = start_y; y <= end_y; y++) {
                    grid[x][y] = 1;
                }
            }
        } else if ((pos = instruction.find("turn off")) != string::npos) {
            int start_x, start_y, end_x, end_y;
            sscanf(instruction.c_str(), "turn off %d,%d through %d,%d", &start_x, &start_y, &end_x, &end_y);
            for (int x = start_x; x <= end_x; x++) {
                for (int y = start_y; y <= end_y; y++) {
                    grid[x][y] = 0;
                }
            }
        }
    }

    // Count the number of lights that are turned on.
    int count = 0;
    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            count += grid[x][y];
        }
    }

    cout << "Number of lit lights: " << count << endl;

    return 0;
}
