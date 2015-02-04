// Author: Amadeus Sanchez
#include "Board.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

Board::Board()
{
	tiles.push_back(Tile(1, 2, Position(2, 3), Position(3, 3), 0));
	tiles.push_back(Tile(1, 2, Position(6, 1), Position(6, 2), 1));
	tiles.push_back(Tile(1, 2, Position(3, 7), Position(3, 8), 2));
	tiles.push_back(Tile(1, 2, Position(7, 6), Position(8, 6), 3));

	tiles.push_back(Tile(1, 3, Position(1, 1), Position(1, 3), 4));
	tiles.push_back(Tile(1, 3, Position(6, 3), Position(8, 3), 5));
	tiles.push_back(Tile(1, 3, Position(1, 6), Position(3, 6), 6));
	tiles.push_back(Tile(1, 3, Position(6, 6), Position(6, 8), 7));

	tiles.push_back(Tile(2, 2, Position(2, 1), Position(3, 2), 8));
	tiles.push_back(Tile(2, 2, Position(7, 1), Position(8, 2), 9));
	tiles.push_back(Tile(2, 2, Position(1, 7), Position(2, 8), 10));
	tiles.push_back(Tile(2, 2, Position(7, 7), Position(8, 8), 11));
	tiles.push_back(Tile(2, 2, Position(4, 4), Position(5, 5), 12));

	tiles.push_back(Tile(2, 3, Position(4, 1), Position(5, 3), 13));
	tiles.push_back(Tile(2, 3, Position(1, 4), Position(3, 5), 14));
	tiles.push_back(Tile(2, 3, Position(6, 4), Position(8, 5), 15));
	tiles.push_back(Tile(2, 3, Position(4, 6), Position(5, 8), 16));

	for (int i = 1; i <= 8; ++i){
		for (int j = 1; j <= 8; ++j){
			//taken[Position(i, j)] = false;
			//taken[Position(i, j)].insert(false));
			taken.insert(std::make_pair(Position(i, j), false));
		}
	}
	for (auto tile: tiles){
		for (auto marble : tile.marbles){
			//indexOfTileInPosition[marble.first] = tile.indexTile;
			indexOfTileInPosition.insert((std::make_pair(marble.first, tile.indexTile)));
		}
	}
}

// ^ empty 
// player 1 &
// player 2 *
// Border;
void Board::printBoard(){
	char boardChar[28][28];
	for (int i = 1; i <= 27; ++i){
		for (int j = 1; j <= 27; ++j){
			boardChar[i][j] = '#';
		}
	}

	for (auto tile : tiles){
		for (int i = (tile.lowerLeft.vertical - 1) * 3 + 2; i <= (tile.upperRight.vertical - 1) * 3 + 2; ++i){
			for (int j = (tile.lowerLeft.horizontal - 1) * 3 + 2; j <= (tile.upperRight.horizontal - 1) * 3 + 2; ++j){
				boardChar[i][j] = '+';
			}
		}
	}
	for (auto tile : tiles){
		for (auto marble : tile.marbles){
			Position p = marble.first;
			int c = marble.second;
			
			if (c == 1){
				boardChar[(p.vertical - 1) * 3 + 2][(p.horizontal - 1) * 3 + 2] = '&';
			}
			else if (c == 2){
				boardChar[(p.vertical - 1) * 3 + 2][(p.horizontal - 1) * 3 + 2] = '@';
			}
		}
	}


	for (int i = 1; i <= 27; ++i){
		for (int j = 1; j <= 27; ++j){
			printf("%c", boardChar[i][j]);
		}
		printf("\n");
	}
}
Board::~Board()
{
}

bool Board::isPositionTaken(Position position){
	bool result = false;
	if (taken[position] == true){
		result = true;
	}
	return result;
}

