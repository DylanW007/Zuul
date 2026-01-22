/*
Dylan Waters
11/5/25

Name : Room.h

Description : Room class header file for Zuul adventure game.

Note: This code is ported from the original Python version by galbraithja.
*/

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