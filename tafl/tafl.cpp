
/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
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
		bool isDefenderTurn = currentMove & 1;
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

void mainMenu() {
	cout << "Welcome to Tafl\n\n\n";
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


int main() {
	mainMenu();
}