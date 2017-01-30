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
		targetLocation = inputTarget(size);
		
		//This line requires and overloaded inBounds()
		good_target = inBounds(targetLocation, size);
	}
	
	//Check grid to determine hit status
	if (checkHit(players, whichPlayer, targetLocation))
		writeHit(players, whichPlayer, targetLocation);
	
}
Cell inputTarget(char size)
{
	//Safely read in target coordinates
	string rowOptions = (toupper(size) == 'L') ? "(ABCDEFGHIJ)" : "(ABCDEFGH)";
	string colOptions= (toupper(size) == 'L') ? "(1-23)" : "(1-11)";
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	string prompt1 = "Please enter a row letter ";
	string prompt2 = "Please enter a column number ";

	bool goodCol = false;
	bool goodRow = false;
	Cell target;
	char inputChar = '\0';
	short inputCol = 0;

	while (goodCol == false)
	{
		while (goodRow == false)
		{
			cout << prompt1 << rowOptions;
			cin.get(inputChar);
			inputChar = toupper(inputChar);

			if (inputChar <= 'A' && inputChar < 'A' + numberOfRows)
			{
				goodRow = true;
				target.m_row = inputChar - 'A';
			}
		}
		cout << prompt2 << colOptions;
		cin >> inputCol;
		
		if (inputCol >= 0 && inputCol < numberOfCols + 1)
		{
			goodCol = true;
			target.m_col = inputCol;
		}
	}
	return target;
}
bool checkHit(Player players[], short whichPlayer, Cell target)
{
	if (players[!whichPlayer].m_gameGrid[0][target.m_row][target.m_col] != NOSHIP)
		return true;
	else
		return false;

}
void writeMiss(Player players[], short whichPlayer, char size, Cell target)
{
	const short OFFENSE_GRID = 1;
	//Write miss to player's [1] grid
	players[whichPlayer].m_gameGrid[OFFENSE_GRID][target.m_row][target.m_col] = MISSED;
}
void writeHit(Player players[], short whichPlayer, Cell target)
{
	const short OFFENSE_GRID = 1;
	const short DEFENSE_GRID = 0;
	Ship damagedShip;
	//If checkHit returns true, this writes the hit to 
	//the current player's [1] grid 
	players[whichPlayer].m_gameGrid[OFFENSE_GRID][target.m_row][target.m_col] = HIT;
	
	//Read other player's [0] grid at that loc, 
	//decrement that ship's pieces
	damagedShip = players[!whichPlayer].m_gameGrid[DEFENSE_GRID][target.m_row][target.m_col];
		
	//if pieces <=0 announce that ship is sunk
	if (--(players[!whichPlayer].m_ships[shipNameToNumber(damagedShip)].m_piecesLeft) <= 0)
	{
		//Tell players
	}
		
	//Compute the total ship pieces
	if (--(players[!whichPlayer].m_piecesLeft) <= 0)
	{
		//end the game
	}	

}