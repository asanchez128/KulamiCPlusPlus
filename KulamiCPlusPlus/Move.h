#include "Position.h"
#pragma once
class Move
{
public:
	Position position;
	int tileNumber;
	int color;
	Move();
	Move(Position, int, int);
	~Move();
};

