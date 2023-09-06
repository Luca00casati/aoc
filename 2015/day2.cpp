//length l, width w, and height h
//2*l*w + 2*w*h + 2*h*l
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

int mymin(int a, int b, int c){
    return min(a , min(b, c));
}

int calculator(string dimension){
    //string dimension = "11x1x10";
    istringstream dimensionStream(dimension);
    string token;
    vector<int> dimensions;

    while (getline(dimensionStream, token, 'x')) {
        int dimensionValue = stoi(token);
        dimensions.push_back(dimensionValue);
    }

    // Check if there are three dimensions
    if (dimensions.size() == 3) {
        int l = dimensions[0];
        int w = dimensions[1];
        int h = dimensions[2]; 
        int lw = l*w;
        int wh = w*h;
        int hl = h*l; 
        int slack = mymin(lw, wh, hl);
        int formula = 2*lw + 2*wh + 2*hl;
        int result = formula+slack;
        return result;
    }
    else{
        return 1;
    }
}
int main(){
    auto result2 = 0;
    ofstream MyFile("day2calc.txt");
    ifstream MyReadFile("day2.txt");

    if (!MyFile.is_open() || !MyReadFile.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    std::string line;

    while (getline(MyReadFile, line)) {
        int result = calculator(line);

        // Write the result to the output file
        MyFile << result << endl;
    }

    // Close the files after processing
    MyFile.close();
    MyReadFile.close();
    //part2
    //ofstream MyFile2("day2res.txt");
    ifstream MyReadFile2("day2calc.txt");

    if (!MyReadFile2.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    std::string line2;

    while (getline(MyReadFile2, line2)) {
        result2 += stoi(line2);

        // Write the result to the output file
    }
    cout << "paper: " << result2 << endl;
    // Close the files after processing
    //MyFile2.close();
    MyReadFile2.close();

    return 0;
}