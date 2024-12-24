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

const char EMPTY = 46;
const char KING = 30;
const char ATTACKER = 'A';
const char DEFENDER = 'D';
const char CORNER = '*';
const char CASTLE = 28;

const char parlettBoard[13][13] = {
	{ CORNER, EMPTY, EMPTY, EMPTY,  ATTACKER, ATTACKER, ATTACKER, ATTACKER, ATTACKER, EMPTY, EMPTY, EMPTY,  CORNER },
	{ EMPTY, EMPTY, EMPTY, EMPTY,  EMPTY, ATTACKER, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY,  EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY,  EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,  EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY,  EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,  EMPTY },
	{ ATTACKER, EMPTY, EMPTY, EMPTY,  DEFENDER, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY,  ATTACKER },
	{ ATTACKER, ATTACKER, EMPTY, EMPTY,  EMPTY, DEFENDER, DEFENDER, DEFENDER, EMPTY, EMPTY, EMPTY, ATTACKER,  ATTACKER },
	{ ATTACKER, EMPTY, ATTACKER, DEFENDER,  EMPTY, DEFENDER, KING, DEFENDER, EMPTY, DEFENDER, ATTACKER, EMPTY,  ATTACKER },
	{ ATTACKER, ATTACKER, EMPTY, EMPTY,  EMPTY, DEFENDER, DEFENDER, DEFENDER, EMPTY, EMPTY, EMPTY, ATTACKER,  ATTACKER },
	{ ATTACKER, EMPTY, EMPTY, EMPTY,  DEFENDER, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY,  ATTACKER },
	{ EMPTY, EMPTY, EMPTY, EMPTY,  EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,  EMPTY },
	{ EMPTY, EMPTY, EMPTY,EMPTY,  EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,  EMPTY },
	{ EMPTY, EMPTY, EMPTY,EMPTY,  EMPTY, ATTACKER, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY,  EMPTY },
	{ CORNER, EMPTY, EMPTY,EMPTY,  ATTACKER, ATTACKER, ATTACKER, ATTACKER, ATTACKER, EMPTY, EMPTY, EMPTY,  CORNER },
};

const char hnefataflBoard[11][11] = {
	{ CORNER, EMPTY, EMPTY, ATTACKER, ATTACKER, ATTACKER, ATTACKER, ATTACKER, EMPTY, EMPTY, CORNER },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, DEFENDER, DEFENDER, DEFENDER, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ ATTACKER, ATTACKER, EMPTY, DEFENDER, DEFENDER, KING, DEFENDER, DEFENDER, EMPTY, ATTACKER, ATTACKER },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, DEFENDER, DEFENDER, DEFENDER, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
	{ CORNER, EMPTY, EMPTY, ATTACKER, ATTACKER, ATTACKER, ATTACKER, ATTACKER, EMPTY, EMPTY, CORNER }
};

const char tablutBoard[9][9] = {
	{ CORNER, EMPTY, EMPTY, ATTACKER, ATTACKER, ATTACKER, EMPTY, EMPTY, CORNER },
	{ EMPTY, EMPTY, EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, EMPTY },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ ATTACKER, ATTACKER, DEFENDER, DEFENDER, KING, DEFENDER, DEFENDER, ATTACKER, ATTACKER },
	{ ATTACKER, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, ATTACKER },
	{ EMPTY, EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY, EMPTY },
	{ CORNER, EMPTY, EMPTY, ATTACKER, ATTACKER, ATTACKER, EMPTY, EMPTY, CORNER }
};

const char brandubhBoard[7][7] = {
	{ CORNER, EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, CORNER },
	{ EMPTY, EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY },
	{ ATTACKER, ATTACKER, DEFENDER, KING, DEFENDER, ATTACKER, ATTACKER },
	{ EMPTY, EMPTY, EMPTY, DEFENDER, EMPTY, EMPTY, EMPTY },
	{ EMPTY, EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, EMPTY },
	{ CORNER, EMPTY, EMPTY, ATTACKER, EMPTY, EMPTY, CORNER }
};

size_t getBoardSize() {
	cout << endl << endl << "Choose game board size:\n\n";
	cout << "1) 11x11 (Standard)\n";
	cout << "2) 9x9\n";
	cout << "3) 7x7\n";
	cout << "4) 13x13\n\n";
	cout << "Choose one of the options (1 - 4) : ";

	size_t option;
	cin >> option;

	while (option < 1 || option > 4) {
		cout << "Invalid option. Type a number between 1 and 4 : ";
		cin >> option;
	}

	size_t boardSize = 11;
	switch (option) {
	case 1: boardSize = 11; break;
	case 2: boardSize = 9; break;
	case 3: boardSize = 7; break;
	case 4: boardSize = 13; break;
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

char** getBoardOfSize13() {
	const size_t boardSize = 13;
	char** board = new char* [boardSize];
	for (size_t i = 0; i < boardSize; i++)
	{
		char* row = new char[boardSize];
		for (size_t j = 0; j < boardSize; j++)
		{
			row[j] = parlettBoard[i][j];
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
	case 13:
		return getBoardOfSize13();
	default:
		cout << "Invalid boardSize!!!\n";
		return nullptr;
		break;
	}
}

void printBoard(char** board, size_t boardSize) {

	if (board == nullptr)
	{
		return;
	}

	for (size_t i = 0; i < boardSize; i++)
	{
		for (size_t j = 0; j < boardSize; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << " |";
		if (i + 1 >= 10)
		{
			cout << i + 1;
		}
		else {
			cout << " " << i + 1;
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
	cout << endl;
}

void deleteBoard(char** board, size_t boardSize) {
	if (board == nullptr)
	{
		return;
	}
	for (size_t i = 0; i < boardSize; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}