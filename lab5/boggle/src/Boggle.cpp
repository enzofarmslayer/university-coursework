// The file that contains functionality for finding words in the boggle.
// Developers: kevma271, enzcu445

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


// Constructor that fixes the board
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

// Load lexicon
void Boggle::loadLexicon() {
    lexicon.addWordsFromFile(DICTIONARY_FILE);
}

// Create board
void Boggle::createBoard() {
    shuffle(cubes);

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int randomSide = randomInteger(0,5);
            board[i][j] = cubes[i][j][randomSide];
        }
    }

}

// Create board manually
void Boggle::createBoardMan(const string& boardInput){
    int index = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = toupper(boardInput[index++]);
        }
    }
}

// Prints board
void Boggle::printBoard(){
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Add word to used
void Boggle::addWord(const string &input) {
    usedWords.insert(input);
}

// Return the amount of words that the user guessed
int Boggle::getWords() {
    return usedWords.size();
}

// Print all words that user guessed
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

// Print all words that computer guessed
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

// Clears lists containing guessed words
void Boggle::clearWords() {
    usedWords.clear();
    usedCompWords.clear();
}

// Check that input has correct length
bool Boggle::validateWordLength(const string& input) {
    return input.size() > 3 && input.size() < 17;
}

// Check that input hasn't been guessed
bool Boggle::validateUsedWord(const string& input) {
    return usedWords.count(input);
}

// Check that word is in lexicon
bool Boggle::validateWord(const string& input) {
    return lexicon.contains(input);
}

// Takes in user input and loops through the board to find it
bool Boggle::findWord(const string& input) {
    clearTraverse();
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == input[0]) {
                isVisited[i][j] = true;
                string recursiveWord = findInputWordHelper(i,j,input.substr(1));
                if (input.substr(1) == recursiveWord) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Recursive helper to find all neighbours of letters
string Boggle::findInputWordHelper(const int i, const int j, const string& input) {
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

    // If the current position didn't yeild any word
    isVisited[i][j] = false;
    return "";
}

// Loops through all positions and sets them as not visited
void Boggle::clearTraverse() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            isVisited[i][j] = false;
        }
    }
}

// Loops through each position on the board and calls
// the recursive helper on each
unordered_set<string> Boggle::findAllWords(int &score){
    clearTraverse();
    //unordered_set<string> tempWordlist;
    unordered_set<string> wordList;
    string currWord;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            currWord = board[i][j];

            if(lexicon.containsPrefix(currWord)){
                isVisited[i][j] = true;
                findAllWordsHelper(i,j,currWord, score, wordList);
                isVisited[i][j] = false;
            }
        }
    }
    for(auto i = wordList.begin(); i != wordList.end(); ++i) {
        //wordList.insert(*i);
        score += i->length()-3;
    }
    return wordList;
}

// Recursive function for finding all words that start with a given letter.
void Boggle::findAllWordsHelper(const int i, const int j, string &currWord, int& score, unordered_set<string>& wordList){
    // Loop through a neighbours of a given position
    for (int m = i-1; m < i+2; ++m) {
        for (int n = j-1; n < j+2; ++n) {
            if (board.inBounds(m,n) && !isVisited[m][n]){
                currWord += board[m][n];

                // If we found a word, insert it to the found ones
                if(isWord(currWord)) {
                    wordList.insert(currWord);
                    usedCompWords.insert(currWord);
                }

                // If the current word is the beginning of a word
                // in the lexicon, recurse in it
                if(lexicon.containsPrefix(currWord)){
                    isVisited[m][n] = true;
                    findAllWordsHelper(m,n,currWord, score, wordList);
                    isVisited[m][n] = false;
                }

                // Pop back the last letter so we can continue with next neuighbour
                currWord.pop_back();
            }
        }
    }
    return;
}

// Validates a word, if it is english, hasn't been used and is at least 4 chars
bool Boggle::isWord(const string& currWord) {
    if (lexicon.contains(currWord) && !usedCompWords.count(currWord) && validateWordLength(currWord)) {
        return true;
    }
    return false;
}
