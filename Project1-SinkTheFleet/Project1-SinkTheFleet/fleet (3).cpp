//----------------------------------------------------------------------------
// File:	fleet.cpp
// 
// Functions: 
//	  setShipInfo()	
//	  allocMem() 
//	  deleteMem()
//	  printShip() 
//	  printGrid() 
//	  initializePlayer() 
//	  setships()	      
//	  saveGrid()
//	  getGrid()
//	  getCoord()
//	  validLocation() 
//	  header() 
//	  endBox() 
//----------------------------------------------------------------------------
#include "fleet.h"
//---------------------------------------------------------------------------------
// YOU ARE RESPONSIBLE FOR CORRECT HEADERS -- one for each function
// include the definitions for each of the non-template functions
//    declared in fleet.h 
//---------------------------------------------------------------------------------

const char* shipNames[SHIP_SIZE_ARRAYSIZE] = 
	{"No Ship", "Mine Sweeper", "Submarine", "Frigate",
		"Battleship", "Aircraft Carrier"};
const int TOTALPIECES = 17; // total pieces in all ships

//---------------------------------------------------------------------------------
// Function:	setShipInfo()
// Title:		Set ShipInfo
// Description:
//		Sets struct ShipInfo fields
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Intel Xeon PC 
//                Software:   MS Windows 7 for execution; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Calls:
//
// Called By:
//
// Parameters:	shipInfoPtr: ShipInfo *; pointer to the ShipInfo to be set
//				name: Ship;	enumerated name of type of ship; default: NOSHIP
//				orientation: Direction;	enumerated direction; default: HORIZONTAL
//				row: unsigned short; row-coordinate in grid; default: 0
//				col: unsigned short; column-coordinate in grid; default: 0
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//   
//---------------------------------------------------------------------------------
void setShipInfo(ShipInfo * shipInfoPtr, Ship name, Direction orientation,
	unsigned short row, unsigned short col)
{
	
} 

//---------------------------------------------------------------------------------
// Function:	allocMem()
// Title:		Allocate Memory
// Description:
//		allocates memory for current grids
// Programmer:	Paul Bladek
// modified by:	
// 
// Date:	9/13/06
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of 2 players in the game
//		size: char;	'	S' or 'L' (small or large)
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 1.0 
//		9/13/06  PB completed v 1.01
//
//---------------------------------------------------------------------------------
void allocMem(Player players[], char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS; //If we asked for large, give large. Else, give small.
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	try
	{
		for(short i = 0; i < NUMPLAYERS; ++i)  //First: Build pointers for the grids
		{
			players[i].m_gameGrid[0] = nullptr; //My ships
			players[i].m_gameGrid[1] = nullptr; //My attacks
			players[i].m_gameGrid[0] = new Ship*[numberOfRows];
			players[i].m_gameGrid[1] = new Ship*[numberOfRows];
			for(short j = 0; j < numberOfRows; ++j) //Second: Build pointers for the rows
			{
			//-------------------------------------------------
			//	your code goes here ...
			// set the pointers to NULL, then allocate the
			// memory for each row in each grid				
				players[i].m_gameGrid[0][j] = nullptr;
				players[i].m_gameGrid[1][j] = nullptr;
				//for testing
				if (j == 7)
					throw bad_alloc();
				players[i].m_gameGrid[0][j] = new Ship[numberOfCols];
				players[i].m_gameGrid[1][j] = new Ship[numberOfCols];

			//--------------------------------------------------
				for(short k = 0; k < numberOfCols; ++k) //Third: Fill values into each column in each row
				{
					players[i].m_gameGrid[0][j][k] = NOSHIP;
					players[i].m_gameGrid[1][j][k] = NOSHIP;
				} // end for k
			} // end for j
		} // end for i
	}
	catch(bad_alloc e)
	{
		deleteMem(players, size);
		cerr << "exception: " << e.what() << endl;
		cout << "shutting down" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		exit(EXIT_FAILURE);
	}
}

//---------------------------------------------------------------------------------
// Function:	deleteMem()
// Title:		Delete Memory
// Description:
//		Safely deletes memory for grids
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of the 2 Players
//		size: char;	'	S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//   
//---------------------------------------------------------------------------------
void deleteMem(Player players[], char size) 
{	
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	// your code goes here ...
	// delete[] in reverse order of allocMem()
	// be sure to check if the memory was allocated (!nullptr) BEFORE deleting
	try
	{
		for (short i = 0; i < NUMPLAYERS; i++)
		{
			for (short j = 0; j < numberOfRows; j++)
			{
				//We don't need to clear the columns because the columns 
				//are actually values within the row arrays.

				//First: Free the memory used by the rows.
				delete players[i].m_gameGrid[0][j];
				delete players[i].m_gameGrid[1][j];
			}
			//Second: Free the memory used by the grids.
			delete players[i].m_gameGrid[0];
			delete players[i].m_gameGrid[1];
		}
	}
	catch (exception ex)
	{
		//How the hell did we break something while cleaning up memory?
		cerr << "exception: " << ex.what() << endl;
		cout << "Error clearing memory.";
		cin.ignore(BUFFER_SIZE, '\n');
		exit(EXIT_FAILURE);
	}

}

//---------------------------------------------------------------------------------
// Function:	printShip()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:		three characters representing one ship to sout
//
// Calls:
//
// Called By:	printGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//				thisShip: Ship;	the Ship to be printed in the grid format
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void printShip(ostream & sout, Ship thisShip)
{	
	sout << ' ' ;
	switch(thisShip)
	{
		case NOSHIP: sout << ' ';
			break;
		case MINESWEEPER: sout << 'M';
			break;
		case SUB: sout << 'S';
			break;
		case FRIGATE: sout << 'F';
			break;
		case BATTLESHIP: sout << 'B';
			break;
		case CARRIER: sout << 'C';
			break;
		case HIT: sout << 'H';
			break;
		case MISSED: sout << MISS;
			break;
		default: sout << 'X';
	}
	sout << VERT ;
}

//---------------------------------------------------------------------------------
// Function:	printGrid()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	a single grid to sout
//
// Calls:	printShip()
//
// Called By:	main()
//		setships()
//		saveGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//		grid: Ship**;	the 2-D array of Ships 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//     
//---------------------------------------------------------------------------------
void printGrid(ostream& sout, Ship** grid, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	for(short j = 1; j <= numberOfCols; ++j)
		sout << setw(3) << j;
	sout  << endl;
	// your code goes here ...
	// use printShip for each element in the grid


} 

//---------------------------------------------------------------------------------
// Function:	initializePlayer()
// Title:	Initialize Player 
// Description:
//		sets initial values for m_ships and m_piecesLeft
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls:
//
// Called By:	main()
//
// Parameters:	playerPtr: Player*;	a pointer to the current Player
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void initializePlayer(Player* playerPtr)
{
	for(short i = 0; i < SHIP_SIZE_ARRAYSIZE; i++)
		setShipInfo(playerPtr->m_ships + i, static_cast<Ship>(i));
	
	playerPtr->m_piecesLeft = TOTALPIECES; 
}

//---------------------------------------------------------------------------------
// Function:	setships()
// Title:	Set Ships 
// Description:
//		Allows user to put ships in grid
// Programmer:	Paul Bladek
// modified by:	Hiromi Cota
// 
// Date:		1/18/2017
//
// Version:	0.6
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:	location and orientation using getCoord from cin
//
// Output:	prompts to cout
//
// Calls:	printGrid()
//		safeChoice()
//		getCoord()
//		saveGrid()
//
// Called By:	main()
//
// Parameters:	players: Player[];	the array of 2 players 
//		size: char;		'S' or 'L'
//		whichPlayer: short;	the player number (0 or 1)
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 0.5
//		1/18/17 HRC completed v 0.6 (Fully functional)
//     
//---------------------------------------------------------------------------------
void setships(Player players[], char size, short whichPlayer)
{
	char input = 'V';
	char ok = 'Y';
	char save = 'N';
	ostringstream outSStream;
	Cell location = {0, 0};
	Ship thisShip = NOSHIP;
	
	for(short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++)
	{
		thisShip = getShip(j);
		system("cls"); //Windows specific command. This must change if we want to support other OSes.
		printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
		outSStream.str("");
		outSStream << "Player " << whichPlayer + 1 << " Enter "
			<< shipNames[j] << " orientation";
		input = safeChoice(outSStream.str(), 'V', 'H');
		players[whichPlayer].m_ships[j].m_orientation
			= (input == 'V') ? VERTICAL : HORIZONTAL;
		cout << "Player " << whichPlayer + 1 << " Enter " << shipNames[j] <<
			" bow coordinates <row letter><col #>: ";
		players[whichPlayer].m_ships[j].m_bowLocation = getCoord(cin, size);

		if (inBounds(players[whichPlayer], j, size))
		{
			//It's in the grid, at least.
			if (j == 1)
			{
				//No collision possible. Just draw it.
				putShip(players[whichPlayer], j);
			}
			else
			{
				//Collision possible. Test it
				if (noCollision(players[whichPlayer], j))
				{
					putShip(players[whichPlayer], j);
				}
				else
				{
					//Collision! Yell at the user!
					cout << "Ship is on top of another ship. Press <enter> to retry";
					cin.get();
					j--; // redo
					continue;
				}
			}
		}
		else
		{
			//Out of bounds. Yell loudly.
			cout << "Ship is outside the grid. Press <enter> to retry";
			cin.get();
			j--; // redo
			continue;
		}
	} // end ship placing block
	save = safeChoice("\nSave starting grid?", 'Y', 'N');
	if(save == 'Y')
		saveGrid(players, whichPlayer, size);
}
void putShip(Player& player, short shipNumber)
{
	Ship thisShip = getShip(shipNumber);

	if (player.m_ships[shipNumber].m_orientation == VERTICAL)
	{
		//Loop vertically
		for (int i = 0; i < shipSize[shipNumber]; i++)
		{
			player.m_gameGrid[0][bowLoc(player, shipNumber, VERTICAL) + i][(player, shipNumber, HORIZONTAL)] =
				thisShip;
		}
	}
	else //Loop horizontally
	{
		for (int i = 0; i < shipSize[shipNumber]; i++)
		{
			player.m_gameGrid[0][bowLoc(player, shipNumber, VERTICAL)][(player, shipNumber, HORIZONTAL + i)] =
				thisShip;
		}
	}
}

//---------------------------------------------------------------------------------
// Function:	getShip()
// Title:		Get Ship
// Description:	Returns the type of ship
// Programmer:	Hiromi Cota
// 
// Date:		1/18/17
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	No visual output
//
// Calls:	none
//
// Called By:	setships()
//				putShip()
//
// Parameters:	shipNumber - Short, defines which ship type
// 
// Returns:	Ship object
//
// History Log:
//		1/18/17 HRC completed v 0.1
//     
//---------------------------------------------------------------------------------
Ship getShip(short shipNumber)
{
	switch (shipNumber)
	{
	case 1: return MINESWEEPER;
	case 2: return SUB;
	case 3: return FRIGATE;
	case 4: return BATTLESHIP;
	case 5: return CARRIER;
	default: return NOSHIP;
	}
}
//---------------------------------------------------------------------------------
// Function:	saveGrid()
// Title:	Save Grid 
// Description:
//		Saves the ship grid to a file
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	grid to specified file
//
// Calls:	printGrid()
//
// Called By:	setships()
//
// Parameters:	player: sPlayer[];	the array of 2 players
//		whichPlayer: short; the player number (0 or 1) 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//     
//---------------------------------------------------------------------------------
void saveGrid(Player players[], short whichPlayer, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;	
	// your code goes here ...
	
}

//---------------------------------------------------------------------------------
// Function:	getGrid()
// Title:	GetGrid 
// Description:
//		Reads grid from a file and properly sets the ships
// Programmer:	Paul Bladek
// modified by:	
// 
// Date:	9/12/06
//
// Version:	0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:	grid from specified file
//
// Output:	prompts to cout
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[];	the array of 2 players
//		whichPlayer: short;	the player number  (0 or 1) 
//		size: char;		'S' or 'L'
//		string fileName:	the name of the file to be opened for reading
// 
// Returns: bool -- 	true if the file is opened and read;
//			false otherwise
//
// History Log: 
//		9/12/06 PB comleted v 0.5
//     
//---------------------------------------------------------------------------------
bool getGrid(Player players[], short whichPlayer, char size, string fileName)
{
	string line;
	ifstream ifs;
	Ship ship = NOSHIP;
	short shipCount[SHIP_SIZE_ARRAYSIZE] = {0};
	char cell = ' ';
	char fsize = 'S';
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	try
	{
		ifs.open(fileName.c_str());
		if(!ifs)
		{
			cout << "could not open file " << fileName << endl
				<< " press <enter> to continue" << endl;
			cin.ignore(BUFFER_SIZE, '\n');
			return false;
		}
	}
	catch(exception e)
	{
		cout << "could not open file " << fileName << endl
			<< " press <enter> to continue" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		return false;
	}	
	// your code goes here ...
	

	return true;
}

//---------------------------------------------------------------------------------
// Function:	getCoord()
// Title:	Get Coordinates 
// Description:
//		Returns a cell with coordinates set by user
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:	cell coordinates (in the form "A13" from sin
//
// Output:	prompts to cout
//
// Calls:	none
//
// Called By:	main()
//		setships()
//
// Parameters:	sin: istream&;	the stream to read from
//		size: char;	'S' or 'L'
// 
// Returns:	Cell location -- a cell containing the input coordinates
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
Cell getCoord(istream& sin, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	char highChar = static_cast<char>(numberOfRows - 1) + 'A';
	char row  = 'A';
	short col = 0;
	Cell location = {0, 0};
	do
	{
		col = 0;
		cout << "Row must be a letter from A to " << highChar 
			<< " and column must be  from 1 to "  << numberOfCols << ": ";
		while((row = toupper(sin.get())) < 'A' || row  > highChar)
		{
			sin.ignore(BUFFER_SIZE, '\n');
			cout << "Row must be a letter from A to " << highChar 
				<< " and column must be  from 1 to "  << numberOfCols << ": ";
		}
		sin >> col;
		if(!sin)
			sin.clear();
		sin.ignore(BUFFER_SIZE, '\n');
	}
	while(col < 1 || col > numberOfCols);
	
	location.m_col = col - 1;
	location.m_row = static_cast<short>(row - 'A');
	return location;
}

//---------------------------------------------------------------------------------
// Function:	validLocation()
// Title:	Valid Location 
// Description:
//		Can the ship legitimately go there?
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls:		inBounds()
//
// Called By:
//
// Parameters:	player: const Player&;	a reference to the specific Player
//				shipNumber: short;	the number of the ship (1 - 5)
//					in the array player.m_ships[]
//				size: char;		'S' or 'L'
// 
// Returns: bool -- 	true if the ship would not go off the edge
//							or cross another ship;
//						false otherwise
//
// History Log:
//		12/20/05 PB completed v 0.1
//		1/17/17 HRC	Testing in bounds seperately 
//		1/18/17	HRC DEPRECATED! Split to noCollision() & inBounds()
//---------------------------------------------------------------------------------
bool validLocation(const Player& player, short shipNumber, char size)
{
	//This function is deprecated.
	//	In bounds testing was pushed to inBounds() since the first 
	//	ship never needs to be checked for collision.
	//	Collision testing was pushed to noCollision() because I was
	//	on a roll and didn't notice that I obviated this function until now.

	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	bool is_valid_location = false;
	
	for (short i = 0; i < shipNumber - 1//Because ship numbers start at 1
		; i++) //loop through each of ships
	{
		if (inBounds(player, shipNumber, size) == true)
		{
			//Then check to see if ships cross
			if (noCollision(player, shipNumber, size) == true)
			{
				is_valid_location = true;
			}			
		} //is_valid_location defaults to false, so there's no need for else statements.		
	}

	// replace the return value
	return is_valid_location;
}

//---------------------------------------------------------------------------------
// Function:	inBounds()
// Title:	In Bounds?
// Description:
//				Is the ship even on the map?
// Programmer:
//				Hiromi Cota
// Date:	1/17/2017
//
// Version:	0.2
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls:		
//
// Called By: validLocation()
//
// Parameters:	player: const Player&;	a reference to the specific Player
//				shipNumber: short;	the number of the ship (1 - 5)
//					in the array player.m_ships[]
//				size: char;		'S' or 'L'
// 
// Returns: bool -- 	true if the ship would not go off the edge
//							or cross another ship;
//						false otherwise
//
// History Log:
//		1/13/2017 HRC completed v 0.1
//	    1/17/2017 HRC completed v 0.2 (optimized loops out of existence & added bad_orient)
//---------------------------------------------------------------------------------
bool inBounds(const Player& player, short shipNumber, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	
	bool onBoard = true; //Assume true until we break it.
	
	class myexception : public exception
	{
		virtual const char* what() const throw()
		{
			return "Somehow the ship is neither horizontal nor vertical.";
		}
	} bad_orient;


	//First, check that the bow position is in the grid

	//get orientation of the ship
	try
	{
		if (player.m_ships[shipNumber].m_orientation == HORIZONTAL)
		{
			if ((player.m_ships[shipNumber].m_bowLocation.m_row >= numberOfRows) ||
				(player.m_ships[shipNumber].m_bowLocation.m_row < 0)
				//The bow location is out of bounds.
				||
				(player.m_ships[shipNumber].m_bowLocation.m_row + shipSize[shipNumber] -1 >= numberOfRows)
				//The stern location is out of bounds.
				//Note: -1 is required because shipSize starts at 1, not 0.
				//Note 2: No need to check if the stern is below 0, because we already checked the bow.
				)
				onBoard = false;				
		}
		else if (player.m_ships[shipNumber].m_orientation == VERTICAL)
		{
			if ((player.m_ships[shipNumber].m_bowLocation.m_col >= numberOfCols) ||
				(player.m_ships[shipNumber].m_bowLocation.m_col < 0)
				//The bow location is out of bounds.
				||
				(player.m_ships[shipNumber].m_bowLocation.m_col + shipSize[shipNumber] -1  >= numberOfCols))
				//The stern location is out of bounds.
				onBoard = false;		
		}
		else
		{
			//m_orientation not set
			throw bad_orient;
			//How the hell did you do that?!
		}
	
	}
	catch (const std::exception&)
	{
		cout << bad_orient.what << endl;
		//This should never actually happen.
		//I just wanted practice building custom exception classes.
	}

	return onBoard;
}
//---------------------------------------------------------------------------------
// Function:	noCollision()
// Title:		No Collision?
// Description:	Will the new ship hit anything already on the board?
// Programmer:	Hiromi Cota
// Date:		1/18/2017
//
// Version:	0.3
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls:		
//
// Called By: validLocation()
//
// Parameters:	player: const Player&;	a reference to the specific Player
//				shipNumber: short;	the number of the ship (1 - 5)
//					in the array player.m_ships[]
//				
// 
// Returns: bool -- 	true if the ship will not cross another ship
//							or cross another ship;
//						false otherwise
//
// History Log:
//		1/13/2017 HRC completed v 0.1
//	    1/17/2017 HRC completed v 0.2 (optimized loops)
//		1/18/2017 HRC completed v 0.3 (Threw old loops in trash; now fully functional)
//---------------------------------------------------------------------------------
bool noCollision(const Player& player, short shipNumber)
{	
	bool noWreck = true; //Assume true until we break it.
	Ship thisShip = getShip(shipNumber);

	if (player.m_ships[shipNumber].m_orientation == VERTICAL)
	{
		//Loop vertically
		for (int i = 0; i < shipSize[shipNumber]; i++)
		{
			if (player.m_gameGrid[0][bowLoc(player, shipNumber, VERTICAL) + i][(player, shipNumber, HORIZONTAL)] !=
				NOSHIP)
				noWreck = false;
		}
	}
	else //Loop horizontally
	{
		for (int i = 0; i < shipSize[shipNumber]; i++)
		{
			if (player.m_gameGrid[0][bowLoc(player, shipNumber, VERTICAL)][(player, shipNumber, HORIZONTAL + i)] !=
				NOSHIP)
				noWreck = false;
		}
	}
		
	return noWreck;
}
//---------------------------------------------------------------------------------
// Function:	bowLoc()
// Title:		Bow Location
// Description:
//				Returns bow location on requested axis
// Programmer:	Hiromi Cota
// 
// Date:		1/17/2017
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	
//
// Calls:	
//
// Called By:	noCollision()
//
// Parameters:	
// Parameters:	
//					player: const Player&;	a reference to the specific Player
//					shipNumber: short;	the number of the ship (1 - 5)
//						in the array player.m_ships[]
//					Direction: enum; HORIZONTAL returns the X coords
//									VERTICAL returns the Y coords
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
int bowLoc(const Player& player, short shipNumber, Direction direction)
{
	//This function probably doesn't make my code any more efficient,
	//but it's less annoying to type.
	if (direction == HORIZONTAL)
	{
		return (player.m_ships[shipNumber].m_bowLocation.m_col);		
	}
	else
	{
		return (player.m_ships[shipNumber].m_bowLocation.m_row);
	}		
}

//---------------------------------------------------------------------------------
// Function:	header()
// Title:	header 
// Description:
//		Prints opening graphic
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	sout: ostream&;	the stream to print to
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void header(ostream& sout)
{
	const string empty;
	const string sink("SINK THE FLEET!");
	// your name goes here!
	const string by("Edmonds Community College CS 132");
	boxTop(sout, BOXWIDTH);
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, sink , BOXWIDTH, 'C');
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, by, BOXWIDTH, 'C');
	boxLine(sout, empty, BOXWIDTH);
	boxBottom(sout, BOXWIDTH);
}

//---------------------------------------------------------------------------------
// Function:	endBox()
// Title:	End Box 
// Description:
//		prints closinging graphic
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	player: short; the number of the winner (0 or 1)
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void endBox(short player)
{
	const string empty;
	ostringstream msg;
	msg << "Congratulations player " << player + 1 << "!";
	boxTop(cout, BOXWIDTH);
	boxLine(cout, empty, BOXWIDTH);
	boxLine(cout, msg.str() , BOXWIDTH, 'C');
	boxLine(cout, empty, BOXWIDTH);
	boxBottom(cout, BOXWIDTH);
}

