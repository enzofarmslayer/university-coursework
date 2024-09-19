/*
 * A version of the hangman game where the computer "cheats" and makes it much harder for the user to win.
 *
 * Developers: kevma271, enzcu445
 */

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";
void getDict(unordered_set<string> &dictionary);
int askWordLength(const unordered_set<string> &dictionary);
int askForGuesses();
bool askToDrawEveryAttempt();
bool validateGuess(const char& guess);
void gameOver();
bool askToPlayAgain();
void getWordsWithLength(unordered_set<string> &dictionary, const int wordLength);
void gameLoop(int &guesses, string &displayString, const bool &showWordsLeft,
              unordered_set<string> &dictionary, const unordered_set<string> &wordsGuessed);


// The main function, calls relevant helper functions to execute the program.
int main() {
    cout << "Welcome to Hangman." << endl;

    int wordLength;
    int guesses;
    bool showWordsLeft;

    string displayString;
    unordered_set<string> wordsGuessed;
    unordered_map<string, unordered_set<string>> wordFamily;
    unordered_set<string> dictionary;

    wordLength = askWordLength(dictionary);
    guesses = askForGuesses();
    showWordsLeft = askToDrawEveryAttempt();

    getDict(dictionary);
    getWordsWithLength(dictionary, wordLength);

    gameLoop(guesses, displayString, showWordsLeft, dictionary, wordsGuessed);

    return 0;
}


/*
 * Given a word and a character, converts it into how it would look in the game.
 * E.g. if E is the first guess and it is given the word 'earn' -> E___
 * This is to divide all words into their respective word family.
 */
string keyMaker(const string& word, char guess) {
    string key;

    // Loop through every char in the string
    for (size_t i = 0; i < word.size(); ++i) {
        // if our char matches the guess one we add it as is
        if (guess == word[i]){
            key.push_back(guess);
        }
        // Otherwise we add the char as a '_'
        else {
            key.push_back('_');
        }
    }
    return key;
}


/*
 * The main loop of the game.
 */
void gameLoop(int &guesses, string &displayString, const bool &showWordsLeft,
               unordered_set<string> &dictionary, const unordered_set<char> &wordsGuessed,
              unordered_map<string, unordered_set<string>> &wordFamily) {
    bool gameCompleted = false;

    // Update the user of guesses left, what the current word is
    while (!gameCompleted) {
        cout << "Guesses left: " + to_string(guesses) << endl;
        cout << displayString << endl;

        // If user wants to, they will see the amount of words that are still 'available'
        if (showWordsLeft) {
            cout << dictionary.size() << endl;
        }

        char newGuessLetter;
        // New round, let the user take a guess
        while (true) {
            cout << "Guess a letter :";
            cin >> newGuessLetter;

            // Check if the letter isn't valid
            if (!validateGuess(newGuessLetter)) {
                cout << "Invalid. Must be a letter A-Z" << endl;
                break;
            }
            // Check if the letter has already been guessed
            else if (wordsGuessed.find(newGuessLetter) != wordsGuessed.end()) {
                cout << "Letter already guessed!" << endl;
                break;
            }
            break;
        }

        // Loop through all words and divide them into 'families'
        // TODO: Compare families and choose the one with most members. Make game completable
        for (unordered_set<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++) {
            string key = keyMaker(*it, newGuessLetter);

            // Add the key if it doesn't exist and then add the word to the key/family
            if (wordFamily.find(key) == wordFamily.end()){
                wordFamily[key];
            }
            wordFamily[key].insert(*it);
        }
    }
}


// Removes all words from our dictionary if their length is not our desired length
void getWordsWithLength(unordered_set<string> &dictionary, const int wordLength) {
    for (unordered_set<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++) {
        if ((int)(*it).length() != wordLength) {
            dictionary.erase(*it);
        }
    }
}


// Converts the content of 'di.txt' to a set
void getDict(unordered_set<string> &dictionary) {
    ifstream input("di.txt");

    string line;
    while (getline(input, line)) {
        dictionary.insert(line);
    }

    input.close();
}


// Asks the user if they want a visual process of the game
bool askToDrawEveryAttempt() {
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


// Asks the user how many guesses they want and returns as an int
int askForGuesses() {
    int guesses;
    string input;

    while (true) {
        cout << "Enter amount of guesses you want: ";
        cin >> input;
        guesses = stoi(input);

        if (guesses < 0) {
            cout << "Guesses must be greater than 0!";
        } else {
            break;
        }
    }
    return guesses;
}


// Asks the user for a word length and returns it as an int
int askWordLength(const unordered_set<string> &dictionary) {
    while (true) {
        string wordLength;
        cout << "Enter a wordlength: ";
        cin >> wordLength;

        unsigned long length = stoi(wordLength);

        // Check if there is a word with that length
        for(unordered_set<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++){
            if (length == it->length()) {
                return length;
            }
        }

        cout << "No words with that length, try again!" << endl;
    }
}


// Verfies the guess to see that it is of desired input
bool validateGuess(const char& guess) {
    bool valid = false;
    for (int i = 0; i < 26; i++) {
        if (guess == toupper(ALPHABET[i])) {
            return valid;
        }
    }
    return valid;
}


// Gives the user a random word that was the goal word
void gameOver() {
    cout << "Game Over! The word was: ";
    float v1;
    //v1 = rand() % wordsLeft.size();
    //cout << wordsLeft[v1] << endl;
}


// Ask the user to play again
bool askToPlayAgain() {
    string response;
    cout << "Play again? (y/n)";
    cin >> response;

    if (response == "y") {
        return true;
    } else {
        return false;
    }
}
