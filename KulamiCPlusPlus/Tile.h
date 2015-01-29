#include <vector>
#include <map>
#include "Position.h"
#include "Marble.h"
#pragma once
class Tile
{
private:
	// width <= height

	
public:
	int width, height, size;
	Position lowerLeft, upperRight;
	std::map<Position, bool> taken;
	int indexTile;
	bool lastPlayed = false;
	bool secondToLastPlayed = false;
	std::map<Position, int> marbles;
	Tile();
	Tile(int, int, Position, Position, int);
	bool isEmpty(Position);
	~Tile();
};

