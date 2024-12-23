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
* <file with main game functions>
*
*/

#include <iostream>
#include "boardLogic.h"
#include "utils.h"
using namespace std;

bool isKingOnTheEdge(size_t boardSize, size_t kingRow, size_t kingCol) {
	if (kingRow == kingCol && (kingRow == 0 || kingRow == boardSize - 1))
	{
		return true;
	}
	if (kingRow == boardSize - kingCol - 1 && (kingRow == 0 || kingRow == boardSize - 1))
	{
		return true;
	}
	return false;
}

bool isHostile(char symbol, bool forDefenders) {
	if (forDefenders)
	{
		return symbol == EDGE || symbol == CASTLE || symbol == ATTACKER;
	}
	return symbol == EDGE || symbol == CASTLE || symbol == DEFENDER;
}

bool isKingSurrounded(char** board, size_t boardSize, size_t kingRow, size_t kingCol) {
	if (kingRow == 0)
	{
		return isHostile(board[kingRow][kingCol - 1], true)
			&& isHostile(board[kingRow][kingCol + 1], true)
			&& isHostile(board[kingRow + 1][kingCol], true);
	}
	else if (kingRow == boardSize - 1) {
		return isHostile(board[kingRow][kingCol - 1], true)
			&& isHostile(board[kingRow][kingCol + 1], true)
			&& isHostile(board[kingRow - 1][kingCol], true);
	}
	else if (kingCol == 0) {
		return isHostile(board[kingRow - 1][kingCol], true)
			&& isHostile(board[kingRow + 1][kingCol], true)
			&& isHostile(board[kingRow][kingCol + 1], true);
	}
	else if (kingCol == boardSize - 1) {
		return isHostile(board[kingRow - 1][kingCol], true)
			&& isHostile(board[kingRow + 1][kingCol], true)
			&& isHostile(board[kingRow][kingCol + 1], true);
	}
	return isHostile(board[kingRow - 1][kingCol], true)
		&& isHostile(board[kingRow + 1][kingCol], true)
		&& isHostile(board[kingRow][kingCol + 1], true)
		&& isHostile(board[kingRow][kingCol - 1], true);
}

bool hasGameEnded(char** board, size_t boardSize) {
	for (size_t i = 0; i < boardSize; i++)
	{
		for (size_t j = 0; j < boardSize; j++) {
			if (board[i][j] == KING)
			{
				if (isKingOnTheEdge(boardSize, i, j) || isKingSurrounded(board, boardSize, i, j))
				{
					return true;
				}
				return false;
			}
		}
	}
	return false;
}

int getColFromLetter(char letter) {
	if (letter >= 'A' && letter <= 'Z')
	{
		return letter - 'A';
	}
	return letter - 'a';
}

bool isValidBoardLocation(char* boardLocation, size_t boardSize) {
	if (!(boardLocation[0] >= 'a' && boardLocation[0] <= ('a' + boardSize - 1))
		&& !(boardLocation[0] >= 'A' && boardLocation[0] <= ('A' + boardSize - 1))) {
		return false;
	}
	if (boardLocation[1] < 1 || boardLocation[1] > boardSize) {
		return false;
	}
	if (boardLocation[2] != '\0') {
		return false;
	}
	return true;
}

bool isValidMove(char* moveFrom, char* moveTo, bool defender, size_t boardSize) {
	if (!isValidBoardLocation(moveFrom, boardSize) || !isValidBoardLocation(moveTo, boardSize))
	{
		return false;
	}
	int moveFromX = getColFromLetter(moveFrom[0]);
	int moveFromY = moveFrom[1] - '0';
	int moveToX = getColFromLetter(moveTo[0]);
	int moveToY = moveTo[1] - '0';

}

void playerTurn(char** board, size_t boardSize, bool defender) {
	const int MAX_WORD_SIZE = 255;
	char option[MAX_WORD_SIZE];
	char moveFrom[MAX_WORD_SIZE];
	char moveTo[MAX_WORD_SIZE];

	while (true) {
		cin >> option;
		if (compareStrings(option, "move") || compareStrings(option, "Move")) {
			cin >> moveFrom >> moveTo;
			if (isValidMove(moveFrom, moveTo, defender, boardSize)) {

			}
		}
		else if (compareStrings(option, "info") || compareStrings(option, "Info")) {

		}
		else if (compareStrings(option, "quit") || compareStrings(option, "Quit")) {

		}
		else if (compareStrings(option, "help") || compareStrings(option, "Help")) {

		}
		else {
			cout << "Invalid command. Try again. Write \"help\" for assistance\n";
		}
	}
}