#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

struct CityData {
    string source;
    string destination;
    int distance;
};

void readData(ifstream& input, unordered_map<string, unordered_map<string, int>>& dataMap, vector<string>& cities, vector<int>& minDistances) {
    string line;
    while (getline(input, line)) {
        string separator1 = " to ";
        size_t pos = line.find(separator1);
        string source = line.substr(0, pos);
        string line_part2 = line.substr(pos + separator1.length());
        string separator2 = " = ";
        pos = line_part2.find(separator2);
        string destination = line_part2.substr(0, pos);
        string distance_str = line_part2.substr(pos + separator2.length());
        int distance = stoi(distance_str);

        CityData data;
        data.source = source;
        data.destination = destination;
        data.distance = distance;

        dataMap[data.source][data.destination] = data.distance;
        dataMap[data.destination][data.source] = data.distance;

        if (cities.empty()) {
            cities.push_back(source);
        } else if (find(cities.begin(), cities.end(), source) == cities.end()) {
            cities.push_back(source);
        }

        if (find(cities.begin(), cities.end(), destination) == cities.end()) {
            cities.push_back(destination);
        }
    }
}

int calculateDistance(const vector<string>& route, const unordered_map<string, unordered_map<string, int>>& dataMap) {
    int distance = 0;
    for (size_t i = 0; i < route.size() - 1; i++) {
        distance += dataMap.at(route[i]).at(route[i + 1]);
    }
    return distance;
}

int main() {
    ifstream input("day9.txt");
    if (!input.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    vector<string> cities;
    vector<int> minDistances;
    vector<int>maxDistances;
    unordered_map<string, unordered_map<string, int>> dataMap;

    readData(input, dataMap, cities, minDistances);

    sort(cities.begin(), cities.end());

    do {
        for (const auto& city : cities) {
            cout << city << " ";
        }
        cout << endl;

        int distance = calculateDistance(cities, dataMap);
        cout << distance << endl;
        minDistances.push_back(distance);
        maxDistances.push_back(distance);
    } while (next_permutation(cities.begin(), cities.end()));

    cout << "Min Distance: " << *min_element(minDistances.begin(), minDistances.end()) << endl;
    cout << "Max Distance: " << *max_element(maxDistances.begin(), maxDistances.end()) << endl;

    return 0;
}
