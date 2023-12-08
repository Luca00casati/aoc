#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int count_neighbors(const vector<vector<char>>& grid, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue; 
            }
            int new_x = x + i;
            int new_y = y + j;
            if (new_x >= 0 && new_x < grid.size() && new_y >= 0 && new_y < grid[0].size()) {
                count += grid[new_x][new_y] == '#';
            }
        }
    }
    return count;
}

vector<vector<char>> update_grid(const vector<vector<char>>& grid) {
    vector<vector<char>> new_grid(grid.size(), vector<char>(grid[0].size(), '.'));
    for (int x = 0; x < grid.size(); ++x) {
        for (int y = 0; y < grid[0].size(); ++y) {
            int neighbors_on = count_neighbors(grid, x, y);
            if ((x == 0 || x == grid.size() - 1) && (y == 0 || y == grid[0].size() - 1)) {
                new_grid[x][y] = '#';
            } else if (grid[x][y] == '#' && neighbors_on != 2 && neighbors_on != 3) {
                new_grid[x][y] = '.';
            } else if (grid[x][y] == '.' && neighbors_on == 3) {
                new_grid[x][y] = '#';
            } else {
                new_grid[x][y] = grid[x][y];
            }
        }
    }
    return new_grid;
}


void print_grid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char cell : row) {
            cout << cell;
        }
        cout << endl;
    }
    cout << endl;
}

int count_lights_on(const vector<vector<char>>& grid) {
    int count = 0;
    for (const auto& row : grid) {
        count += std::count(row.begin(), row.end(), '#');
    }
    return count;
}

int main() {
    ifstream file("day18.txt");
    vector<vector<char>> initial_grid;
    string line;
    while (getline(file, line)) {
        initial_grid.push_back(vector<char>(line.begin(), line.end()));
    }

    for (int step = 0; step < 100; ++step) {
        initial_grid = update_grid(initial_grid);
    }

    int result = count_lights_on(initial_grid);
    cout << result << endl;

    return 0;
}
