//----------------------------------------------------------------------------
// File:		battle.h
// 
// Description: Sink the Fleet declarations for while(!gameOver) loop
//	
// Programmer:	Hiromi Cota
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//----------------------------------------------------------------------------
#ifndef BATTLE_H
#define BATTLE_H

#include <cstdlib>

#include "fleet.h"


//This could probably all go into the fleet.h and fleet.cpp files, 
//but they were getting long, and dividing up code into chunks is cleaner

//
//Start each player's turn
void takeTheShot(Player players[], short whichPlayer, char size);
//Safely read in target coordinates
Cell inputTarget(char size);
//Check to see if a ship gets hit
bool checkHit(Player players[], short whichPlayer, Cell target);
//Mark the hit on the grids.
void writeHit(Player players[], short whichPlayer, Cell target);

#endif // !BATTLE_H

