/*
 * This file includes the program for our Game of Life,
 * a simulation of the lifecycle of a bacteria colony.
 * "Cells (X) live and die by the following rules:"
 * " - A cell with 1 or fewer neighbours dies."
 * " - Locations with 2 with neighbours remain stable."
 * " - Locations with 3 with neighbours will create life."
 * " - A cell with 4 or more neighbours dies."
 *
 * Developers: kevma271, enzcu445
*/

#include <iostream>
#include<fstream>
#include "grid.h"
#include "lifeutil.h"
#include <string>

using namespace std;
void welcomeUser();
string askForFile();
void readFile(string fileName, Grid<char> &grid);
void printGrid(const Grid<char> &grid);
int countNeighbours(int posY, int posX,const Grid<char> &grid);
void advanceGen(Grid<char> &grid);
char createCell(int neighbours, const char currentCell);
void animateGrid(Grid<char> &grid);


/*
 * Main function. Calls relevant functions and
 * waits for correct user input and calls function
 * depending on input.
 */
int main() {
    welcomeUser();

    string fileName = askForFile();
    Grid<char> grid;

    readFile(fileName, grid);
    bool quit = false;
    char userInput;
    printGrid(grid);

    // loop that waits for a user input
    while (quit == false){
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> userInput;
        switch (userInput){
            case 'a':
            animateGrid(grid);
                break;
            case 't':
                clearConsole();
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


/*
 * Prints out a welcome message in the terminal
 * and explains the rules of the game.
*/
void welcomeUser() {
    cout << "Welcome to the TDDD86 Game of Life,"  << endl;
    cout << "a simulation of the lifecycle of a bacteria colony."  << endl;
    cout << "Cells (X) live and die by the following rules:"  << endl;
    cout << " - A cell with 1 or fewer neighbours dies."  << endl;
    cout << " - Locations with 2 with neighbours remain stable."  << endl;
    cout << " - Locations with 3 with neighbours will create life."  << endl;
    cout << " - A cell with 4 or more neighbours dies."  << endl;
}


// Runs the game 20 times and animates every generation
void animateGrid(Grid<char> &grid) {
    int generationCount = 20;

    for (int i = 0; i < generationCount; ++i) {
        clearConsole();
        advanceGen(grid);
        printGrid(grid);
        pause(100);
    }
}


/*
 *  Checks the neighbours of a cell and returns a new
 *  cell for the next generation with correct status.
 */
char createCell(int neighbours, const char currentCell) {
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


/*
 * Counts the amount of neighbours of a cell by looping in a 3x3
 * square with the relevant cell in middle and skipping it when
 * we get to it.
 */
int countNeighbours(int posY,int posX, const Grid<char> &grid) {
    int neighbours = 0;
    for (int y = posY-1; y < posY+2; y++) {
        for (int x = posX-1; x < posX+2; x++) {
            if (y == posY && x == posX) {
                continue;
            }

            else if (grid.inBounds(y, x)) {
                if (grid.get(y,x) == 'X') {
                    neighbours++;
                }
            }
        }
    }

    return neighbours;
}


/*
 * The function that makes the program continue.
 * It loops through all cells and creates a new
 * grid with correct status of all cells.
 */
void advanceGen(Grid<char> &grid){
    int numRows = grid.numRows();
    int numCols = grid.numCols();
    int neighbours;
    Grid<char> tempGrid = grid;


    for(int y = 0; y < numRows; y++){
        for(int x = 0; x < numCols; x++){
            neighbours = countNeighbours(y,x,grid);
            char cell = createCell(neighbours, grid.get(y,x));
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

    for (int y = 0; y < numRows; y++) {
        for(int x = 0; x < numCols; x++) {
            input >> cell;
            grid.set(y,x,cell);
        }
    }
}


// Loops through the grid and prints each cell
void printGrid(const Grid<char> &grid) {
    for (int y = 0; y < grid.numRows(); y++) {
        for (int x = 0; x < grid.numCols(); x++) {
            cout << grid[y][x];
        }
        cout << endl;
    }
    cout << endl;
}
