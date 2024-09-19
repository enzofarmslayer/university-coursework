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
unordered_set<string> getNeighbours(string word, const unordered_set<string> &dictionary);


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
        cout << "No word chain found from " << beginWord << " to " << endWord << "." << endl;
    }

    return 0;
}

stack<string> wordChain(const string &w1, const string &w2, const unordered_set<string> &dictionary){
    unordered_set<string> neighbours;
    unordered_set<string> usedWords;
    queue<stack<string>> q;
    stack<string> s;
    stack<string> finalStack;
    s.push(w1);
    q.push(s);

    while (!q.empty()){
        stack<string> currentChainStack = q.front();
        q.pop();
        if (currentChainStack.top() == w2) {
            finalStack = currentChainStack;
            break;
        }
        else {
            neighbours = getNeighbours(currentChainStack.top(), dictionary);
            stack<string> copyS;
            for(unordered_set<string>::const_iterator it = neighbours.begin(); it != neighbours.end(); it++){
                if(usedWords.find(*it) == usedWords.end()){
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


unordered_set<string> getNeighbours(string word, const unordered_set<string> &dictionary){
    unordered_set<string> neighbours;

    for (unsigned long i = 0; i < word.length(); i++) {
        char tempSave = word[i];
        for(int j = 0; j < 26; j++){
            word[i] = ALPHABET[j];
            if(dictionary.find(word) != dictionary.end()){
                neighbours.insert(word);
            }
        }
        word[i] = tempSave;
    }
    return neighbours;
}


void getDict(const string& fileName, unordered_set<string> &dictionary) {
    ifstream input(fileName);

    string line;
    while (getline(input, line)) {
        dictionary.insert(line);
    }

    input.close();
}

//function wordChain(w1, w2):
//    create an empty queue of stacks
//    create/add a stack containing {w1} to the queue
//  while the queue is not empty:
//  dequeue the partial-chain stack from the front of the queue
//  if the word at the top of the stack is the destinaction word:
//  hooray! output the elements of the stack as the solution
//  e l s e :
//  f o r each valid English word that is a neighbour (differs
//  by 1 letter) of the word at the top of the stack:
//  i f that neighbour word has not already been used in a ladder before:
//  create a copy of the current chain stack
//  put the neighbour word at the top of the copy stack
//  add the copy stack to the end of the queue

void welcomeUser() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
}


