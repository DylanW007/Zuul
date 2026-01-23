/*
Dylan Waters
11/5/25

Name : main.cpp

Description : Main file for Zuul adventure game.

Note: This code is ported from the original Python version by Dylan Waters.
*/

#include "command.h"
#include "commandwords.h"
#include "room.h"
#include "game.h"

using namespace std;

// Main function to start the game
int main() {
    Game game;
    game.play();
    return 0;
}

