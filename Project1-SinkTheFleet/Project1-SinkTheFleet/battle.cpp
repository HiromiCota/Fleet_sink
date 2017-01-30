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
	int new_target = 12;
	bool shotHit = false;
	//Prompt the player for where they want to shoot.
	do
	{
		shotHit = false;
		good_target = false;
		new_target = 12;
		while (!good_target)
		{
			targetLocation = inputTarget(size);

			//This line requires an overloaded inBounds()
			good_target = inBounds(targetLocation, size);
		}

		//Test to see if this target has been used before
		new_target = doubleTap(players, whichPlayer, targetLocation);
		switch (new_target)
		{
		case 0: break;
		case 1: cout << "You have already hit a ship at those coordinates. Try again." << endl;
			break;
		case 2: cout << "You have already missed at those coordinates. Try again." << endl;
			break;
		default:
			break;
		}

		//Check grid to determine hit status
		if (checkHit(players, whichPlayer, targetLocation))
		{
			cout << "HIT!" << endl;
			writeHit(players, whichPlayer, targetLocation);
			shotHit = true;
		}
		else
			cout << "Miss!" << endl;
	} while (shotHit);
	
		
	
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
	
	target.m_col = col - 1;
	target.m_row = static_cast<short>(row - 'A');
	return target;
}
bool checkHit(Player players[], short whichPlayer, Cell target)
{
	whichPlayer = !whichPlayer;
	if (players[whichPlayer].m_gameGrid[DEFENSE_GRID][target.m_row][target.m_col] != NOSHIP)
		return true;
	else
		return false;
}
int doubleTap(Player players[], short whichPlayer, Cell target)
{
	//Basically the converse of checkHit()
	Ship impact = players[whichPlayer].m_gameGrid[OFFENSE_GRID][target.m_row][target.m_col];
	if (impact == HIT)
		return 1; //Already attacked: Hit
	else if (impact == MISSED)
		return 2; //Already attacked: Missed
	else
		return 0; //New target location. Keep going
}
void writeMiss(Player players[], short whichPlayer, char size, Cell target)
{	
	//Write miss to player's [1] grid
	players[whichPlayer].m_gameGrid[OFFENSE_GRID][target.m_row][target.m_col] = MISSED;
}
void writeHit(Player players[], short whichPlayer, Cell target)
{
	
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
		cout << "Player " << !whichPlayer - 1 << "'s " <<
			players[!whichPlayer].m_ships[shipNameToNumber(damagedShip)].m_name <<
			" has been sunk!" << endl;
	}
		
	//Compute the total ship pieces
	if (--(players[!whichPlayer].m_piecesLeft) <= 0)
	{
		//end the game
		cout << "Player " << !whichPlayer << " has lost!";
	}	

}