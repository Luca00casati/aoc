#include <iostream>
#include <string>

int count_next(const std::string& input) {
    int i = 0;
    int count = 1;
    while (i < input.length() - 1 && input[i] == input[i + 1]) {
        count++;
        i++;
    }
    return count;
}

std::string transformation(const std::string& input) {
    std::string res;
    for (size_t i = 0; i < input.length(); i++) {
        int count = count_next(input.substr(i));
        res += std::to_string(count) + input[i];
        i += count - 1;
    }
    return res;
}

std::string for_transformation(const std::string& input, const int& val){
    std::string for_input = input;
    for (unsigned long i = 0; i < val; i++){
        std::cout << i << std::endl;
        for_input = transformation(for_input);
    }
    return for_input;
}

int main() {
    std::string val = "1321131112";
    std::string lenght = for_transformation(val, 50);
    std::cout << lenght.length() << std::endl;
    return 0;
}
//6989950