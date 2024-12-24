#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "utils.h"

bool hasGameEnded(char** board, size_t boardSize);
void playerTurn(char** board, size_t boardSize, int& currentMove, Move moveHistory[], bool& quit);

#endif 
