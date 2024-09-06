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
void readFile(string fileName, Grid<char> &grid);
void printGrid(const Grid<char> &grid);


int main() {

    cout << "Welcome to the TDDD86 Game of Life,"  << endl;
    cout << "a simulation of the lifecycle of a bacteria colony."  << endl;
    cout << "Cells (X) live and die by the following rules:"  << endl;
    cout << " - A cell with 1 or fewer neighbours dies."  << endl;
    cout << " - Locations with 2 with neighbours remain stable."  << endl;
    cout << " - Locations with 3 with neighbours will create life."  << endl;
    cout << " - A cell with 4 or more neighbours dies."  << endl;

    string fileName = askForFile();

    Grid<char> grid;

    readFile(fileName, grid);

    printGrid(grid);

    return 0;
}

string askForFile() {
    string fileName;
    cout << "Grid input file name? ";
    cin >> fileName;
    return fileName;
}

void readFile (string fileName, Grid<char> &grid){
    ifstream input;
    input.open(fileName.c_str());
    int numRows, numCols;

    // Read the first two lines for the grid dimensions
    input >> numRows >> numCols;

    grid.resize(numRows, numCols);

    char cell;

    for(int y = 0; y < numRows; y++){
        for(int x = 0; x < numCols; x++){
            input >> cell;
            grid.set(y,x,cell);
        }
    }
}

void printGrid(const Grid<char> &grid){
    for(int y = 0; y < grid.numRows(); y++){
        for(int x = 0; x < grid.numCols(); x++){
            cout << grid[y][x];
        }
        cout << endl;
    }
}

/*void printFile(string fileName) {
    ifstream input;
    input.open(fileName.c_str());
    string line;
    while (getline(input, line)) {        
        cout << line << endl;
    }
    input.close();
}*/
