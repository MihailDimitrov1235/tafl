#ifndef STRUCTURES
#define STRUCTURES

struct Location {
	int row, col;
};

struct Move {
	Location moveFrom;
	Location moveTo;
	Location captures[4];
};

#endif 
