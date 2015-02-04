// Author: Amadeus Sanchez

#include "Tile.h"

// TODO
Tile::Tile()
{
}

// beware with size. It may cause issues
Tile::Tile(int _width, int _height, Position _lowerLeft, Position _upperRight, int _indexTile){
	width = _width, height = _height, size = width * height, lowerLeft = _lowerLeft, upperRight = _upperRight;
	for (int i = lowerLeft.horizontal; i <= upperRight.horizontal; ++i){
		for (int j = lowerLeft.vertical; j <= upperRight.vertical; ++j){
			marbles[Position(i, j)] = -1;
			taken[Position(i, j)] = false;
		}
	}
	indexTile = _indexTile;
}

bool Tile::isEmpty(Position position){
	return false;
}
Tile::~Tile()
{
}
