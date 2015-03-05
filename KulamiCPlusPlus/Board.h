// Author: Amadeus Sanchez

#include <vector>
#include <map>
#include <cstdio>
#include "Tile.h"
#include <bitset>
#define SIZE 8
#pragma once

class Board
{
private:
	
	
public:
	std::vector<Tile> tiles;
	std::bitset<70> taken;
	Board();
	~Board();
	int tileInPosition[SIZE + 1][SIZE + 1];
	int sizeTileInPosition[SIZE + 1][SIZE + 1];
	bool isPositionTaken(Position);
	void printBoard();
	void Board::setTypeBoard(int);
	void Board::setBit(Position);
	void Board::clearBit(Position);
	int Board::getTileInPosition(Position p);
	int Board::getSizeTileInPosition(Position p);
};

