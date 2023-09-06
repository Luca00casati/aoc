#include <iostream>
#include <string>
#include <fstream>
//#include <sstream>
using namespace std;

bool vocali_test(string parola){
    string vocali = "aieou";
    int n_vocali = 0;
    for (int j = 0; j < vocali.size();j++){
    for (int i = 0; i < parola.size();i++){
        if (parola[i] == vocali[j]){
            //cout << "successo" << endl;
            n_vocali++;
        }
        else{
            continue;
        }
        
    }
    }
    if (n_vocali >= 3){
        return true;
    }
    else{
        return false;
    }
}

bool row_test(string parola){
    int n_row = 0;
    for (int i = 0; i < parola.size();i++){
        if (parola[i] == parola[i+1]){
            n_row++;
        }
        else{
            continue;
        }
    }

    if (n_row >= 1){
        return true;
    }
    else{
        return false;
    }

}

bool forbidden_test(string parola){
    // List of forbidden strings
    string forbiddenStrings[] = {"ab", "cd", "pq", "xy"};

    // Check if the input string contains any of the forbidden substrings
    for (const string& forbidden : forbiddenStrings) {
        if (parola.find(forbidden) != string::npos) {
            return false; 
        }
    }

    return true;
}

int main(){
    int nice = 0;
    ifstream MyReadFile("day5.txt");

    if (!MyReadFile.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    std::string line;

    while (getline(MyReadFile, line)) {
        if (forbidden_test(line) && row_test(line) && vocali_test(line)){
            nice++;
        }
        

        // Write the result to the output file
    }
    cout << "nice: " << nice << endl;
    // Close the files after processing
    //MyFile2.close();
    MyReadFile.close();

    return 0;
}