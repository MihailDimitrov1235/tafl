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