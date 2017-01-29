//----------------------------------------------------------------------------
// File:	battle.cpp
// 
// Functions: 
//			takeTheShot()
//
//
//----------------------------------------------------------------------------
#include "battle.h"
void takeTheShot(Player players[], short whichPlayer, char size)
{
	Cell targetLocation = { 0, 0 };
	bool good_target = false;
	//Prompt the player for where they want to shoot.
	while (!good_target) 
	{
		targetLocation = getCoords(whichPlayer);
		
		//This line requires and overloaded inBounds()
		good_target = inBounds(targetLocation, size);
	}
	
	//Check grid to determine hit status
	if (checkHit(players, whichPlayer, size))
		writeHit(players, whichPlayer, size);
	
}
Cell getCoords(short whichPlayer)
{
	//Safely read in target coordinates
}
bool checkHit(Player players[], short whichPlayer, char size)
{
	//Check target coordinates against opposing player's grid
}
void writeMiss(Player players[], short whichPlayer, char size, Cell target)
{
	const short OFFENSE_GRID = 1;
	//Write miss to player's [1] grid
	players[whichPlayer].m_gameGrid[OFFENSE_GRID][target.m_row][target.m_col] = MISSED;
}
void writeHit(Player players[], short whichPlayer, char size)
{
	//If checkHit returns true, this writes the hit to 
	//the current player's [1] grid 
	
	//Read other player's [0] grid at that loc, 
	//decrement that ship's pieces

	//if pieces <=0 announce that ship is sunk

	//write to that player's [0] grid

	//Compute the total ship pieces

	//If <=0, trigger endgame

}