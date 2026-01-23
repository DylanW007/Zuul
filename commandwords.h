/*
Dylan Waters
1/20/26

Name : commandwords.h

Description : Commandwords class header file for Zuul adventure game.

Note: This code is ported from the original Python version by galbraithja.
*/

#ifndef COMMANDWORDS_H
#define COMMANDWORDS_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class CommandWords {
public:
    // Constructor - initialize the command words.
    CommandWords() {}

    // Check whether a given string is a valid command word. Return true if it is, false if it isn't.
    bool isCommand(string aString) {
        for (string& command : validCommands) {
            if (command == aString) {
                return true;
            }
        }
        // if we get here, the string was not found in the commands
        return false;
    }

    // Print all valid commands to System.out.
    void showAll() {
        for (string& command : validCommands) {
            cout << command << "  ";
        }
        cout << endl;
    }

private:
    // a vector to hold all valid command words.
    vector<string> validCommands = {
        "go", "quit", "help", "look", "inventory", "get", "drop"
    };
};

#endif // COMMANDWORDS_H
