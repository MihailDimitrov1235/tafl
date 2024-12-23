#ifndef BOARD_LOGIC_H
#define BOARD_LOGIC_H

extern const char EMPTY;
extern const char KING;
extern const char ATTACKER;
extern const char DEFENDER;
extern const char EDGE;
extern const char CASTLE;

size_t getBoardSize();
char** getBoard(size_t boardSize);
void printBoard(char** board, size_t boardSize);
void deleteBoard(char** board, size_t boardSize);

#endif 
