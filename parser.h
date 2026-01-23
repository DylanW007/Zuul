/*
Dylan Waters
11/5/25

Name : parser.h

Description : Parser class header file for Zuul adventure game.

Note: This code is ported from the original Python version by galbraithja.
*/

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <sstream>

#include "command.h"
#include "commandwords.h"

// This parser reads user input and tries to interpret it as an "Adventure" command. Every time it is called it
// reads a line from the terminal and tries to interpret the line as a two word command. It returns the command
// as an object of class Command.
class Parser {
public:
    // Constructor - initialize the command words.
    Parser() {
        commands = CommandWords();
    }

    // Get a new command from the user.
    Command getCommand() {

        string inputLine = "";   // will hold the full input line
        string word1 = "";
        string word2 = "";

        cout << "> ";     // print prompt

        getline(cin, inputLine);

        istringstream tokenizer(inputLine);
        tokenizer >> word1;
        tokenizer >> word2;

        // Now check whether this word is known. If so, create a command
        // with it. If not, create a "null" command (for unknown command).

        if (commands.isCommand(word1)) {
            return Command(word1, word2);
        } else {
            return Command("", word2);
        }
    }

    // Print out a list of valid command words.
    void showCommands() {
        commands.showAll();
    }

private:
    CommandWords commands;
};

#endif // PARSER_H

// Python reference implementation:
/*
'''
Created on Tue Apr 16 13:37:54 2024

@author: galbraithja

This class is the main class of the "World of Zuul" application. "World of Zuul" is a very simple, text based adventure game.  

This parser reads user input and tries to interpret it as an "Adventure" command. Every time it is called it reads a line from the terminal and tries to interpret the line as a two word command. It returns the command as an object of class Command.

The parser has a set of known command words. It checks user input against the known commands, and if the input is not one of the known commands, it returns a command object that is marked as an unknown command.

@author  Michael Kolling and David J. Barnes
@version 1.0 (February 2002)
 * This class is the main class of the "World of Zuul" application. 
 * "World of Zuul" is a very simple, text based adventure game.  
 *
 * This parser reads user input and tries to interpret it as an "Adventure"
 * command. Every time it is called it reads a line from the terminal and
 * tries to interpret the line as a two word command. It returns the command
 * as an object of class Command.
 *
 * The parser has a set of known command words. It checks user input against
 * the known commands, and if the input is not one of the known commands, it
 * returns a command object that is marked as an unknown command.
 * 
 * @author  Michael Kolling and David J. Barnes
 * @version 1.0 (February 2002)
 
'''
class Parser:
    commands = CommandWords();  #// holds all valid command words

    def __init__(self): 
        self.commands = CommandWords()

    def getCommand(self):
        inputLine = ""   # will hold the full input line
        word1 = None
        word2 = None

        print("> ", end="")     # print prompt

        try:
            inputLine = input()
        except Exception as inst:
            print("There was an error during reading: " + inst)

        tokenizer = inputLine.split()

        if (len(tokenizer) > 0):
            word1 = tokenizer[0]    # get first word
        else:
            word1 = None
        if (len(tokenizer) > 1):
            word2 = tokenizer[1]    # get second word
        else:
            word2 = None

        # note: we just ignore the rest of the input line.

        # Now check whether this word is known. If so, create a command
        # with it. If not, create a "null" command (for unknown command).

        if (self.commands.isCommand(word1)):
            return Command(word1, word2)
        else:
            return Command(None, word2)

    '''Print out a list of valid command words.'''
    def showCommands(self):
        self.commands.showAll()

*/