#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

bool contains_red(const json& data) {
    if (data.is_object()) {
        for (const auto& [key, value] : data.items()) {
            if (value.is_string() && value.get<std::string>() == "red") {
                return true; // Ignore the entire object if it contains "red"
            }
        }
    }
    return false;
}

int sum_numbers(const json& data) {
    if (contains_red(data)) {
        return 0; // Ignore the entire object
    }

    if (data.is_number()) {
        return data.get<int>();
    } else if (data.is_array()) {
        int sum = 0;
        for (const auto& item : data) {
            sum += sum_numbers(item);
        }
        return sum;
    } else if (data.is_object()) {
        int sum = 0;
        for (const auto& [key, value] : data.items()) {
            sum += sum_numbers(value);
        }
        return sum;
    } else {
        return 0;
    }
}

int main() {
    std::ifstream file("day12.json");

    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    json json_document;
    file >> json_document;
    file.close();

    int result = sum_numbers(json_document);

    std::cout << "Sum of all numbers (ignoring red objects): " << result << std::endl;

    return 0;
}
