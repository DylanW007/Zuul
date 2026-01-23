/*
Dylan Waters
11/5/25

Name : Game.h

Description : Game class header file for Zuul adventure game.

Note: This code is ported from the original Python version by galbraithja.
*/
#ifndef GAME_H
#define GAME_H

#include "room.h"
#include "command.h"
#include "commandwords.h"
#include "parser.h"
#include <string>

using namespace std;

// Class Game - main class of the Zuul adventure game.
class Game {
public:
    // Constructor - initialize the command words.
    Game() {
        inventory = vector<string>();
        createRooms();
        zuulPoweredOn = false;
        faradayPoweredOn = true;
        quit = false;
    }

    ~Game() {}

    // Create all the rooms and link their exits together.
    void createRooms();

    // Main play routine.  Loops until end of play.
    void play();

    void printWelcome();

    //Inventory check
    string getInventoryDescription();

    // Given a command, process (that is: execute) the command. If this command ends the game, true is returned, otherwise false is returned.   
    bool processCommand(Command command);

    // Print out some help information. Here we print some stupid, cryptic message and a list of the command words.
    void printHelp();
    
    void goRoom(Command command);

    bool quitGame(Command command);

private:
    Parser parser;
    Room* currentRoom;
    vector<string> inventory;
    bool zuulPoweredOn;
    bool faradayPoweredOn; 
    bool quit;
};

#endif // GAME_H