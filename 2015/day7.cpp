#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>


using namespace std;

vector<pair<string, unsigned short>> mainvec;
vector<string> instructions;
int ciclo = 0;

unsigned short stringToUnShort(const string& str) {
    stringstream ss(str);
    unsigned short result;
    ss >> result;
    return result;
}

unsigned short getValueInVec(const string& target) {
    for (auto &pair : mainvec) {
        if (pair.first == target) {
            return pair.second;
        }
    }
    return 0;
}

bool SearchinVec(const string& target) {
    for (auto &pair : mainvec) {
        if (pair.first == target) {
            return true;
        }
    }
    return false;
}

vector<string> splitByString(const string &input, const string& token) {
    string cleanInput = "";
    for (char c : input) {
        if (!isspace(c)) {
            cleanInput += c;
        }
    }

    vector<string> parts;
    size_t startPos = 0;

    while (startPos < cleanInput.length()) {
        size_t foundPos = cleanInput.find(token, startPos);
        if (foundPos != string::npos) {
            parts.push_back(cleanInput.substr(startPos, foundPos - startPos));
            startPos = foundPos + token.length();
        } else {
            parts.push_back(cleanInput.substr(startPos));
            break;
        }
    }

    return parts;
}

bool no_key_check(const string& parola) {
    string forbiddenStrings[] = {"NOT", "LSHIFT", "RSHIFT", "AND", "OR"};
    for (const string &forbidden : forbiddenStrings) {
        if (parola.find(forbidden) != string::npos) {
            return false;
        }
    }
    return true;
}

bool key_specific_check(const string& parola, const string& token) {
    if (parola.find(token) != string::npos) {
        return true;
    }
    return false;
}

bool is_number(const string &parola) {
    for (char c : parola) {
        if (isdigit(c)) {
            return true;
        }
    }
    return false;
}

bool insertvec(const string& input) {
    vector<string> parts = splitByString(input, "->");
    string ress = parts[1];
    string op1 = parts[0];

    if (is_number(op1)) {
        unsigned short resv = stringToUnShort(op1);
        if (SearchinVec(ress)) {
            for (auto &pair : mainvec) {
                if (pair.first == ress) {
                    pair.second = resv;
                    break;
                }
            }
        } else {
            mainvec.push_back(make_pair(ress, resv));
        }

        return true;
    } else if (SearchinVec(op1)) {
        unsigned short resv = getValueInVec(op1);
        if (SearchinVec(ress)) {
            for (auto &pair : mainvec) {
                if (pair.first == ress) {
                    pair.second = resv;
                    break;
                }
            }
        } else {
            mainvec.push_back(make_pair(ress, resv));
        }

        return true;
    }

    return false;
}

bool op_and(const string &str) {
    vector<string> parts1 = splitByString(str, "->");
    string ress = parts1[1];
    vector<string> parts2 = splitByString(parts1[0], "AND");
    string op1 = parts2[0];
    string op2 = parts2[1];

    if (!is_number(op1) && !is_number(op2)) {
        if (SearchinVec(op1) && SearchinVec(op2)) {
            unsigned short resv = getValueInVec(op1) & getValueInVec(op2);
            if (SearchinVec(ress)) {
                for (auto &pair : mainvec) {
                    if (pair.first == ress) {
                        pair.second = resv;
                        break;
                    }
                }
            } else {
                mainvec.push_back(make_pair(ress, resv));
            }
            return true;
        }
    } else if (!is_number(op1) && is_number(op2)) {
        if (SearchinVec(op1)) {
            unsigned short resv = getValueInVec(op1) & stringToUnShort(op2);
            if (SearchinVec(ress)) {
                for (auto &pair : mainvec) {
                    if (pair.first == ress) {
                        pair.second = resv;
                        break;
                    }
                }
            } else {
                mainvec.push_back(make_pair(ress, resv));
            }
            return true;
        }
    } else if (is_number(op1) && !is_number(op2)) {
        if (SearchinVec(op2)) {
            unsigned short resv = stringToUnShort(op1) & getValueInVec(op2);
            if (SearchinVec(ress)) {
                for (auto &pair : mainvec) {
                    if (pair.first == ress) {
                        pair.second = resv;
                        break;
                    }
                }
            } else {
                mainvec.push_back(make_pair(ress, resv));
            }
            return true;
        }
    }
    return false;
}

bool op_or(const string &str) {
    vector<string> parts1 = splitByString(str, "->");
    string ress = parts1[1];
    vector<string> parts2 = splitByString(parts1[0], "OR");
    string op1 = parts2[0];
    string op2 = parts2[1];

    if (!is_number(op1) && !is_number(op2)) {
        if (SearchinVec(op1) && SearchinVec(op2)) {
            unsigned short resv = getValueInVec(op1) | getValueInVec(op2);
            if (SearchinVec(ress)) {
                for (auto &pair : mainvec) {
                    if (pair.first == ress) {
                        pair.second = resv;
                        break;
                    }
                }
            } else {
                mainvec.push_back(make_pair(ress, resv));
            }
            return true;
        }
    } else if (!is_number(op1) && is_number(op2)) {
        if (SearchinVec(op1)) {
            unsigned short resv = getValueInVec(op1) | stringToUnShort(op2);
            if (SearchinVec(ress)) {
                for (auto &pair : mainvec) {
                    if (pair.first == ress) {
                        pair.second = resv;
                        break;
                    }
                }
            } else {
                mainvec.push_back(make_pair(ress, resv));
            }
            return true;
        }
    } else if (is_number(op1) && !is_number(op2)) {
        if (SearchinVec(op2)) {
            unsigned short resv = stringToUnShort(op1) | getValueInVec(op2);
            if (SearchinVec(ress)) {
                for (auto &pair : mainvec) {
                    if (pair.first == ress) {
                        pair.second = resv;
                        break;
                    }
                }
            } else {
                mainvec.push_back(make_pair(ress, resv));
            }
            return true;
        }
    }
    return false;
}

bool op_rshift(const string &str) {
    vector<string> parts1 = splitByString(str, "->");
    string ress = parts1[1];
    vector<string> parts2 = splitByString(parts1[0], "RSHIFT");
    string op1 = parts2[0];
    unsigned short op2 = stringToUnShort(parts2[1]);

    if (SearchinVec(op1)) {
        unsigned short resv = getValueInVec(op1) >> op2;
        if (SearchinVec(ress)) {
            for (auto &pair : mainvec) {
                if (pair.first == ress) {
                    pair.second = resv;
                    break;
                }
            }
        } else {
            mainvec.push_back(make_pair(ress, resv));
        }
        return true;
    }
    return false;
}

bool op_lshift(const string &str) {
    vector<string> parts1 = splitByString(str, "->");
    string ress = parts1[1];
    vector<string> parts2 = splitByString(parts1[0], "LSHIFT");
    string op1 = parts2[0];
    unsigned short op2 = stringToUnShort(parts2[1]);

    if (SearchinVec(op1)) {
        unsigned short resv = getValueInVec(op1) << op2;
        if (SearchinVec(ress)) {
            for (auto &pair : mainvec) {
                if (pair.first == ress) {
                    pair.second = resv;
                    break;
                }
            }
        } else {
            mainvec.push_back(make_pair(ress, resv));
        }
        return true;
    }
    return false;
}

bool op_not(const string &str) {
    vector<string> parts1 = splitByString(str, "->");
    string ress = parts1[1];
    vector<string> parts2 = splitByString(parts1[0], "NOT");
    string op1 = parts2[1];

    if (SearchinVec(op1)) {
        unsigned short resv = ~getValueInVec(op1);
        if (SearchinVec(ress)) {
            for (auto &pair : mainvec) {
                if (pair.first == ress) {
                    pair.second = resv;
                    break;
                }
            }
        } else {
            mainvec.push_back(make_pair(ress, resv));
        }
        return true;
    }
    return false;
}

int main() {
    mainvec.clear();

    ifstream inputFile("day7.txt");
    if (!inputFile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        instructions.push_back(line);
    }

    inputFile.close();

    while (!instructions.empty()) {
        bool operationSuccess = false;

        for (long unsigned ind = 0; ind < instructions.size();) {
            const string& instruction = instructions[ind];

            if (no_key_check(instruction)) {
                operationSuccess = insertvec(instruction);
            } else if (key_specific_check(instruction, "AND")) {
                operationSuccess = op_and(instruction);
            } else if (key_specific_check(instruction, "OR")) {
                operationSuccess = op_or(instruction);
            } else if (key_specific_check(instruction, "RSHIFT")) {
                operationSuccess = op_rshift(instruction);
            } else if (key_specific_check(instruction, "LSHIFT")) {
                operationSuccess = op_lshift(instruction);
            } else if (key_specific_check(instruction, "NOT")) {
                operationSuccess = op_not(instruction);
            }

            if (operationSuccess) {
                instructions.erase(instructions.begin() + ind);
                //ind++;
            } else {
                ind++;
            }

        }
        ciclo++;
    }

    for (const auto &pair : mainvec) {
        cout << pair.first << '=' << pair.second << endl;
    }

    cout << "cicli: " << ciclo << endl;

    return 0;
}