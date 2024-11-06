// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)
    // string choice;
    // cout << "Do you want to generate a random board? (Y/N): ";
    // getline(cin, choice);

    // if (toLowerCase(choice) == "y") {
    //     boggle.createBoard();
    // } else {
    //     string input;
    //     cout << "Enter 16 characters for the board configuration: ";
    //     getline(cin, input);
    //     while (input.length() != 16) {
    //         cout << "Invalid input. Enter exactly 16 letters: ";
    //         getline(cin, input);
    //     }
    //     boggle.createBoardMan(input);
    // }

    boggle.createBoard();
    clearConsole();
    cout << "Current Boggle Board:" << endl;
    boggle.printBoard();
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
