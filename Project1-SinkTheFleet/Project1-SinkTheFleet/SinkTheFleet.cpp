//----------------------------------------------------------------------------
// File:	SinkTheFleetleet.cpp
// 
// Function:
//      main()
//----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include "fleet.h"
#include "battle.h"

using namespace std;
extern const char* shipNames[6];
//---------------------------------------------------------------------------------
// Function:	main()
// Title:		Set ShipInfo
// Description:
//				Runs the Sink the Fleet Game
// Programmer:	Paul Bladek
// modified by:
// 
// Date:		12/9/2010
//
// Version:		0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:		
//
// Output:		
//
// Calls:		initializePlayer()
//				allocMem()
//				safeChoice()
//				getGrid()
//				printGrid()
//				resetGrid()
//				setships()
//				header()
//				getCoord()
//				deleteMem()
//				endBox()
//
// Called By:	n/a
//
// Parameters:	void
// 
// Returns:		int -- EXIT_SUCCESS upon successful completion
//
// History Log: 
//				12/9/2010 PB completed v 0.5
//				1/20/2017 - 1/30/2017 (many commits that I forgot to document)
//				1/30/2017 HRC Completed v 1.0 (final)
//   
//---------------------------------------------------------------------------------
int main(void)
{
	short numRows = SMALLROWS;			// total number of rows in the array
	short numCols = SMALLCOLS;			// total number of columns in the array
	char again = 'N';
	char gridSize = 'S';
	short whichPlayer = 0;
	bool gameOver = false;
	bool reshot = false;
	Cell coord = {0, 0};
	string message;
	string filename;
	Ship shipHit = NOSHIP;
	Player game[NUMPLAYERS] ;	//The highest level of the struct tree
	char loadFromFile = false;	
	bool gridComplete = false;
	bool turnOver = false;
	int fileReturn = 0;
	char goodGridInput = '\0';

	do
	{
		system("cls");
		cout << endl;
		header(cout);
		gridSize = safeChoice("Which size grid to you want to use", 'S', 'L');
		
		if( gridSize == 'L')
		{
			numRows = LARGEROWS;
			numCols = LARGECOLS;
		}
		else
		{
			numRows = SMALLROWS;
			numCols = SMALLCOLS;
		}
		initializePlayer(game);		
		initializePlayer(game + 1);
		// dynamically create the rows of the array
		allocMem(game,gridSize);
		
		for(whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
		{			
			gridComplete = false;
			while (gridComplete == false)
			{
				cout << "Player " << whichPlayer + 1 << ": \n";
				//Load from file?
				loadFromFile = safeChoice("Would you like to load your grid from a file?", 'Y', 'N');

				//give me the file name
				if (toupper(loadFromFile) == 'Y')
				{
					filename = getFileName("loading ");
					fileReturn = getGrid(game, whichPlayer, gridSize, filename);

					if (fileReturn == 0) //No error, get out of the loop
					{
						cout << "Load successful!" << endl;

						//Show them the grid and get confirmation
						printGrid(cout, game[whichPlayer].m_gameGrid[0], gridSize);
						goodGridInput = safeChoice("Are your ships placed correctly?", 'Y', 'N');
						gridComplete = (toupper((goodGridInput == 'N')) ? false : true);						
					}
					else
						errorDecoder(fileReturn); //print error. stay in loop
				}//End file load
				else
				{
					//Loop through manual ship input
					setShips(game, gridSize, whichPlayer);
				}
			}//End building the grid			
			if (whichPlayer == 0) //Wipe the grid so Player 2 can't see Player 1's ships.
			{
				system("cls");
				cout << endl;
				header(cout);
			}
		}
		whichPlayer = 0;
		while(!gameOver)
		{
			system("cls");
			//This loop only exits when the player misses OR runs out of targets
			while (!turnOver)
			{				
				turnOver = takeTheShot(game, whichPlayer, gridSize);
			}
			//Also require that there be valid targets left
			if (game[!whichPlayer].m_piecesLeft <= 0)
			{
				cout << "Victory is yours, Player " << whichPlayer + 1 << "!" << endl;
				gameOver = true;
			}
			else
			{
				//Next player
				whichPlayer = !whichPlayer;  // switch players
				system("cls");
				cout << "It is now Player " << whichPlayer + 1 << "'s turn." << endl;
				cout << "Press enter to take your turn.";
				cin.get();
			}
			
			turnOver = false;
		}
		//Congratulate player for victory

		//Prompt for play again
		again = safeChoice("Would you like to play again?", 'Y', 'N');

	}
	while(again == 'Y');

	return EXIT_SUCCESS;
} 
//---------------------------------------------------------------------------------
// Function:	errorDecoder()
// Title:		Error Decoder
// Description:
//				Translates getGrid()'s error codes into a human-readable format
// Programmer:	Hiromi Cota
// 
// Date:		1/21/2017
//
// Version:		1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	Error message to cout
//
// Calls:	nothing
//
// Called By:	main()
//
// Parameters:	code; int (values explained in comments below)
// 
// Returns:	void
//
// History Log: 
//		1/21/17	HRC completed v 1.0
//     
//---------------------------------------------------------------------------------
void errorDecoder(int code)
{
	string error = "Error! \n";
	switch (code)
	{
	case 0:
		break; //All OK.
	case 1:
		cout << error << "Could not open file.";
		break;
	case 2:
		cout << error << "File does not match game size.";
		break;
	case 3:
		cout << error << "File has bad orientation data for ships.";
		break;
	case 4:
		cout << error << "Ships are out of bounds for game size.";
		break;
	case 5:
		cout << error << "Illegal positions for ships in file.";
		break;
	default:
		break;
	}
	cout << endl;
}