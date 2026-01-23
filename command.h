/*
Dylan Waters
1/20/26

Name : Command.h

Description : Command class header file for Zuul adventure game.

Note: This code is ported from the original Python version by galbraithja.
*/

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <iostream>

using namespace std;

class Command {
public:
    Command() {
        commandWord = "";
        secondWord = "";
        cout << "Don't use the default constructor for Command class!" << endl;
    }

    // Constructor - initialise the command with command word and second word
    Command(string first, string second) {
        commandWord = first;
        secondWord = second;
    }
    
    // Return the command word (the first word) of this command. If the command was not understood, the result is empty string.
    string getCommandWord() { return commandWord; }
    
    // Return the second word of this command. Returns empty string if there was no second word.
    string getSecondWord() { return secondWord; }
    
    // Return true if this command was not understood.
    bool isUnknown() { return (commandWord == ""); }

    // Return true if the command has a second word.
    bool hasSecondWord() { return (secondWord != ""); }

private:
    string commandWord;
    string secondWord;
};

#endif // COMMAND_H