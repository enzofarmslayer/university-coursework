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
stack<string> wordChain(const string w1, const string w2);
string getNeighbours(const string word);


int main() {
    unordered_set<string> dictionary;
    string fileName = "dictionary.txt";
    getDict(fileName);

    welcomeUser();

    cout << "Please type two words: ";
    string twoWords, beginWord, endWord;
    cin >> beginWord >> endWord;



    return 0;
}

void getDict(const string& fileName, unordered_set<string> &dictionary) {
    ifstream input(fileName);

    string line;
    while (getline(input, line)) {
        dictionary.insert(line);
    }

    input.close();


}

//string getNeighbours(const string word){

//}

stack<string> wordChain(const string &w1, const string &w2){
    queue<stack<string>> q;
    stack<string> s;
    stack<string> finalStack;
    s.push(w1);
    q.push(s);

    while (!q.empty()){
        stack<string> currentChainStack = q.front();
        q.pop();
        if (currentChainStack.top() == w2)
        {
            finalStack = currentChainStack;
            break;
        }
        else
        {
            //for()
            //  for each valid English word that is a neighbour (differs
            //  by 1 letter) of the word at the top of the stack:
                //  if that neighbour word has not already been used in a ladder before:
                    //  create a copy of the current chain stack
                    //  put the neighbour word at the top of the copy stack
                    //  add the copy stack to the end of the queue
        }
    }
    return finalStack;
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


