// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include<fstream>
#include "grid.h"
#include "lifeutil.h"
#include <string>

using namespace std;
string askForFile();
void printFile(string fileName);

int main() {

    cout << "Welcome to the TDDD86 Game of Life,"  << endl;
    cout << "a simulation of the lifecycle of a bacteria colony."  << endl;
    cout << "Cells (X) live and die by the following rules:"  << endl;
    cout << " - A cell with 1 or fewer neighbours dies."  << endl;
    cout << " - Locations with 2 with neighbours remain stable."  << endl;
    cout << " - Locations with 3 with neighbours will create life."  << endl;
    cout << " - A cell with 4 or more neighbours dies."  << endl;

    string fileName = askForFile();
    printFile(fileName);
    return 0;
}

string askForFile() {
    string fileName;
    cout << "Grid input file name? ";
    cin >> fileName;
    return fileName;
}

void printFile(string fileName) {
    ifstream input;
    input.open(fileName.c_str());
    string line;
    while (getline(input, line)) {
        cout << line << endl;
    }
    input.close();
}
