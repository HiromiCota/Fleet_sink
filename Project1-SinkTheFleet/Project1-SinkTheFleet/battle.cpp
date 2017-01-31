//----------------------------------------------------------------------------
// File:	battle.cpp
// 
// Functions: 
//			takeTheShot()
//
//
//----------------------------------------------------------------------------
#include "battle.h"

//---------------------------------------------------------------------------------
// Function:	takeTheShot()
// Title:		Take the Shot!
// Description:
//				Handles cannon firing from input to sinking ships
// Programmer:	Hiromi Cota
// 
// Date:		1/30/2017
//
// Version:		1.0
//
// Input: Accepts characters to cin to unpause
//
// Output:	Status updates to cout
//
// Calls:	getCoord()
//			printGrid()
//			checkHit()
//			writeHit()
//			writeMiss()
//
// Called By:	main()
//
// Parameters:	players[]: player; where the game is
//				whichPlayer: short; the number of the winner (0 or 1)
//				size: char; size of game board
// 
// Returns:	bool - true if the current player's turn should end
//
// History Log: 
//		1/20/17	HRC Completed v 0.1
//		1/22/17 HRC Completed v 0.2 (rewrote function)
//		1/28/17 HRC Completed v 0.3 (now pauses correctly)
//---------------------------------------------------------------------------------
bool takeTheShot(Player players[], short whichPlayer, char size)
{
	Cell targetLocation = { 0, 0 };
	bool good_target = false;
	bool new_target = false;
	bool endOfTurn = false;
	
	//Forces player to pick a target inside the grid && 
	//one that hasn't been shot at before.
	while (!good_target || !new_target)
	{
		good_target = false;
		new_target = false;

		system("cls");
		cout << "Player " << whichPlayer + 1 << ": It's your turn!" << endl;
		printGrid(cout, players[whichPlayer].m_gameGrid[OFFENSE_GRID], size);

		//Get input	
		targetLocation = getCoord(cin, size);

		//This line requires an overloaded inBounds()
		//Check to see if it's in bounds
		good_target = inBounds(targetLocation, size);
	
		//Test to see if this target has been used before
		new_target = doubleTap(players, whichPlayer, targetLocation);
	}	
	
	//Check grid to determine hit status
	if (checkHit(players, whichPlayer, targetLocation))
	{
		//Hit. Tell the player		
		writeHit(players, whichPlayer, targetLocation);
		cout << "HIT!" << endl;
		cout << "Press enter to to take another turn." << endl;
		cin.get();
	}
	else
	{
		writeMiss(players, whichPlayer, targetLocation);
		cout << "Miss!" << endl;
		cout << "Press enter to complete your turn." << endl;
		cin.get();
		endOfTurn = true;
	}

	//Also require that there be valid targets left
	if (players[!whichPlayer].m_piecesLeft <= 0)
		endOfTurn = true;
	
	return endOfTurn;
}

//---------------------------------------------------------------------------------
// Function:	checkHit()
// Title:		Check Hit
// Description:
//		checks to see if the shot hit a ship
// Programmer:	Hiromi Cota
// 
// Date:	1/17/17
//
// Version:	1.0
// 
// Output:	nothing to screen
//
// Calls:	nothing
//
// Called By:	takeTheShot()
//
// Parameters:	players[]: Player; the game
//				whichPlayer: short; the number of the player (0 or 1)
//				target: Cell; where the shot is going
// 
// Returns:	bool - true if hit, false if miss
//
// History Log: 
//		1/17/2017 - HRC Completed v 1.0
//     
//---------------------------------------------------------------------------------
bool checkHit(Player players[], short whichPlayer, Cell target)
{
	whichPlayer = !whichPlayer;
	if (players[whichPlayer].m_gameGrid[DEFENSE_GRID][target.m_row][target.m_col] != NOSHIP)
		return true;
	else
		return false;
}
//---------------------------------------------------------------------------------
// Function:	doubleTap()
// Title:		Double Tap?
// Description:
//		Is this a double tap? 
//		Checks to see if these coordinates have been used already
// Programmer:	Hiromi Cota
// 
// Date:	1/28/17
//
// Version:	1.0
// 
// Output:	Mocks players for reusing coordinates
//
// Calls:	nothing
//
// Called By:	takeTheShot()
//
// Parameters:	players[]: Player; the game
//				whichPlayer: short; the number of the player (0 or 1)
//				target: Cell; where the shot is going)
// 
// Returns:	bool - false if already used, true if a good location
//
// History Log: 
//		1/28/17	- HRC Completed v 1.0
//     
//---------------------------------------------------------------------------------
bool doubleTap(Player players[], short whichPlayer, Cell target)
{
	//Basically the converse of checkHit()
	Ship impact = players[whichPlayer].m_gameGrid[OFFENSE_GRID][target.m_row][target.m_col];
	if (impact == HIT)
	{
		cout << "You have already hit a ship at those coordinates. Try again." << endl;
		return false;
	}
	else if (impact == MISSED)
	{
		cout << "You have already missed at those coordinates. Try again." << endl;
		return false;
	}
	else
		return true; //New target location. Keep going
}
//---------------------------------------------------------------------------------
// Function:	writeMiss()
// Title:		Write Miss
// Description:
//		Writes miss data to current player's Offense grid
// Programmer:	Hiromi
// 
// Date:	1/17/17
//
// Version:	1.0
//
// Output:	nothing to screen
//
// Calls:	nothing
//
// Called By:	takeTheShot()
//
// Parameters:	players[]: Player; the game
//				whichPlayer: short; the number of the player (0 or 1)
//				target: Cell; where the shot is going
// 
// Returns:	void
//
// History Log: 
//				1/17/17	HRC Completed v 1.0     
//---------------------------------------------------------------------------------
void writeMiss(Player players[], short whichPlayer, Cell target)
{	
	//Write miss to player's [1] grid
	players[whichPlayer].m_gameGrid[OFFENSE_GRID][target.m_row][target.m_col] = MISSED;
}
//---------------------------------------------------------------------------------
// Function:	writeHit()
// Title:		Write Hit
// Description:
//		Writes hit data to current player's Offense grid
// Programmer:	Hiromi
// 
// Date:	1/17/17
//
// Version:	1.0
//
// Output:	Tells players if something got sunk or if someone lost
//
// Calls:	nothing
//
// Called By:	takeTheShot()
//
// Parameters:	players[]: Player; the game
//				whichPlayer: short; the number of the player (0 or 1)
//				target: Cell; where the shot is going
// 
// Returns:	void
//
// History Log: 
//				1/17/17	HRC Completed v 1.0     
//---------------------------------------------------------------------------------
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
		cout << "Player " << !whichPlayer + 1 << "'s " <<
			shipNames[shipNameToNumber(damagedShip)] <<
			" has been sunk!" << endl;
	}
		
	//Compute the total ship pieces
	if (--(players[!whichPlayer].m_piecesLeft) <= 0)
	{
		//end the game
		cout << "Player " << !whichPlayer + 1 << " has lost!";
	}	

}