/*
Dylan Waters
11/5/25

Name : Room.h

Description : Room class header file for Zuul adventure game.

Note: This code is ported from the original Python version by galbraithja.
*/
#include <string>
#include <map>
#include <vector>
#include <algorithm>  // Reference: https://www.geeksforgeeks.org/cpp/std-find-in-cpp/

using namespace std;

// Class Room - a room in an adventure game.
class Room {
public:
    // Create a room described "description". Initially, it has no exits. "description" is something like "in a kitchen" or "in an open court yard".
    Room(string name, string description) {}
   ~Room() {}

    void setName(string name) { this->name = name; }
    string getName() { return name; }

    // add hasExits to test whether exit exists in room
    bool hasExit(string direction) {
        // Reference: https://cplusplus.com/reference/map/map/find/
        map<string, Room*>::iterator it;

        it = exits.find(direction);
        if (it != exits.end()) {
            return true;
        }
        return false;
    }

    // Define an exit from this room.
    void setExit(string direction, Room* neighbor) {
        exits[direction] = neighbor;
    }

    // Return the room that is reached if we go from this room in direction "direction". If there is no room in that direction, return null.
    Room* getExit(string direction) {
        // check if exit exists first using hasExit()
        if (hasExit(direction)) {
            // safe to return exit now
            return exits[direction];
        }
        return nullptr;
    }

    // add item to room
    void addItem(string item_str) {
        items.push_back(item_str);
    }

    // remove item from room
    void removeItem(string item_str) {
        if (hasItem(item_str) == false) {
            return; // item not in room
        }
        
        // Reference: https://stackoverflow.com/questions/40453469/removing-a-string-from-a-stdvector
        std::vector<string>::iterator itr = std::find(items.begin(), items.end(), item_str);
        if (itr != items.end()) {
            items.erase(itr);
        }
    }

    // does room have item?
    bool hasItem(string item_str) {
        // Reference: https://www.geeksforgeeks.org/check-if-an-element-is-present-in-a-vector-in-cpp/
        for (string item : items) {
            if (item == item_str) {
                return true;
            }
        }
        return false;
    }

    // set a lock on this room. Meaning you can't access this room without the key in your inventory
    void setLock(string lock_str) { lock = lock_str; }
    // get lock string for room
    string getLock() { return lock; }
    // does room have a lock?
    bool hasLock() { return lock != ""; }

    // Return description of items in room
    string getItemsDescription() { 
        string str = "\n";
        if (items.empty()) { //If no items...
            str += "No items seen in room. \n";
            return str;
        }
        
        str = "You see the following items..."; 
        for (string item : items) { //If items...
            str += "\n    " + item + " ";
        }
        str += "\n";
        return str;
    }
    // Return the description of the room (the one that was defined.
    string getShortDescription() { return description; }

    // Return a string describing the room's exits, for example "Exits: north west".
    string getExitString() { 
        string returnString = "Exits:";
        // Reference: https://medium.com/@ryan_forrester_/how-to-iterate-through-a-map-in-c-8aa459ea8bc5
        for (const auto& pair : exits) {
            returnString += " " + pair.first;
        }
        return returnString;
    }

    // Return a long description of this room, in the form: 
    // You are in the kitchen.
    // Exits: north west
    string getLongDescription() {
        return "You are " + description + ".\n" + getItemsDescription() + "\n" + getExitString();
    }

private:
    string name; // give rooms name so we can check for game conditions
    string description; // description of the room
    map<string, Room*> exits;  // stores exits of this room.
    vector<string> items;  // list of items in this room.
    string lock;   // key lock for this room
};
    

/*
# -*- coding: utf-8 -*-
'''
Created on Tue Apr 16 13:37:54 2024

@author: galbraithja

Class Room - a room in an adventure game.

This class is the main class of the "World of Zuul" application. "World of Zuul" is a very simple, text based adventure game.  

A "Room" represents one location in the scenery of the game.  It is connected to other rooms via exits.  For each existing exit, the room stores a reference to the neighboring room.

@author  Michael Kolling and David J. Barnes
@version 1.0 (February 2002)
'''
class Room:

    '''Create a room described "description". Initially, it has no exits. "description" is something like "in a kitchen" or "in an open court yard".'''
    def __init__(self, name, description):
        self.name = name # give rooms name so we can check for game conditions
        self.description = description
        self.exits = {}  # stores exits of this room.
        self.items = []  # list of items in this room.
        self.lock = ""   # key lock for this room

    '''Define an exit from this room.'''
    def setExit(self, direction, neighbor):
        self.exits[direction] = neighbor
    
    def setName(self, name):
        self.name = name
        
    def getName(self):
        return self.name
    
    # add hasExits to test whether exit exists in room
    def hasExit(self, direction):
        if direction in self.exits:
            return True
        return False
    
    # add item to room =======================================================
    def addItem(self, item_str):
        self.items.append(item_str)
        
    # remove item from room
    def removeItem(self, item_str):
        self.items.remove(item_str)
        
    # does room have item? ====================================================
    def hasItem(self, item_str):
        if item_str in self.items:
            return True
        return False
    
    # set a lock on this room. Meaning you can't access this room without the key in your inventory
    def setLock(self, lock_str):
        self.lock = lock_str
        
    # get lock string for room
    def getLock(self):
        return self.lock
        
    # does room have a lock?
    def hasLock(self):
        if len(self.lock) > 0:
            return True
        return False
    
    def getItemsDescription(self): 
        str = "\n"
        if not self.items: #If no items... ===================
            str += "No items seen in room. \n"
            return str
        
        str = "You see the following items..." 
        for item in self.items: #If items... ==================
            str += "\n    " + item + " "
        str += "\n"
        return str

    '''Return the description of the room (the one that was defined.'''
    def getShortDescription(self):
        return self.description

    '''Return a string describing the room's exits, for example "Exits: north west".'''
    def getExitString(self):
        returnString = "Exits:";
        for key in self.exits:
            returnString += " " + key
        return returnString

    '''Return a long description of this room, in the form: 
        You are in the kitchen.
        Exits: north west'''
    def getLongDescription(self):
        return "You are " + self.description + ".\n" + self.getItemsDescription() + "\n" + self.getExitString()

    '''Return the room that is reached if we go from this room in direction "direction". If there is no room in that direction, return null.'''
    def getExit(self, direction):
        return self.exits[direction]
    */