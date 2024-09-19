#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";
void getDict(unordered_set<string> &dictionary);
int checkWordLength(const unordered_set<string> &dictionary);
int askForGuesses();
bool drawEveryAttempt();
void getWordsWithLength(unordered_set<string> &dictionary, const int wordLength);
void gameLoop(int &guesses, string &displayString, const bool &showWordsLeft, const int &wordLength,
              unordered_set<string> &dictionary, const unordered_set<string> &wordsGuessed);

int main() {
    int wordLength;
    int guesses;
    bool showWordsLeft;
    string displayString;
    unordered_set<string> wordsGuessed;
    unordered_map<string, unordered_set<string>> wordFamily;

    cout << "Welcome to Hangman." << endl;


    unordered_set<string> dictionary;
    getDict(dictionary);

    wordLength = checkWordLength(dictionary);
    guesses = askForGuesses();
    showWordsLeft = drawEveryAttempt();

    getWordsWithLength(dictionary, wordLength);

    gameLoop(guesses, displayString, showWordsLeft, wordLength, dictionary, wordsGuessed);

    return 0;
}

string keyMaker(const string& word, char guess){
    string key;
    for (size_t i = 0; i < word.size(); ++i) {
        if(guess == word[i]){
            key.push_back(guess);
        }
        else{
            key.push_back('_');
        }
    }
    return key;
}

void gameLoop(int &guesses, string &displayString, const bool &showWordsLeft, const int &wordLength,
              unordered_set<string> &dictionary, const unordered_set<char> &wordsGuessed, unordered_map<string, unordered_set<string>> &wordFamily) {
    bool gameCompleted = false;
    while(!gameCompleted) {
        cout << "Guesses left: " + to_string(guesses) << endl;
        cout << displayString << endl;
        if (showWordsLeft) {
            cout << dictionary.size() << endl;
        }
        char newGuess;
        //bool valid;
        while(true) {
            // make func that checks newguees
            cout << "Guess a letter :";
            cin >> newGuess;
            if (wordsGuessed.find(newGuess) != wordsGuessed.end()) {
                cout << "Letter already guessed!" << endl;
            } break;
        }

        for (unordered_set<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++){
            string key = keyMaker(*it, newGuess);
            if (wordFamily.find(key) == wordFamily.end()){
                wordFamily[key];

            }
            wordFamily[key].insert(*it);
        }
    }



}


void getWordsWithLength(unordered_set<string> &dictionary, const int wordLength) {
    for (unordered_set<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++) {
        if ((int)(*it).length() != wordLength) {
            dictionary.erase(*it);
        }
    }
}


void getDict(unordered_set<string> &dictionary) {
    ifstream input("di.txt");

    string line;
    while (getline(input, line)) {
        dictionary.insert(line);
    }

    input.close();
}

bool drawEveryAttempt() {
    bool response;
    string input;

    cout << "Do you want to see the amount of words left after every guess? (y/n)";
    cin >> input;

    if (input == "y") {
        response = true;
    } else {
        response = false;
    }

    return response;
}


int askForGuesses() {
    int guesses;
    string input;
    bool valid = false;

    while (!valid) {
        cout << "Enter amount of guesses you want: ";
        cin >> input;
        guesses = stoi(input);
        if (guesses < 0) {
            cout << "Guesses must be greater than 0!";
        } else {
            valid = true;
        }
    }

    return guesses;
}


int checkWordLength(const unordered_set<string> &dictionary) {
    bool valid = false;
    while (!valid) {
        string wordLength;
        cout << "Enter a wordlength: ";
        cin >> wordLength;

        unsigned long length = stoi(wordLength);

        for(unordered_set<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++){
            if (length == it->length()) {
                return length;
            }
        }
        if (!valid) {
            cout << "No words with that length, try again!" << endl;
        }
    }
}
