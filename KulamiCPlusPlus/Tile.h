// Author: Amadeus Sanchez

#include <vector>
#include <map>
#include "Position.h"
#include "Marble.h"
#pragma once
class Tile
{
private:
	
public:
	int width, height, size;
	Position lowerLeft, upperRight;
	std::map<Position, bool> taken; // I think I can get rid of this one
	int indexTile;
	bool lastPlayed = false;
	bool secondToLastPlayed = false;
	std::map<Position, int> marbles;
	Tile();
	Tile(int, int, Position, Position, int);
	bool isEmpty(Position);
	int marblesPlayer1, marblesPlayer2;
	~Tile();
};

