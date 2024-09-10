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
int countNeighbours(int posY, int posX,const Grid<char> &grid);
void advanceGen(Grid<char> &grid);
char newCell(int neighbours, const char currentCell);
void animateGrid(const Grid<char> &grid);


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
    bool quit = false;
    char userInput;
    printGrid(grid);

    while (quit == false){
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> userInput;
        switch (userInput){
            case 'a':
                // animate
                break;
            case 't':
                advanceGen(grid);
                printGrid(grid);
                break;
            case 'q':
                quit = true;
                break;
            }
    }
    return 0;
}

void animateGrid(const Grid<char> &grid){
    int generationCount = 20;

    for (int i = 0; i < generationCount; ++i) {

    }
}

char newCell(int neighbours, const char currentCell){
    switch (neighbours) {
    case 0:
    case 1:
        return '-';
        break;
    case 2:
        return currentCell;
        break;
    case 3:
        return 'X';
        break;
    default:
        return '-';
    }
}

int countNeighbours(int posY,int posX, const Grid<char> &grid){
    int neighbours = 0;
    for(int y = posY-1; y < posY+2; y++){
        for(int x = posX-1; x < posX+2; x++){
            if (y == posY && x == posX) {
                continue;
            }

            if (y > 0 && y < grid.numRows() && x > 0 && x < grid.numCols()){
                if(grid.get(y,x) == 'X'){
                    neighbours++;
                }
            }
        }
    }
    return neighbours;
}


void advanceGen(Grid<char> &grid){
    int numRows = grid.numRows();
    int numCols = grid.numCols();
    int neighbours;
    Grid<char> tempGrid = grid;


    for(int y = 0; y < numRows; y++){
        for(int x = 0; x < numCols; x++){
            neighbours = countNeighbours(y,x,grid);
            char cell = newCell(neighbours, grid.get(y,x));
            tempGrid.set(y,x,cell);
        }
    }

    grid = tempGrid;
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

