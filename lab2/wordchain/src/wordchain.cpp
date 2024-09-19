/*
 * A program that finds out the shortest path from one word to another using BFS algorithm.
 *
 * Developers: kevma271, enzcu445
 */

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <sstream>
#include <unordered_set>
using namespace std;

const char ALPHABET[]  = "abcdefghijklmnopqrstuvwxyz";
void welcomeUser();
void getDict(const string &fileName, unordered_set<string> &dictionary);
stack<string> wordChain(const string &w1, const string &w2, const unordered_set<string> &dictionary);
unordered_set<string> getNeighbours(string &word, const unordered_set<string> &dictionary);


// Main function, handles all function calls and the printing of the result
int main() {
    unordered_set<string> dictionary;
    stack<string> finalStack;
    string fileName = "dictionary.txt";
    getDict(fileName, dictionary);

    welcomeUser();

    cout << "Please type two words: ";
    string beginWord, endWord;
    cin >> beginWord >> endWord;

    finalStack = wordChain(beginWord, endWord, dictionary);

    // Printing the stack if it's not empty
    if (!finalStack.empty()) {
        cout << "Word chain from " << beginWord << " to " << endWord << ":" << endl;

        // Create a temporary stack to reverse the order for printing
        stack<string> tempStack;
        while (!finalStack.empty()) {
            tempStack.push(finalStack.top());
            finalStack.pop();
        }

        // Print words in the correct order
        while (!tempStack.empty()) {
            cout << tempStack.top() << " ";
            tempStack.pop();
        }
        cout << endl;
    } else {
        cout << "No word chain found from " << beginWord << " to " << endWord;
    }
    return 0;
}

// Main function for finding the wordchain
stack<string> wordChain(const string &w1, const string &w2, const unordered_set<string> &dictionary) {
    unordered_set<string> neighbours;
    unordered_set<string> usedWords;
    queue<stack<string>> q;
    stack<string> s;
    stack<string> finalStack;
    s.push(w1);
    q.push(s);

    // Make a stack of the front of queue
    while (!q.empty()){
        stack<string> currentChainStack = q.front();
        q.pop();

        // Finish the loop if the stack is our goal word
        if (currentChainStack.top() == w2) {
            finalStack = currentChainStack;
            break;
        }
        // Otherwise we find all neighbours of our current word
        else {
            neighbours = getNeighbours(currentChainStack.top(), dictionary);
            stack<string> copyS;

            // Loop through all words that are neighbours
            for (unordered_set<string>::const_iterator it = neighbours.begin(); it != neighbours.end(); it++) {

                // Check if the neighbour word hasn't been found yet
                if (usedWords.find(*it) == usedWords.end()) {
                      usedWords.insert(*it);
                      copyS = currentChainStack;
                      copyS.push(*it);
                      q.push(copyS);
                }
            }
        }
    }
    return finalStack;
}


// Get all neighbours for a string which are english words
unordered_set<string> getNeighbours(string &word, const unordered_set<string> &dictionary) {
    unordered_set<string> neighbours;

    // Loop through every position of the word
    for (unsigned long i = 0; i < word.length(); i++) {
        char tempSave = word[i];

        // Try every letter in the alphabet for that position
        for (int j = 0; j < 26; j++) {
            word[i] = ALPHABET[j];

            // Check if it's a real word
            if (dictionary.find(word) != dictionary.end()) {
                neighbours.insert(word);
            }
        }
        word[i] = tempSave;
    }
    return neighbours;
}


// Converts the content of the given file to a set
void getDict(const string& fileName, unordered_set<string> &dictionary) {
    ifstream input(fileName);
    string line;

    while (getline(input, line)) {
        dictionary.insert(line);
    }

    input.close();
}


// Simple welcoming function
void welcomeUser() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
}


