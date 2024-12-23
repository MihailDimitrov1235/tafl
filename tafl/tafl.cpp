
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
#include "BoardLogic.h"
using namespace std;

void startGame() {

	size_t boardSize = getBoardSize();
	char** board = getBoard(boardSize);
	printBoard(board, boardSize);

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