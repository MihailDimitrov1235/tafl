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

const int MAX_WORD_SIZE = 255;
const int NUMBER_OF_POSSIBLE_CAPTURES = 4;

bool isKingInACorner(size_t boardSize, size_t kingRow, size_t kingCol) {
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
		return symbol == CORNER || symbol == CASTLE || symbol == ATTACKER;
	}
	return symbol == CORNER || symbol == CASTLE || symbol == DEFENDER;
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
	if (board == nullptr)
	{
		return true;
	}
	for (size_t i = 0; i < boardSize; i++)
	{
		for (size_t j = 0; j < boardSize; j++) {
			if (board[i][j] == KING)
			{
				if (isKingInACorner(boardSize, i, j))
				{
					cout << "Defender wins!";
					return true;
				}
				if (isKingSurrounded(board, boardSize, i, j))
				{
					cout << "Attacker wins!";
					return true;
				}
				return false;
			}
		}
	}
	return false;
}

int getRowFromBoardLocation(char* boardLocation) {
	int num = 0;
	boardLocation++;
	if (*boardLocation == '0')
	{
		return 0;
	}
	while (*boardLocation != '\0') {
		num = num * 10 + (*boardLocation - '0');
		boardLocation++;
	}
	return num;
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
	int index = 1;
	while (boardLocation[index] != '\0') {
		if (boardLocation[index] < '0' || boardLocation[index] > '9') {
			return false;
		}
		index++;
	}
	int row = getRowFromBoardLocation(boardLocation);

	if (row < 1 || row > boardSize)
	{
		return false;
	}

	return true;
}

bool isTheirPiece(bool isDefender, char piece) {
	if (isDefender)
	{
		return piece == KING || piece == DEFENDER;
	}
	return piece == ATTACKER;
}

bool canMoveTo(bool isKing, char place) {
	if (place == EMPTY)
	{
		return true;
	}
	return (place == CASTLE || place == CORNER) && isKing;
}

bool isVerticalOrHorizontal(int fromX, int fromY, int toX, int toY) {
	if ((fromX != toX && fromY != toY)
		|| (fromX == toX && fromY == toY))
	{
		return false;
	}
	return true;
}

bool canMoveOver(char place) {
	return place == EMPTY || place == CASTLE;
}

bool isPathClearToMove(char** board, int fromX, int fromY, int toX, int toY, bool isDefender) {
	if (fromX == toX) {
		if (fromY > toY) {
			for (int i = toY + 1; i < fromY; i++) {
				if (!canMoveOver(board[i][fromX])) {
					return false;
				}
			}
		}
		else {
			for (int i = fromY + 1; i < toY; i++) {
				if (!canMoveOver(board[i][fromX])) {
					return false;
				}
			}
		}
	}
	else {
		if (fromX > toX) {
			for (int i = toX + 1; i < fromX; i++) {
				if (!canMoveOver(board[fromY][i])) {
					return false;
				}
			}
		}
		else {
			for (int i = fromX + 1; i < toX; i++) {
				if (!canMoveOver(board[fromY][i])) {
					return false;
				}
			}
		}
	}
	return true;
}

bool isValidMove(char** board, size_t boardSize, char* moveFrom, char* moveTo, bool isDefender) {
	if (!isValidBoardLocation(moveFrom, boardSize) || !isValidBoardLocation(moveTo, boardSize))
	{
		cout << "Invalid coordinates\n";
		return false;
	}
	int moveFromY = getRowFromBoardLocation(moveFrom) - 1;
	int moveFromX = getColFromLetter(moveFrom[0]);
	int moveToY = getRowFromBoardLocation(moveTo) - 1;
	int moveToX = getColFromLetter(moveTo[0]);
	bool isKing = board[moveFromY][moveFromX] == KING;
	if (!isTheirPiece(isDefender, board[moveFromY][moveFromX])) {
		cout << "Not your piece. Try again.\n";
		return false;
	}
	if (!canMoveTo(isKing, board[moveToY][moveToX]))
	{
		cout << "You can't move there. Try again.\n";
		return false;
	}
	if (!isVerticalOrHorizontal(moveFromX, moveFromY, moveToX, moveToY))
	{
		cout << "The piece can only move vertically or horizontally. Try again.\n";
		return false;
	}
	if (!isPathClearToMove(board, moveFromX, moveFromY, moveToX, moveToY, isDefender))
	{
		cout << "The path isn't clear. Try again.\n";
		return false;
	}
	return true;
}

void makeCaptures(char** board, size_t boardSize, int pieceX, int pieceY, bool isDefender, Move moveHistory[], int currentMove) {
	char enemy = isDefender ? ATTACKER : DEFENDER;
	size_t capturedPieces = 0;
	if (pieceY - 2 >= 0
		&& board[pieceY - 1][pieceX] == enemy
		&& isHostile(board[pieceY - 2][pieceX], !isDefender)) {
		board[pieceY - 1][pieceX] = EMPTY;
		moveHistory[currentMove - 1].captures[capturedPieces] = { pieceY - 1 , pieceX };
		capturedPieces++;
	}
	if (pieceY + 2 < boardSize
		&& board[pieceY + 1][pieceX] == enemy
		&& isHostile(board[pieceY + 2][pieceX], !isDefender)) {
		board[pieceY + 1][pieceX] = EMPTY;
		moveHistory[currentMove - 1].captures[capturedPieces] = { pieceY + 1 , pieceX };
		capturedPieces++;
	}
	if (pieceX - 2 >= 0
		&& board[pieceY][pieceX - 1] == enemy
		&& isHostile(board[pieceY][pieceX - 2], !isDefender)) {
		board[pieceY][pieceX - 1] = EMPTY;
		moveHistory[currentMove - 1].captures[capturedPieces] = { pieceY , pieceX - 1 };
		capturedPieces++;
	}
	if (pieceX + 2 < boardSize
		&& board[pieceY][pieceX + 1] == enemy
		&& isHostile(board[pieceY][pieceX + 2], !isDefender)) {
		board[pieceY][pieceX + 1] = EMPTY;
		moveHistory[currentMove - 1].captures[capturedPieces] = { pieceY , pieceX + 1 };
		capturedPieces++;
	}
	if (capturedPieces > 0)
	{
		cout << (isDefender ? "Defender" : "Attacker") << " captured " << capturedPieces
			<< " piece" << (capturedPieces > 1 ? "s" : "") << ".\n";
	}
}

void makeMove(char** board,
	size_t boardSize,
	char* moveFrom,
	char* moveTo,
	bool isDefender,
	Move moveHistory[],
	int currentMove) {

	int moveFromY = getRowFromBoardLocation(moveFrom) - 1;
	int moveFromX = getColFromLetter(moveFrom[0]);
	int moveToY = getRowFromBoardLocation(moveTo) - 1;
	int moveToX = getColFromLetter(moveTo[0]);

	board[moveToY][moveToX] = board[moveFromY][moveFromX];
	if (moveFromX == (boardSize - 1) / 2 && moveFromY == (boardSize - 1) / 2) {
		board[moveFromY][moveFromX] = CASTLE;
	}
	else {
		board[moveFromY][moveFromX] = EMPTY;
	}
	makeCaptures(board, boardSize, moveToX, moveToY, isDefender, moveHistory, currentMove);
}

void goBackOneMove(char** board, size_t boardSize, int& currentMove, Move moveHistory[]) {
	if (currentMove <= 1)
	{
		cout << "Can't go back any further\n";
		return;
	}
	Move move = moveHistory[currentMove - 2];
	int moveFromY = move.moveTo.row;
	int moveFromX = move.moveTo.col;
	cout << moveFromY << " " << moveFromX << endl;
	int moveToY = move.moveFrom.row;
	int moveToX = move.moveFrom.col;
	cout << moveToY << " " << moveToX << endl;
	board[moveToY][moveToX] = board[moveFromY][moveFromX];
	if (moveFromX == (boardSize - 1) / 2 && moveFromY == (boardSize - 1) / 2) {
		board[moveFromY][moveFromX] = CASTLE;
	}
	else {
		board[moveFromY][moveFromX] = EMPTY;
	}

	for (size_t i = 0; i < NUMBER_OF_POSSIBLE_CAPTURES; i++)
	{
		int row = move.captures[i].row;
		int col = move.captures[i].col;

		if (row == -1 || col == -1)
		{
			break;
		}

		char symbol = currentMove & 1 ? ATTACKER : DEFENDER;
		board[row][col] = symbol;
	}
	currentMove -= 2;
}

int countCaptures(int currentMove, Move moveHistory[], bool countDefenders) {
	size_t counter = 0;
	for (size_t i = 0; i < currentMove - 1; i++)
	{
		if (countDefenders && (i % 2 == 1))
		{
			continue;
		}
		if (!countDefenders && (i % 2 == 0))
		{
			continue;
		}
		Move move = moveHistory[i];
		for (size_t j = 0; j < NUMBER_OF_POSSIBLE_CAPTURES; j++)
		{
			int row = move.captures[j].row;
			int col = move.captures[j].col;

			if (row == -1 || col == -1)
			{
				break;
			}
			counter++;
		}
	}
	return counter;
}

void saveMove(char* moveFrom, char* moveTo, Move moveHistory[], int currentMove) {
	int moveFromY = getRowFromBoardLocation(moveFrom) - 1;
	int moveFromX = getColFromLetter(moveFrom[0]);
	int moveToY = getRowFromBoardLocation(moveTo) - 1;
	int moveToX = getColFromLetter(moveTo[0]);
	moveHistory[currentMove - 1] = { {moveFromY, moveFromX}, {moveToY, moveToX}, {{-1,-1},{-1,-1},{-1,-1}} };
}

void playerTurn(char** board, size_t boardSize, int& currentMove, Move moveHistory[], bool& quit) {
	if (board == nullptr)
	{
		quit = true;
		return;
	}
	char option[MAX_WORD_SIZE];
	char moveFrom[MAX_WORD_SIZE];
	char moveTo[MAX_WORD_SIZE];
	bool isDefender = currentMove % 2 == 0;

	while (true) {
		cin >> option;
		if (compareStrings(option, "move") || compareStrings(option, "Move")) {
			cin >> moveFrom >> moveTo;
			if (isValidMove(board, boardSize, moveFrom, moveTo, isDefender)) {
				saveMove(moveFrom, moveTo, moveHistory, currentMove);
				makeMove(board, boardSize, moveFrom, moveTo, isDefender, moveHistory, currentMove);
				break;
			}
		}
		else if (compareStrings(option, "info") || compareStrings(option, "Info")) {
			int capturedDefenders = countCaptures(currentMove, moveHistory, true);
			int capturedAttackers = countCaptures(currentMove, moveHistory, false);
			printInfo(capturedDefenders, capturedAttackers, currentMove);
		}
		else if (compareStrings(option, "back") || compareStrings(option, "Back")) {
			goBackOneMove(board, boardSize, currentMove, moveHistory);
			break;
		}
		else if (compareStrings(option, "quit") || compareStrings(option, "Quit")) {
			quit = true;
			break;
		}
		else if (compareStrings(option, "help") || compareStrings(option, "Help")) {
			printHelp();
		}
		else {
			cout << "Invalid command. Try again. Write \"help\" to see available commands\n";
		}
	}
}