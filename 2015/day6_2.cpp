#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Initialize a 1000x1000 grid with all lights' brightness set to zero.
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
                    grid[x][y] += 2; // Increase brightness by 2.
                }
            }
        } else if ((pos = instruction.find("turn on")) != string::npos) {
            int start_x, start_y, end_x, end_y;
            sscanf(instruction.c_str(), "turn on %d,%d through %d,%d", &start_x, &start_y, &end_x, &end_y);
            for (int x = start_x; x <= end_x; x++) {
                for (int y = start_y; y <= end_y; y++) {
                    grid[x][y] += 1; // Increase brightness by 1.
                }
            }
        } else if ((pos = instruction.find("turn off")) != string::npos) {
            int start_x, start_y, end_x, end_y;
            sscanf(instruction.c_str(), "turn off %d,%d through %d,%d", &start_x, &start_y, &end_x, &end_y);
            for (int x = start_x; x <= end_x; x++) {
                for (int y = start_y; y <= end_y; y++) {
                    grid[x][y] = max(0, grid[x][y] - 1); // Decrease brightness, but not below 0.
                }
            }
        }
    }

    // Calculate the total brightness of all lights.
    int totalBrightness = 0;
    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            totalBrightness += grid[x][y];
        }
    }

    cout << "Total brightness of all lights: " << totalBrightness << endl;

    return 0;
}
