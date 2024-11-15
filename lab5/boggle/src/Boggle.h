// Boggle.h
// Header file for the Boggle game class.
// Developers: kevma271, enzcu445

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <grid.h>
#include <lexicon.h>
#include <unordered_set>
#include <utility>
#include <stack>


using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    Boggle();
    void createBoard();
    void createBoardMan(const string& boardInput);
    void printBoard();
    void addWord(const string& input);
    void clearTraverse();
    void printWords();
    void clearWords();
    void printCompWords();
    void addCompWord(const string &currWord, unordered_set<string>* wordList);
    int getWords();
    bool isWord(const string& currWord);
    bool validateWordLength(const string& input);
    bool validateUsedWord(const string& input);
    bool validateWord(const string& input);
    bool findWord(const string& input);
    unordered_set<string> findAllWords(int& score);
    void findAllWordsHelper(const int i, const int j, string& currWord, int& score, unordered_set<string>& wordList);

private:
    Grid<char> board;
    Grid<string> cubes;
    Grid<bool> isVisited;
    Lexicon lexicon;
    unordered_set<string> usedWords;
    unordered_set<string> usedCompWords;

    void loadLexicon();
    string findInputWordHelper(const int i, const int j, const string& input);

};

#endif
