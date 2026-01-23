/*
Dylan Waters
11/5/25

Name : Game.cpp

Description : Game class implementation file for Zuul adventure game.

Note: This code is ported from the original Python version by galbraithja.
*/
#include "game.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Create all the rooms and link their exits together.
void Game::createRooms() {
    // -- main hallways
    Room* west_hall = new Room("West Hall", "in the West hallway");
    Room* east_hall = new Room("East Hall", "in the East hallway");
    
    // -- control sector
    Room* control_room = new Room("Control Room", "in the Control room");
    Room* aux_room = new Room("Auxilary Room", "in the Auxilary room");
    
    // -- command sector
    Room* command_room = new Room("Command Room", "in the Command room");
    Room* communications_room = new Room("Communications Room", "in the Communications room");
    
    // -- power sector
    Room* zuul_room = new Room("Zuul Room", "in the Zuul power room");
    Room* faraday_room = new Room("Faraday Room", "in the Faraday power room");
    Room* transfer_room = new Room("Transfer Room", "in the Transfer room");
    
    // science sector
    Room* lab1 = new Room("Lab 1", "in Lab 1 science room");
    Room* lab2 = new Room("Lab 2", "in Lab 2 science room");
    
    // cafeteria
    Room* cafeteria = new Room("Cafeteria", "in the cafeteria");
    
    // Life support sector
    Room* water_room = new Room("Water Room", "in the water room");
    Room* air_room = new Room("Air Room", "in the air room");
    
    // Medical sector
    Room* recovery_room = new Room("Recovery", "in the medical recovery room");
    Room* intensive_care = new Room("Intensive Care", "in the medical intensive care room");
    Room* operating_room = new Room("Operating Room", "in the medical operating room");
    
    // set exits
    west_hall->setExit("north", control_room);
    west_hall->setExit("south", command_room);
    west_hall->setExit("east", transfer_room);
    west_hall->setExit("west", water_room);
    
    east_hall->setExit("north", lab1);
    east_hall->setExit("south", recovery_room);
    east_hall->setExit("east", cafeteria);
    east_hall->setExit("west", transfer_room);
    
    transfer_room->setExit("north", zuul_room);
    transfer_room->setExit("south", faraday_room);
    transfer_room->setExit("east", east_hall);
    transfer_room->setExit("west", west_hall);

    zuul_room->setExit("south", transfer_room);
    faraday_room->setExit("north", transfer_room);
    control_room->setExit("east", aux_room);
    control_room->setExit("south", west_hall);
    aux_room->setExit("west", control_room);
    command_room->setExit("north", west_hall);
    command_room->setExit("east", communications_room);
    communications_room->setExit("west", command_room);
    water_room->setExit("east", west_hall);
    water_room->setExit("south", air_room);
    air_room->setExit("north", water_room);
    lab1->setExit("west", lab2);
    lab1->setExit("south", east_hall);
    lab2->setExit("east", lab1);
    recovery_room->setExit("north", east_hall);
    recovery_room->setExit("west", intensive_care);
    intensive_care->setExit("east", recovery_room);
    intensive_care->setExit("west", operating_room);
    operating_room->setExit("east", intensive_care);
    cafeteria->setExit("west", east_hall);

    // set items =====================================================
    lab1->addItem("zuul_manual");
    lab2->addItem("toolkit");
    command_room->addItem("faraday_manual");
    control_room->addItem("blue_key");
    aux_room->addItem("red_key");
    zuul_room->setLock("red_key");
    faraday_room->setLock("blue_key");
    currentRoom = recovery_room;    // start game in recovery room

    // cheat codes for end game
    //inventory.push_back("blue_key");
    //inventory.push_back("red_key");
    //inventory.push_back("faraday_manual");
    //inventory.push_back("zuul_manual");
    //inventory.push_back("toolkit");
    //currentRoom = faraday_room;
}

// Main play routine.  Loops until end of play.
void Game::play() {
    printWelcome();

    // Enter the main command loop.  Here we repeatedly read commands and
    // execute them until the game is over.
            
    bool finished = false;
    while (not finished) {
        Command command = parser.getCommand();
        finished = processCommand(command);
    }
    cout << "Thank you for playing.  Good bye." << endl;
}

void Game::printWelcome() {
    cout << "----------------- Zuul ------------------" << endl;
    cout << endl;
    cout << "You're on a space station that has been damaged" << endl;
    cout << "by a small asteroid. The main power plant is" << endl;
    cout << "disabled and nobody knows how to start the" << endl;
    cout << "ancient backup power plant called Zuul except" << endl;
    cout << "for you! The problem is that you've been knocked" << endl;
    cout << "unconsious by the asteroid strike" << endl;
    cout << "" << endl;
    cout << "Type 'help' if you need help." << endl;
    cout << endl;
    cout << currentRoom->getLongDescription() << endl;
}

//Inventory check
string Game::getInventoryDescription() {
    string str = "\n";
    if (inventory.empty()) {
        str += "No items in your inventory.\n";
        return str;
    }
    
    str = "You have the following items...";
    for (string item : inventory) {
        str += "\n    " + item + " ";
    }
    str += "\n";
    return str;
}

// Given a command, process (that is: execute) the command. If this command ends the game, true is returned, otherwise false is returned.  
bool Game::processCommand(Command command) {
    bool wantToQuit = false;

    if(command.isUnknown()) {
        cout << "I don't know what you mean..." << endl;
        return false;
    }

    string commandWord = command.getCommandWord();
    if (commandWord == "help") {
        printHelp();
    } else if (commandWord == "go") {
        goRoom(command);
    } else if (commandWord == "quit") {
        wantToQuit = quitGame(command);
    } else if (commandWord == "look") {
        cout << currentRoom->getLongDescription() << endl;
    } else if (commandWord == "inventory") {
        cout << getInventoryDescription() << endl;
    } else if (commandWord == "get") {
        string itemToGet = command.getSecondWord();
        if (currentRoom) {
            if (currentRoom->hasItem(itemToGet)) {
                inventory.push_back(itemToGet);
                currentRoom->removeItem(itemToGet);
                cout << "You've added " << itemToGet << " to your inventory" << endl;
            } else {
                cout << "Room does not have " << itemToGet << " item." << endl;
            }
        } else {
            cout << "Error: Current room is not set!" << endl;
        }
    } else if (commandWord == "drop") {
        string itemToDrop = command.getSecondWord();
        
        auto itr = find(inventory.begin(), inventory.end(), itemToDrop);
        if (itr != inventory.end()) {
            inventory.erase(itr);
            currentRoom->addItem(itemToDrop);
            cout << "You have dropped " << itemToDrop << "." << endl;
        } else {
            cout << "You do not have " << itemToDrop << " in your inventory!" << endl;
        }
    }

    if (quit) {
        wantToQuit = true;
    }
    
    return wantToQuit;
}

// Print out some help information. Here we print some stupid, cryptic message and a list of the command words.
void Game::printHelp() {
    cout << "You are lost. You are alone. You wander" << endl;
    cout << "around on the space station." << endl;
    cout << endl;
    cout << "Your command words are:" << endl;
    parser.showCommands();
}

// Try to go to one direction. If there is an exit, enter the new room, otherwise print an error message.
void Game::goRoom(Command command) {
    if(!command.hasSecondWord()) {
        cout << "Go where?" << endl;
        return;
    }
    string direction = command.getSecondWord();
    if (currentRoom->hasExit(direction) == false) {
        cout << "You can't go " << direction << " from this room." << endl;
        return;
    }
    // Try to leave current room.
    Room* nextRoom = currentRoom->getExit(direction);
    if (nextRoom == nullptr) {
        cout << "There is no door!" << endl;
    } else {
        if (nextRoom->hasLock()) {
            string lock_str = nextRoom->getLock();
            // Check if player has key in inventory
            bool has_key = false;
            for (string item : inventory) {
                if (item == lock_str) {
                    has_key = true;
                    break;
                }
            }
            if (has_key) {
                cout << "You have accessed room using " << lock_str << "." << endl;
                currentRoom = nextRoom;
                cout << currentRoom->getLongDescription() << endl;
                
                if (currentRoom->getName() == "Zuul Room") {
                    bool has_items = true;
                    
                    bool has_zuul_manual = false;
                    bool has_toolkit = false;
                    
                    for (string item : inventory) {
                        if (item == "zuul_manual") {
                            has_zuul_manual = true;
                        }
                        if (item == "toolkit") {
                            has_toolkit = true;
                        }
                    }
                    
                    if (!has_zuul_manual) {
                        has_items = false;
                        cout << "You need the Zuul manual to turn on the power plant!" << endl;
                    } else {
                        cout << "You have the Zuul manual!" << endl;
                    }
                    
                    if (!has_toolkit) {
                        has_items = false;
                        cout << "You need a tool kit to help turn on the power plant!" << endl;
                    }
                    
                    if (has_items) {
                        zuulPoweredOn = true;
                        cout << "Congratulations! You have turned on Zuul power plant!" << endl;
                    }
                }
                
                if (currentRoom->getName() == "Faraday Room") {
                    bool has_items = true;
                    
                    bool has_faraday_manual = false;
                    bool has_toolkit = false;
                    
                    for (string item : inventory) {
                        if (item == "faraday_manual") {
                            has_faraday_manual = true;
                        }
                        if (item == "toolkit") {
                            has_toolkit = true;
                        }
                    }
                    
                    if (!has_faraday_manual) {
                        has_items = false;
                        cout << "You need the Faraday manual to turn off the power plant!" << endl;
                    }
                    
                    if (has_items) {
                        faradayPoweredOn = false;                        
                        cout << "Congratulations! You have turned off Faraday power plant!" << endl;
                    }
                }
            } else {
                cout << "You don't have the key to access this room!" << endl;
            }
        } else {
            currentRoom = nextRoom;
            cout << currentRoom->getLongDescription() << endl;
        }
    }
}

bool Game::quitGame(Command command) {
    if(command.hasSecondWord()) {
        cout << "Quit what?" << endl;
        return false;
    } else {
        return true;  // signal that we want to quit
    }
}