#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

const char ALPHABET[]  = "abcdefghijklmnopqrstuvwxyz";
void welcomeUser();
string askForWords();

int main() {
    welcomeUser();

    string twoWords;
    words = askForWords();

    return 0;
}


string askForWords() {
    cout << "Please type two words: ";

    string twoWords;
    cin >> twoWords;
    return twoWords;
}


void welcomeUser() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
}


