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
            int randomSide = randomInteger(0,5);
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

void Boggle::addWord(const string &input) {
    usedWords.insert(input);
}


bool Boggle::validateWordLength(const string& input) {
    return input.size() > 3 && input.size() < 17;
}


bool Boggle::validateUsedWord(const string& input) {
    return usedWords.count(input);
}


bool Boggle::validateWord(const string& input) {
    return lexicon.contains(input);
}


bool Boggle::findWord(const string& input) {
    clearTraversed();
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == input[0]) {
                traversedCubes.insert({i, j});
                string recursiveWord = recurse(i,j,input.substr(1));
                if (input.substr(1) == recursiveWord) {
                    return true;
                }
            }
        }
    }
    return false;
}


string Boggle::recurse(const int i, const int j, const string& input) {
    if (input == ""){
        return "";
    }

    for (int m = i-1; m < i+2; ++m) {
        for (int n = j-1; n < j+2; ++n) {
            if (board.inBounds(m,n) && !traversedCubes.count({m,n})) {
                if(board[m][n] == input[0]){
                    traversedCubes.insert({m, n});
                    return input[0] + recurse(m,n,input.substr(1));
                }
            }
        }
    }

    return "";
}

void Boggle::clearTraversed() {
    traversedCubes.clear();
}
