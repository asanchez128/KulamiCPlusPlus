// Author: Amadeus Sanchez

#include <vector>
#include <map>
#include "Tile.h"
#pragma once

class Board
{
private:
	
	
public:
	std::vector<Tile> tiles;
	std::map<Position, bool> taken;
	Board();
	~Board();
	std::map<Position, int> indexOfTileInPosition;
	bool isPositionTaken(Position);
	void printBoard();
};

