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
* <board logic file>
*
*/

#include <iostream>
#include "BoardLogic.h"
using namespace std;

const char EMPTY = '-';
const char KING = 'K';
const char ATTACKER = 'A';
const char DEFENDER = 'D';
const char EDGE = 'X';
const char CASTLE = 'C';

const char hnefataflBoard[11][11] = {
	{ EDGE, EMPTY, EMPTY, ATTACKER, ATTACKER, ATTACKER, ATTACKER, ATTACKER, EMPTY, EMPTY, EDGE },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, DEFENDER, DEFENDER, DEFENDER, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ ATTACKER, ATTACKER, EMPTY, DEFENDER, DEFENDER, KING, DEFENDER, DEFENDER, EMPTY, ATTACKER, ATTACKER },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, DEFENDER, DEFENDER, DEFENDER, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EDGE, EMPTY, EMPTY, ATTACKER, ATTACKER, ATTACKER, ATTACKER, ATTACKER, EMPTY, EMPTY, EDGE }
};

const char tablutBoard[9][9] = {
	{ EDGE, EMPTY, EMPTY, ATTACKER, ATTACKER, ATTACKER, EMPTY, EMPTY, EDGE },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, EMPTY },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ ATTACKER, EMPTY, DEFENDER, DEFENDER, KING, DEFENDER, DEFENDER, EMPTY, ATTACKER },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ EMPTY, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EDGE, EMPTY, EMPTY, ATTACKER, ATTACKER, ATTACKER, EMPTY, EMPTY, EDGE }
};

const char brandubhBoard[7][7] = {
	{ EDGE, EMPTY, ATTACKER, ATTACKER, ATTACKER, EMPTY, EDGE },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ ATTACKER, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, ATTACKER },
	{ ATTACKER, EMPTY, DEFENDER, KING, DEFENDER, EMPTY, ATTACKER },
	{ ATTACKER, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, ATTACKER },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EDGE, EMPTY, ATTACKER, ATTACKER, ATTACKER, EMPTY, EDGE }
};

size_t getBoardSize() {
	cout << endl << endl << "Choose game board size:\n\n";
	cout << "1) 11x11 (Standard)\n";
	cout << "2) 9x9\n";
	cout << "3) 7x7\n\n";
	cout << "Choose one of the options (1 - 3) : ";

	size_t option;
	cin >> option;

	while (option < 1 || option > 3) {
		cout << "Invalid option. Type a number between 1 and 3 : ";
		cin >> option;
	}

	size_t boardSize = 11;
	switch (option) {
	case 1: boardSize = 11; break;
	case 2: boardSize = 9; break;
	case 3: boardSize = 7; break;
	}

	return boardSize;
}

char** getBoardOfSize11() {
	const size_t boardSize = 11;
	char** board = new char* [boardSize];
	for (size_t i = 0; i < boardSize; i++)
	{
		char* row = new char[boardSize];
		for (size_t j = 0; j < boardSize; j++)
		{
			row[j] = hnefataflBoard[i][j];
		}
		board[i] = row;
	}
	return board;
}

char** getBoardOfSize9() {
	const size_t boardSize = 9;
	char** board = new char* [boardSize];
	for (size_t i = 0; i < boardSize; i++)
	{
		char* row = new char[boardSize];
		for (size_t j = 0; j < boardSize; j++)
		{
			row[j] = tablutBoard[i][j];
		}
		board[i] = row;
	}
	return board;
}

char** getBoardOfSize7() {
	const size_t boardSize = 7;
	char** board = new char* [boardSize];
	for (size_t i = 0; i < boardSize; i++)
	{
		char* row = new char[boardSize];
		for (size_t j = 0; j < boardSize; j++)
		{
			row[j] = brandubhBoard[i][j];
		}
		board[i] = row;
	}
	return board;
}

char** getBoard(size_t boardSize) {
	switch (boardSize) {
	case 11:
		return getBoardOfSize11();
	case 9:
		return getBoardOfSize9();
	case 7:
		return getBoardOfSize7();
	default:
		cout << "Invalid boardSize!!!\n";
		return nullptr;
		break;
	}
}

void printBoard(char** board, size_t boardSize) {
	for (size_t i = 0; i < boardSize; i++)
	{
		for (size_t j = 0; j < boardSize; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << " |";
		if (boardSize - i >= 10)
		{
			cout << boardSize - i;
		}
		else {
			cout << " " << boardSize - i;
		}
		cout << endl;
	}
	for (size_t i = 0; i < boardSize + 1; i++)
	{
		cout << "--";
	}
	cout << endl;

	for (size_t i = 0; i < boardSize; i++)
	{
		char letter = 'a' + i;
		cout << letter << " ";
	}
}

void deleteBoard(char** board, size_t boardSize) {
	for (size_t i = 0; i < boardSize; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}