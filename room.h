/*
Dylan Waters
11/5/25

Name : Room.h

Description : Room class header file for Zuul adventure game.

Note: This code is ported from the original Python version by galbraithja.
*/

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>
#include <vector>

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
    bool hasExit(string direction);

    // Define an exit from this room.
    void setExit(string direction, Room* neighbor);

    // Return the room that is reached if we go from this room in direction "direction". If there is no room in that direction, return null.
    Room* getExit(string direction);

    // add item to room
    void addItem(string item_str);

    // remove item from room
    void removeItem(string item_str);

    // does room have item?
    bool hasItem(string item_str);

    // set a lock on this room. Meaning you can't access this room without the key in your inventory
    void setLock(string lock_str);
    // get lock string for room
    string getLock();
    // does room have a lock?
    bool hasLock();

    // Return description of items in room
    string getItemsDescription();
    // Return the description of the room (the one that was defined.
    string getShortDescription();

    // Return a string describing the room's exits, for example "Exits: north west".
    string getExitString();

    // Return a long description of this room, in the form: 
    // You are in the kitchen.
    // Exits: north west
    string getLongDescription();

private:
    string name; // give rooms name so we can check for game conditions
    string description; // description of the room
    map<string, Room*> exits;  // stores exits of this room.
    vector<string> items;  // list of items in this room.
    string lock;   // key lock for this room
};

#endif // ROOM_H