// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};


// TODO: implement the members you declared in Boggle.h
Boggle::Boggle()  {
    board.resize(BOARD_SIZE, BOARD_SIZE);
    cubes.resize(BOARD_SIZE,BOARD_SIZE);
    loadLexicon();


    int cubeIndex = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cubes[i][j] = CUBES[cubeIndex++];
        }
    }
}


void Boggle::loadLexicon() {
    lexicon.addWordsFromFile(DICTIONARY_FILE);
}

void Boggle::createBoard() {
    shuffle(cubes);

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int randomSide = rand() % CUBE_SIDES;
            board[i][j] = cubes[i][j][randomSide];
        }
    }

}

void Boggle::createBoardMan(const string& boardInput){
    int index = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = toupper(boardInput[index++]);
        }
    }
}

void Boggle::printBoard(){
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
