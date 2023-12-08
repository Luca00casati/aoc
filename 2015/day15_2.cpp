#include <iostream>
#include <vector>
#include <algorithm>

struct Ingredient {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
};

int calculateScore(const std::vector<Ingredient>& ingredients, const std::vector<int>& amounts) {
    int capacity = 0, durability = 0, flavor = 0, texture = 0, calories = 0;

    for (size_t i = 0; i < ingredients.size(); ++i) {
        capacity += amounts[i] * ingredients[i].capacity;
        durability += amounts[i] * ingredients[i].durability;
        flavor += amounts[i] * ingredients[i].flavor;
        texture += amounts[i] * ingredients[i].texture;
        calories += amounts[i] * ingredients[i].calories;
    }

    capacity = std::max(0, capacity);
    durability = std::max(0, durability);
    flavor = std::max(0, flavor);
    texture = std::max(0, texture);

    if (calories == 500) {
        int totalScore = capacity * durability * flavor * texture;
        return totalScore;
    } else {
        return 0; 
    }
}

int findHighestScore(const std::vector<Ingredient>& ingredients, std::vector<int>& amounts, int remainingTeaspoons, int index = 0) {
    if (index == ingredients.size() - 1) {
        amounts[index] = remainingTeaspoons;
        int score = calculateScore(ingredients, amounts);
        return score;
    }

    int highestScore = 0;
    for (int i = 0; i <= remainingTeaspoons; ++i) {
        amounts[index] = i;
        int score = findHighestScore(ingredients, amounts, remainingTeaspoons - i, index + 1);
        highestScore = std::max(highestScore, score);
    }

    return highestScore;
}

int main() {
    std::vector<Ingredient> ingredients = {
        {3, 0, 0, -3, 2},
        {-3, 3, 0, 0, 9},
        {-1, 0, 4, 0, 1},
        {0, 0, -2, 2, 8}
    };

    std::vector<int> amounts(ingredients.size(), 0);
    int highestScore = findHighestScore(ingredients, amounts, 100);

    std::cout << "The total score of the highest-scoring cookie with a calorie total of 500 is: " << highestScore << std::endl;

    return 0;
}
