//length l, width w, and height h
//2*l*w + 2*w*h + 2*h*l
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

void mymin2(int a, int b, int c, int arr[]){
    int i = min(a , min(b, c));
    arr[0] = i;
    if (i == a){
        arr[1] = min(b, c);
    }
    else if (i == c){
        arr[1] = min(b, a);
    }
    else if (i == b){
        arr[1] = min(a, c);
    }

}
int calculator(string dimension){
    int arr[2];
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
         mymin2(l,w,h, arr);
        int min1 = arr[0];
        int min2 = arr[1];
        int result = min1*2+min2*2+l*w*h;
        return result;
    }
    else{
        return 1;
    }
}
int main(){
    auto result2 = 0;
    ofstream MyFile("day2_2calc.txt");
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
    ifstream MyReadFile2("day2_2calc.txt");

    if (!MyReadFile2.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    std::string line2;

    while (getline(MyReadFile2, line2)) {
        result2 += stoi(line2);

        // Write the result to the output file
    }
    cout << "ribbon: " << result2 << endl;
    // Close the files after processing
    //MyFile2.close();
    MyReadFile2.close();


    return 0;
}