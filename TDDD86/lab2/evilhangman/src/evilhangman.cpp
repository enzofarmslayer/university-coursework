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
int askWordLength(unordered_set<string> &dictionary, string &displayString);
int askForGuesses();
bool askToDrawEveryAttempt();
bool validateGuess(const char& guess);
bool gameOver(const int &guesses, const string &displayString);
void handleGameOver(const unordered_set<string> &dictionary);
bool askToPlayAgain();
bool stringFullyDisplayed(const string &displayString);
void updateContainers(unordered_set<string> &dictionary, const string &largestFamilyKey, unordered_map<string, unordered_set<string>> &wordFamily, string &displayString);
void getWordsWithLength(unordered_set<string> &dictionary, const int wordLength);
void findBiggestFamily(unordered_map<string, unordered_set<string>> &wordFamily, int &largestFamilyCount, string &largestFamilyKey);
void createFamilies(unordered_set<string> &dictionary, unordered_map<string, unordered_set<string>> &wordFamily,
                    const char &newGuessLetter);
void gameLoop(int &guesses, string &displayString, const bool &showWordsLeft,
              unordered_set<string> &dictionary, const unordered_set<char> &wordsGuessed,
             unordered_map<string, unordered_set<string>> &wordFamily, bool &playAgain);
void updateDisplayString(string &displaystring, const string &largestFamilyKey);


// The main function, calls relevant helper functions to execute the program.
int main() {
    cout << "Welcome to Hangman." << endl;

    int wordLength;
    int guesses;
    bool showWordsLeft;

    unordered_set<char> wordsGuessed;
    string displayString;
    unordered_map<string, unordered_set<string>> wordFamily;
    unordered_set<string> dictionary;

    bool playAgain = true;

    while (playAgain) {
        getDict(dictionary);
        displayString = "";

        wordLength = askWordLength(dictionary, displayString);
        guesses = askForGuesses();
        showWordsLeft = askToDrawEveryAttempt();

        getWordsWithLength(dictionary, wordLength);

        gameLoop(guesses, displayString, showWordsLeft, dictionary, wordsGuessed, wordFamily, playAgain);
    }

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
        if (tolower(guess) == word[i]){
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
              unordered_map<string, unordered_set<string>> &wordFamily, bool &playAgain) {
    bool gameCompleted = false;

    // Update the user of guesses left, what the current word is
    while (!gameCompleted) {
        system("CLS");
        cout << "Guesses left: " + to_string(guesses) << endl;
        cout << displayString << endl;

        // If user wants to, they will see the amount of words that are still 'available'
        if (showWordsLeft) {
            cout << "Possible words left: " << dictionary.size() << endl;
        }

        char newGuessLetter;
        // New round, let the user take a guess
        bool validGuess = false;

        while (!validGuess) {
            cout << "Guess a letter :";
            cin >> newGuessLetter;

            // Check if the letter isn't valid
            if (!validateGuess(newGuessLetter)) {
                cout << "Invalid. Must be a letter A-Z" << endl;
            }
            // Check if the letter has already been guessed
            else if (wordsGuessed.find(newGuessLetter) != wordsGuessed.end()) {
                cout << "Letter already guessed!" << endl;
            }
            // If guess is valid then exit the question loop
            else {
                validGuess = true;
            }
        }

        int largestFamilyCount = 0;
        string largestFamilyKey;

        createFamilies(dictionary, wordFamily, newGuessLetter);
        findBiggestFamily(wordFamily, largestFamilyCount, largestFamilyKey);
        updateContainers(dictionary, largestFamilyKey, wordFamily, displayString);

        guesses -= 1;
        if (gameOver(guesses, displayString)) {
            handleGameOver(dictionary);
            if (!askToPlayAgain()) {
                playAgain = false;
            }
            gameCompleted = true;
        }
    }
}


// Loop through all wordfamilies and stick with the biggest one
void findBiggestFamily(unordered_map<string, unordered_set<string>> &wordFamily, int &largestFamilyCount, string &largestFamilyKey) {

    for (unordered_map<string,unordered_set<string>>::const_iterator it = wordFamily.begin(); it != wordFamily.end(); it++){
        if((*it).second.size() > largestFamilyCount){
            largestFamilyCount = (*it).second.size();
            largestFamilyKey = (*it).first;
        }
    }
}


// Loop through all words and divide them into 'families'
void createFamilies(unordered_set<string> &dictionary, unordered_map<string, unordered_set<string>> &wordFamily,
                    const char &newGuessLetter) {

    for (unordered_set<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++) {
        string key = keyMaker(*it, newGuessLetter);

        // Add the key if it doesn't exist and then add the word to the key/family
        if (wordFamily.find(key) == wordFamily.end()){
            wordFamily[key];
        }
        wordFamily[key].insert(*it);
    }

}


// Update the display so it shows the current string
void updateDisplayString(string &displaystring, const string &largestFamilyKey){
    string displayTemp;
    for (int i = 0; i < displaystring.length(); i++) {
        if (displaystring[i] != '_'){
            displayTemp.push_back(displaystring[i]);
        }
        else if (largestFamilyKey[i] != '_'){
            displayTemp.push_back(largestFamilyKey[i]);
        }
        else
        {
            displayTemp.push_back('_');
        }
    }
    displaystring = displayTemp;
}


// Removes all words from dict that doesn't match our key
void updateContainers(unordered_set<string> &dictionary, const string &largestFamilyKey, unordered_map<string, unordered_set<string>> &wordFamily, string &displayString) {
    dictionary = wordFamily.at(largestFamilyKey);
    unordered_map<string, unordered_set<string>> emptymap;
    wordFamily = emptymap;

    updateDisplayString(displayString, largestFamilyKey);
    //displayString = largestFamilyKey;
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
    ifstream input("dictionary.txt");

    string line;
    while (getline(input, line)) {
        dictionary.insert(line);
    }

    input.close();
}


// Asks the user if they want a visual process of the game
bool askToDrawEveryAttempt() {
    string input;

    while (true) {
        cout << "Do you want to see the amount of words left after every guess? (y/n)";
        cin >> input;

        if (input == "y") {
            return true;
        } else if (input == "n") {
            return false;
        }
        cout << "Invalid input. Only accepting 'y' or 'n'!" << endl;
    }
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
int askWordLength(unordered_set<string> &dictionary, string &displayString) {
    string wordLength;

    while (true) {
        cout << "Enter a wordlength: ";
        cin >> wordLength;
        unordered_set<string> tempDict;
        unsigned long length = stoi(wordLength);

        // Loop through all words in dictionary
        for (unordered_set<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++){
            // Check if there is a word with that length
            if (length == it->length()) {
                tempDict.insert(*it);
            }
        }

        if(!tempDict.empty()){
            for (int i = 0; i < (int)length; i++) {
                displayString.push_back('_');
            }
            dictionary = tempDict;
            return length;
        }
        else{
            cout << "No words with that length, try again!" << endl;
        }
    }

}


// Verfies the guess to see that it is of desired input
bool validateGuess(const char& guess) {
    for (int i = 0; i < 26; i++) {
        if (guess == toupper(ALPHABET[i])) {
            return true;
        }
    }
    return false;
}


// Checks if game's over
bool gameOver(const int &guesses, const string &displayString) {
    if (guesses == 0 || stringFullyDisplayed(displayString)) {
        return true;
    } else {
        return false;
    }
}


// Check if the entire string is displayed
bool stringFullyDisplayed(const string &displayString) {
    int fullLength = displayString.length();
    int counter;

    for (int i = 0; i < fullLength; i++) {
        if (displayString[i] != '_') {
            counter += 1;
        }
    }
    cout << displayString << endl;
    return counter == fullLength;
}


// Gives the user a random word that was the goal word
void handleGameOver(const unordered_set<string> &dictionary) {
    cout << "Game Over! The word was: " << *dictionary.begin() << endl;
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
