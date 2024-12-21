
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
using namespace std;

void startGame() {
	cout << endl << endl << "Choose game board size:\n\n";
	cout << "1) 13x13\n";
	cout << "2) 11x11 (Standard)\n";
	cout << "3) 9x9\n";
	cout << "4) 7x7\n\n";
	cout << "Choose one of the options (1 - 4) : ";

	size_t option;
	cin >> option;

	while (option < 1 || option > 4) {
		cout << "Invalid option. Type a number between 1 and 4 : ";
		cin >> option;
	}

	size_t boardSize = 11;
	switch (option) {
	case 1: boardSize = 13; break;
	case 2: boardSize = 11; break;
	case 3: boardSize = 9; break;
	case 4: boardSize = 7; break;
	}
	cout << boardSize;
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