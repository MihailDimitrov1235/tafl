#ifndef UTILS
#define UTILS

struct Location {
	int row, col;
};

struct Move {
	Location moveFrom;
	Location moveTo;
	Location captures[4];
};

bool compareStrings(const char* str1, const char* str2);
void printHelp();
void printInfo(int capturedDefenders, int capturedAttackers, int currentMove);

#endif 
