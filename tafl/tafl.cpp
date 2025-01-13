
/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Mihail Dimitrov
* @idnumber 3MI0600472
* @compiler VC
*
* <main program file>
*
*/
#include <iostream>
#include "boardLogic.h"
#include "gameLogic.h"
#include "utils.h"
using namespace std;

void startGame() {
	const int MAX_MOVES = 1024;
	Move moveHistory[MAX_MOVES];

	size_t boardSize = getBoardSize();
	char** board = getBoard(boardSize);

	bool quit = false;
	int currentMove = 1;

	while (!hasGameEnded(board, boardSize)) {
		bool isDefenderTurn = currentMove % 2 == 0;
		printBoard(board, boardSize);
		cout << "It's " << (isDefenderTurn ? "defender" : "attacker") << "'s turn.\n";
		playerTurn(board, boardSize, currentMove, moveHistory, quit);
		if (quit) {
			break;
		}
		currentMove++;
	}
	deleteBoard(board, boardSize);
}

void printWelcomeMessage() {
	cout << "W       W  EEEEE  L       CCCCC  OOOOO  M     M  EEEEE" << endl;
	cout << "W       W  E      L      C       O   O  MM   MM  E    " << endl;
	cout << "W   W   W  EEEE   L      C       O   O  M M M M  EEEE " << endl;
	cout << " W W W W   E      L      C       O   O  M  M  M  E    " << endl;
	cout << "  W   W    EEEEE  LLLLL   CCCCC  OOOOO  M     M  EEEEE" << endl;
	cout << endl;

	cout << "  		    TTTTT  OOOOO" << endl;
	cout << "		      T    O   O" << endl;
	cout << "		      T    O   O" << endl;
	cout << "		      T    O   O" << endl;
	cout << "		      T    OOOOO" << endl;
	cout << endl;

	cout << "		TTTTT  AAAAA  FFFFF  L    " << endl;
	cout << "		  T    A   A  F      L    " << endl;
	cout << "		  T    AAAAA  FFF    L    " << endl;
	cout << "		  T    A   A  F      L    " << endl;
	cout << "		  T    A   A  F      LLLLL" << endl;
}

void mainMenu() {
	while (true) {
		cout << "Main Menu\n\n";
		cout << "1) Start game\n";
		cout << "2) Quit\n\n";
		cout << "Choose one of the options (1 or 2) : ";

		int option;
		cin >> option;

		while (option < 1 || option > 2) {
			cout << "Invalid option. Type 1 or 2 : ";
			cin >> option;
		}

		if (option == 2)
		{
			return;
		}

		startGame();
	}

}


int main() {
	printWelcomeMessage();
	mainMenu();
}