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
    isVisited.resize(BOARD_SIZE, BOARD_SIZE);
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


int Boggle::getWords() {
    return usedWords.size();
}

void Boggle::printWords() {
    cout << "{";
    for (auto i = usedWords.begin(); i != usedWords.end(); i++) {
        if (i == usedWords.begin()) {
            cout << "''" << *i << "''";
        } else {
            cout << ", ''" << *i << "''";
        }
    }
    cout << "}" << endl;
}


void Boggle::printCompWords() {
    cout << "{";
    for (auto i = usedCompWords.begin(); i != usedCompWords.end(); i++) {
        if (i == usedCompWords.begin()) {
            cout << "''" << *i << "''";
        } else {
            cout << ", ''" << *i << "''";
        }
    }
    cout << "}" << endl;
}

void Boggle::clearWords() {
    usedWords.clear();
    usedCompWords.clear();
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
    clearTraverse();
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == input[0]) {
                isVisited[i][j] = true;
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
            if (board.inBounds(m,n) && !isVisited[m][n]) {
                if(board[m][n] == input[0]){
                    isVisited[m][n] = true;
                    return input[0] + recurse(m,n,input.substr(1));
                }
            }
        }
    }

    return "";
}

void Boggle::clearTraverse() {
    //traversedCubes.clear();
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            isVisited[i][j] = false;
        }
    }
}


unordered_set<string> Boggle::findAllWords(int &score){
    clearTraverse();
    unordered_set<string> tempWordlist;
    unordered_set<string> wordList;
    string currWord;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            currWord = board[i][j];
            if(lexicon.containsPrefix(currWord)){
                isVisited[i][j] = true;
                tempWordlist = recurse2(i,j,currWord, score);
                isVisited[i][j] = false;
            }
            // lägg till t lista och unmark
            for(auto i = tempWordlist.begin(); i != tempWordlist.end(); ++i) {
                wordList.insert(*i);
                score += i->length()-3;

            }

        }
    }
    return wordList;
}

unordered_set<string> Boggle::recurse2(const int i, const int j, string &currWord, int& score){
    unordered_set<string> tempWordlist;
    unordered_set<string> wordList;

    for (int m = i-1; m < i+2; ++m) {
        for (int n = j-1; n < j+2; ++n) {
            if (board.inBounds(m,n) && !isVisited[m][n]){
                currWord += board[m][n];

                if(isWord(currWord)) { // reset used
                    wordList.insert(currWord);
                    usedCompWords.insert(currWord);
                }

                if(lexicon.containsPrefix(currWord)){
                    isVisited[m][n] = true;
                    tempWordlist = recurse2(m,n,currWord, score);
                    isVisited[m][n] = false;

                }
                for(auto i = tempWordlist.begin(); i != tempWordlist.end(); ++i) {
                    wordList.insert(*i);
                }

                currWord.pop_back();
            }

        }
    }
    return wordList;
}


bool Boggle::isWord(const string& currWord) {
    if (lexicon.contains(currWord) && !usedCompWords.count(currWord) && validateWordLength(currWord)) {
        return true;
    }
    return false;
}
