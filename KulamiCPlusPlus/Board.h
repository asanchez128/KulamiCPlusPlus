// Author: Amadeus Sanchez

#include <vector>
#include <map>
#include <cstdio>
#include "Tile.h"
#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

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
	void Board::setTypeBoard(int);
};

