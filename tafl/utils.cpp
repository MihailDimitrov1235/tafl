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
* <file with utility functions>
*
*/

#include <iostream>
using namespace std;

bool compareStrings(const char* str1, const char* str2) {
	if (str1 == nullptr || str2 == nullptr)
	{
		return false;
	}

	while (*str1 != '\0') {
		if (*str1 != *str2)
		{
			return false;
		}
		str1++;
		str2++;
	}
	return *str2 == '\0';
}

void printHelp() {
	cout << "\nPossible commands\n\n";
	cout << "move <from> <to>\n"
		<< "Moves a piece to a square\n"
		<< "e.g. move a1 a4\n\n";
	cout << "back\n"
		<< "Goes back one move\n\n";
	cout << "info\n"
		<< "Gives info about the game\n\n";
	cout << "quit\n"
		<< "Quits the game\n\n";
}

void printInfo(int capturedDefenders, int capturedAttackers, int currentMove) {
	cout << "Current move: " << currentMove << endl;
	cout << (currentMove % 2 == 0 ? "Defender" : "Attacker") << "'s move" << endl;
	cout << "Captured defenders: " << capturedDefenders << endl;
	cout << "Captured attackers: " << capturedAttackers << endl;
}