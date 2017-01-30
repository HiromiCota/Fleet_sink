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
	{
		cout << "HIT!" << endl;
		writeHit(players, whichPlayer, targetLocation);
	}
	else
		cout << "Miss!" << endl;
		
	
}
Cell inputTarget(char size)
{
	//Safely read in target coordinates
	string rowOptions = (toupper(size) == 'L') ? "(ABCDEFGHIJ)" : "(ABCDEFGH)";
	string colOptions= (toupper(size) == 'L') ? "(1-24)" : "(1-12)";
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	char highChar = (toupper(size) == 'L') ? 'J' : 'H';

	string prompt1 = "Please enter a row letter ";
	string prompt2 = "Please enter a column number ";

	bool goodCol = false;
	bool goodRow = false;
	Cell target = { 0,0 };
	char inputChar = '\0';
	short col = 0;
	char row = 'A';


	cout << "It's your turn to attack. Pick a target: " << endl;
	do
	{
		col = 0;
		cout << "Row must be a letter from A to " << highChar 
			<< " and column must be from 1 to "  << numberOfCols << endl;
		while ((row = toupper(cin.get())) < 'A' || row  > highChar)
		{
			cin.ignore(BUFFER_SIZE, '\n');
			cout << "Row must be a letter from A to " << highChar
				<< " and column must be from 1 to " << numberOfCols << ": ";
		}
		cin >> col;
		if (!cin)
			cin.clear();
		cin.ignore(BUFFER_SIZE, '\n');
	} while (col < 1 || col > numberOfCols);
	
	/*while (goodCol == false)
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
	}*/
	target.m_col = col - 1;
	target.m_row = static_cast<short>(row - 'A');
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