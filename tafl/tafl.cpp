
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
	cout << "Welcome to Tafl\n\n";
	cout << "1) Start game\n";
	cout << "2) Quit\n";
	cout << "Choose one of the options (1 or 2) :";

	char option;
	cin >> option;

	while (option != '1' && option != '2') {
		cout << "Invalid option. Type 1 or 2 :";
		cin >> option;
	}

	if (option == '2')
	{
		return;
	}
}


int main() {
	startGame();
}