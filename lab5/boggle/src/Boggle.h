// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <grid.h>
#include <lexicon.h>
#include <unordered_set>
#include <utility>
#include <stack>

// TODO: include any other header files you need

using namespace std;

struct pair_hash {
    template <typename T1, typename T2>
    size_t operator ()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);  // Hash the first element
        auto h2 = hash<T2>{}(p.second); // Hash the second element
        // Combine the two hash values using XOR and bit shifting
        return h1 ^ (h2 << 1);
    }
};

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
    bool isWord(const string& currWord);
    bool validateWordLength(const string& input);
    bool validateUsedWord(const string& input);
    bool validateWord(const string& input);
    bool findWord(const string& input);
    unordered_set<string> findAllWords();
    unordered_set<string> recurse2(const int i, const int j, string& currWord);

    // TODO: decide the public member functions and declare them

private:
    // TODO: decide the private member variables/functions and declare them
    Grid<char> board;
    Grid<string> cubes;
    Grid<bool> isVisited;
    Lexicon lexicon;
    unordered_set<string> usedWords;
    unordered_set<string> usedCompWords;

    void loadLexicon();
    string recurse(const int i, const int j, const string& input);

};

#endif
