#include <iostream>
#include <string>

bool isValidPassword(const std::string& password) {
    bool straight = false;
    for (int i = 0; i < password.length() - 2; ++i) {
        if (password[i] == password[i + 1] - 1 && password[i + 1] == password[i + 2] - 1) {
            straight = true;
            break;
        }
    }

    bool noForbiddenLetters = true;
    for (char letter : password) {
        if (letter == 'i' || letter == 'o' || letter == 'l') {
            noForbiddenLetters = false;
            break;
        }
    }

    bool twoDifferentPairs = false;
    int pairCount = 0;
    for (int i = 0; i < password.length() - 1; ++i) {
        if (password[i] == password[i + 1]) {
            ++pairCount;
            ++i;  // Skip the next character of the pair
        }
    }
    twoDifferentPairs = (pairCount >= 2);

    return straight && noForbiddenLetters && twoDifferentPairs;
}

std::string incrementPassword(std::string password) {
    int index = password.length() - 1;
    while (index >= 0) {
        if (password[index] == 'z') {
            password[index] = 'a';
            --index;
        } else {
            ++password[index];
            break;
        }
    }
    return password;
}

int main() {
    std::string currentPassword = "hxbxxyzz";

    do {
        currentPassword = incrementPassword(currentPassword);
    } while (!isValidPassword(currentPassword));

    std::cout << "Santa's next password: " << currentPassword << std::endl;

    return 0;
}
