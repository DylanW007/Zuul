/*
Dylan Waters
11/5/25

Name : Room.cpp

Description : Room class implementation file for Zuul adventure game.

Note: This code is ported from the original Python version by galbraithja.
*/
#include "room.h"

#include <iostream>

#include <algorithm>  // Reference: https://www.geeksforgeeks.org/cpp/std-find-in-cpp/

using namespace std;

Room::Room(string name, string description) {
    this->name = name;
    this->description = description;
    this->lock = "";
}

// add hasExits to test whether exit exists in room
bool Room::hasExit(string direction) {
    // Reference: https://cplusplus.com/reference/map/map/find/
    map<string, Room*>::iterator it;

    it = exits.find(direction);
    if (it != exits.end()) {
        return true;
    }
    return false;
}

// Define an exit from this room.
void Room::setExit(string direction, Room* neighbor) {
    exits[direction] = neighbor;
}

// Return the room that is reached if we go from this room in direction "direction". If there is no room in that direction, return null.
Room* Room::getExit(string direction) {
    // check if exit exists first using hasExit()
    if (hasExit(direction)) {
        // safe to return exit now
        return exits[direction];
    }
    return nullptr;
}

// add item to room
void Room::addItem(string item_str) {
    items.push_back(item_str);
}

// remove item from room
void Room::removeItem(string item_str) {
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
bool Room::hasItem(string item_str) {
    // Reference: https://www.geeksforgeeks.org/check-if-an-element-is-present-in-a-vector-in-cpp/
    for (string item : items) {
        if (item == item_str) {
            return true;
        }
    }
    return false;
}

// set a lock on this room. Meaning you can't access this room without the key in your inventory
void Room::setLock(string lock_str) { lock = lock_str; }
// get lock string for room
string Room::getLock() { return lock; }
// does room have a lock?
bool Room::hasLock() { return lock != ""; }

// Return description of items in room
string Room::getItemsDescription() { 
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
string Room::getShortDescription() { return description; }

// Return a string describing the room's exits, for example "Exits: north west".
string Room::getExitString() { 
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
string Room::getLongDescription() {
    cout << "getLongDescription called" << endl;
    cout << "description: " << description << endl;
    cout << "items description: " << getItemsDescription() << endl;
    cout << "exit string: " << getExitString() << endl << endl;

    return "You are " + description + ".\n" + getItemsDescription() + "\n" + getExitString();
}
