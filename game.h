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


// Python reference implementation:
/*
'''
Wednesday Dec 19 2024

Dylan Waters

Created space station themed game where there has been an accident and we need to restore power to the ship!

* Added lots of rooms for the space station
* Added player inventory
* Added room locks
* Added room items that can be picked up and dropped
* Added turn on Zuul power plant and turn off Faraday power plant
* Added winning conditions for transferring power to station to Zuul power plant

Created on Tue Apr 16 13:37:54 2024

@author: galbraithja

This class is the main class of the "World of Zuul" application. "World of Zuul" is a very simple, text based adventure game.  Users can walk around some scenery. That's all. It should really be extended to make it more interesting!

To play this game, create an instance of this class and call the "play" method.

This main class creates and initialises all the others: it creates all rooms, creates the parser and starts the game.  It also evaluates and executes the commands that the parser returns.

@author  Michael Kolling and David J. Barnes
@version 1.0 (February 2002)
'''

class Game:
    parser = Parser()
    currentRoom = None
        
    '''Create the game and initialise its internal map.'''
    def __init__(self):
        self.inventory = []
        self.createRooms()
        self.zuulPoweredOn = False
        self.faradayPoweredOn = True
        self.quit = False

    '''Create all the rooms and link their exits together.'''
    def createRooms(self):
        # create the rooms
        
        # ---- medical sector ----
        # recovery
        # intensive care
        # operating room
        
        # ---- power sector ----
        # zuul power plant
        # faraday power plant
        # transfer room - tranfer power to station from either zuul or archimedis
        
        # --- control sector ----
        # control room - controlling all systems on station
        # auxilary room - for backup systems
        
        # --- life sector ---
        # oxygen room
        # water room
        # cafeteria
        
        # --- command sector
        # command deck - main room for captain and crew maintain operations
        # communications room - room for communicating back to earth and rest of station
        
        # --- science sector ---
        # lab 01
        # lab 02
        
        # Items:
        # blue keycard to get into transfer room. You need to go meet captain in control room
        # red keycard to get into zuul power room.
        # zuul program manual needed to start system
        # faraday program manual needed to shut down system
        # tool kit needed to unscrew panel covers, etc.
        
        # create the rooms
        
        # -- main hallways
        west_hall = Room("West Hall", "in the West hallway")
        east_hall = Room("East Hall", "in the East hallway")
        
        # -- control sector
        control_room = Room("Control Room", "in the Control room")
        aux_room = Room("Auxilary Room", "in the Auxilary room")
        
        # -- command sector
        command_room = Room("Command Room", "in the Command room")
        communications_room = Room("Communications Room", "in the Communications room")
        
        # -- power sector
        zuul_room = Room("Zuul Room", "in the Zuul power room")
        faraday_room = Room("Faraday Room", "in the Faraday power room")
        transfer_room = Room("Transfer Room", "in the Transfer room")
        
        # science sector
        lab1 = Room("Lab 1", "in Lab 1 science room")
        lab2 = Room("Lab 2", "in Lab 2 science room")
        
        # cafeteria
        cafeteria = Room("Cafeteria", "in the cafeteria")
        
        # Life support sector
        water_room = Room("Water Room", "in the water room")
        air_room = Room("Air Room", "in the air room")
        
        # Medical sector
        recovery_room = Room("Recovery", "in the medical recovery room")
        intensive_care = Room("Intensive Care", "in the medical intensive care room")
        operating_room = Room("Operating Room", "in the medical operating room")
        
        # set exits
        west_hall.setExit("north", control_room)
        west_hall.setExit("south", command_room)
        west_hall.setExit("east", transfer_room)
        west_hall.setExit("west", water_room)
        
        east_hall.setExit("north", lab1)
        east_hall.setExit("south", recovery_room)
        east_hall.setExit("east", cafeteria)
        east_hall.setExit("west", transfer_room)
        
        transfer_room.setExit("north", zuul_room)
        transfer_room.setExit("south", faraday_room)
        transfer_room.setExit("east", east_hall)
        transfer_room.setExit("west", west_hall)
        
        zuul_room.setExit("south", transfer_room)
        faraday_room.setExit("north", transfer_room)
        
        control_room.setExit("east", aux_room)
        control_room.setExit("south", west_hall)
        aux_room.setExit("west", control_room)
        
        command_room.setExit("north", west_hall)
        command_room.setExit("east", communications_room)
        communications_room.setExit("west", command_room)
        
        water_room.setExit("east", west_hall)
        water_room.setExit("south", air_room)
        air_room.setExit("north", water_room)
        
        lab1.setExit("west", lab2)
        lab1.setExit("south", east_hall)
        lab2.setExit("east", lab1)
        
        recovery_room.setExit("north", east_hall)
        recovery_room.setExit("west", intensive_care)
        intensive_care.setExit("east", recovery_room)
        intensive_care.setExit("west", operating_room)
        operating_room.setExit("east", intensive_care)
        
        cafeteria.setExit("west", east_hall)
        
        # set items =====================================================
        lab1.addItem("zuul_manual")
        lab2.addItem("toolkit")
        command_room.addItem("faraday_manual")
        control_room.addItem("blue_key")
        aux_room.addItem("red_key")
    
        zuul_room.setLock("red_key")
        faraday_room.setLock("blue_key")
        
        self.currentRoom = recovery_room    # start game in recovery room
    
        # cheat codes for end game
        #self.inventory.append("blue_key")
        #self.inventory.append("red_key")
        #self.inventory.append("faraday_manual")
        #self.inventory.append("zuul_manual")
        #self.inventory.append("toolkit")
        #self.currentRoom = faraday_room
        
        #I used this to cut to the end to save time when testing

    '''Main play routine.  Loops until end of play.'''
    def play(self):
        self.printWelcome()

        # Enter the main command loop.  Here we repeatedly read commands and
        # execute them until the game is over.
                
        finished = False
        while (not finished):
            command = self.parser.getCommand()
            finished = self.processCommand(command)
        print("Thank you for playing.  Good bye.")

    '''Print out the opening message for the player.'''
    def printWelcome(self):
        print("----------------- Zuul ------------------")
        print()
        print("You're on a space station that has been damaged")
        print("by a small asteroid. The main power plant is")
        print("disabled and nobody knows how to start the")
        print("ancient backup power plant called Zuul except")
        print("for you! The problem is that you've been knocked")
        print("unconsious by the asteroid strike")
        print("")
        print("You're are starting to wake up in the recovery room...")
        print("")
        print(self.currentRoom.getLongDescription())

    #Inventory check =================================================
    def getInventoryDescription(self):
        str = "\n"
        if not self.inventory:
            str += "No items in your inventory.\n"
            return str
        
        str = "You have the following items..."
        for item in self.inventory:
            str += "\n    " + item + " "
        str += "\n"
        return str

    '''Given a command, process (that is: execute) the command. If this command ends the game, true is returned, otherwise false is returned.'''
    def processCommand(self, command):
        wantToQuit = False

        if(command.isUnknown()):
            print("I don't know what you mean...")
            return False

        commandWord = command.getCommandWord()
        if (commandWord == "help"):
            self.printHelp()
        elif (commandWord == "go"):
            self.goRoom(command)
        elif (commandWord == "quit"):
            wantToQuit = self.quitGame(command)
        # Add look to see whats in current room.
        elif (commandWord == "look"):
            print(self.currentRoom.getLongDescription())
        # Add inventory command to print my inventory
        elif (commandWord == "inventory"):
            print(self.getInventoryDescription())
        # Add get command to get item from room and add it to my inventory
        elif (commandWord == "get"):
            itemToGet = command.getSecondWord()
            if self.currentRoom:
                if self.currentRoom.hasItem(itemToGet):
                    self.inventory.append(itemToGet)
                    self.currentRoom.removeItem(itemToGet)
                    print("You've added " + itemToGet + " to your inventory")
                else:
                    print("Room does not have " + itemToGet + " item.")
            else:
                print("Error: Current room is not set!")
        # Add drop command to drop item into current room.
        elif (commandWord == "drop"):
            itemToDrop = command.getSecondWord()
            
            if itemToDrop in self.inventory:
                self.inventory.remove(itemToDrop)
                self.currentRoom.addItem(itemToDrop)
                print("You have dropped " + itemToDrop + ".")
            else:
                print("You do not have " + itemToDrop + " in your inventory!")

        if self.quit:
            wantToQuit = True
            
        return wantToQuit

    # implementations of user commands:

    '''Print out some help information. Here we print some stupid, cryptic message and a list of the command words.'''
    def printHelp(self):
        print("You are lost. You are alone. You wander")
        print("around on the space station.")
        print()
        print("Your command words are:")
        self.parser.showCommands()

    '''Try to go to one direction. If there is an exit, enter the new room, otherwise print an error message.'''
    def goRoom(self, command):
        if (not command.hasSecondWord()):
            # if there is no second word, we don't know where to go...
            print("Go where?")
            return

        direction = command.getSecondWord()

        if self.currentRoom.hasExit(direction) == False:
            print("You can't go " + direction + " from this room.")
            return

        # Try to leave current room.
        nextRoom = self.currentRoom.getExit(direction)

        if (nextRoom == None):
            print("There is no door!")
        else :
            
            if nextRoom.hasLock():
                lock_str = nextRoom.getLock()
            
                if lock_str in self.inventory:
                    print("You have accessed room using " + lock_str + ".")
                    self.currentRoom = nextRoom
                    print(self.currentRoom.getLongDescription())
                    
                    if self.currentRoom.getName() == "Zuul Room":
                        has_items = True
                        
                        if "zuul_manual" not in self.inventory:
                            has_items = False
                            print("You need the Zuul manual to turn on the power plant!")
                        else:
                            print("You have the Zuul manual!")
                            
                        if "toolkit" not in self.inventory:
                            has_items = False
                            print("You need a tool kit to help turn on the power plant!")
                            
                        if has_items:
                            self.zuulPoweredOn = True
                            print("Congratulations! You have turned on Zuul power plant!")
                            
                    if self.currentRoom.getName() == "Faraday Room":
                        has_items = True
                        
                        if "faraday_manual" not in self.inventory:
                            has_items = False
                            print("You need the Faraday manual to turn off the power plant!")
                            
                        if "toolkit" not in self.inventory:
                            has_items = False
                            print("You need a tool kit to help turn off the power plant!")
                            
                        if has_items:
                            self.faradayPoweredOn = False
                            print("Congratulations! You have turned off the damaged Faraday power plant!")                        
                        
                else:
                    print("Can't access room without " + lock_str + ".")
            else:
                self.currentRoom = nextRoom;
                print(self.currentRoom.getLongDescription())
                
                if self.currentRoom.getName() == "Transfer Room":
                    print("\n")
                    
                    if self.zuulPoweredOn == False:
                        print("You need to turn on Zuul power plant before transferring power!")
                    if self.faradayPoweredOn == True:
                        print("You need to turn off Faraday power plant before transferring power!")
                    
                    if self.zuulPoweredOn == True and self.faradayPoweredOn == False:
                        print("Congratulations! You successfully switched to the Zuul power plant")
                        print("and have restored power back to the space station!")
                        self.quit = True

    '''"Quit" was entered. Check the rest of the command to see whether we really quit the game. Return true, if this command quits the game, false otherwise.'''
    def quitGame(self, command):
        if (command.hasSecondWord()):
            print("Quit what?")
            return False
        else:
            return True  # signal that we want to quit

*/