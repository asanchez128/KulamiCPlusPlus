// Author: Amadeus Sanchez
#include "Board.h"

Board::Board(){
	taken = 0;
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
		for (int i = (tile.lowerLeft.vertical) * 3 + 2; i <= (tile.upperRight.vertical) * 3 + 2; ++i){
			for (int j = (tile.lowerLeft.horizontal) * 3 + 2; j <= (tile.upperRight.horizontal) * 3 + 2; ++j){
				boardChar[i][j] = '+';
			}
		}
	}
	for (auto tile : tiles){
		for (auto marble : tile.marbles){
			Position p = marble.first;
			int c = marble.second;
			
			if (c == 1){
				boardChar[(p.vertical) * 3 + 2][(p.horizontal) * 3 + 2] = '&';
			}
			else if (c == 2){
				boardChar[(p.vertical) * 3 + 2][(p.horizontal) * 3 + 2] = '@';
			}
		}
	}

	//freopen("output.txt", "a", stdout);

	for (int i = 1; i <= 27; ++i){
		for (int j = 1; j <= 27; ++j){
			printf("%c", boardChar[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
}
Board::~Board()
{
}

bool Board::isPositionTaken(Position p){
	return taken.test((8 * p.horizontal + p.vertical));
}

void Board::setTypeBoard(int type){
	if (type == 1){
		tiles.push_back(Tile(1, 2, Position(2, 1), Position(2, 2), 0));
		tiles.push_back(Tile(1, 2, Position(3, 1), Position(3, 2), 1));
		tiles.push_back(Tile(1, 2, Position(4, 1), Position(4, 2), 2));
		tiles.push_back(Tile(1, 2, Position(5, 1), Position(5, 2), 3));

		tiles.push_back(Tile(1, 3, Position(0, 0), Position(2, 0), 4));
		tiles.push_back(Tile(1, 3, Position(3, 0), Position(5, 0), 5));
		tiles.push_back(Tile(1, 3, Position(6, 0), Position(6, 2), 6));
		tiles.push_back(Tile(1, 3, Position(7, 0), Position(7, 2), 7));

		tiles.push_back(Tile(2, 2, Position(0, 1), Position(1, 2), 8));
		tiles.push_back(Tile(2, 2, Position(0, 3), Position(1, 4), 9));
		tiles.push_back(Tile(2, 2, Position(2, 3), Position(3, 4), 10));
		tiles.push_back(Tile(2, 2, Position(4, 3), Position(5, 4), 11));
		tiles.push_back(Tile(2, 2, Position(6, 3), Position(7, 4), 12));

		tiles.push_back(Tile(2, 3, Position(0, 5), Position(1, 7), 13));
		tiles.push_back(Tile(2, 3, Position(2, 5), Position(3, 7), 14));
		tiles.push_back(Tile(2, 3, Position(4, 5), Position(5, 7), 15));
		tiles.push_back(Tile(2, 3, Position(6, 5), Position(7, 7), 16));
	}
	else if (type == 2){
		tiles.push_back(Tile(1, 2, Position(3, 0), Position(4, 0), 0));
		tiles.push_back(Tile(1, 2, Position(3, 2), Position(3, 3), 1));
		tiles.push_back(Tile(1, 2, Position(4, 2), Position(4, 3), 2));
		tiles.push_back(Tile(1, 2, Position(5, 2), Position(5, 3), 3));

		tiles.push_back(Tile(1, 3, Position(0, 0), Position(2, 0), 4));
		tiles.push_back(Tile(1, 3, Position(5, 0), Position(7, 0), 5));
		tiles.push_back(Tile(1, 3, Position(2, 1), Position(2, 3), 6));
		tiles.push_back(Tile(1, 3, Position(3, 1), Position(5, 1), 7));

		tiles.push_back(Tile(2, 2, Position(0, 4), Position(1, 5), 8));
		tiles.push_back(Tile(2, 2, Position(2, 4), Position(3, 5), 9));
		tiles.push_back(Tile(2, 2, Position(4, 4), Position(5, 5), 10));
		tiles.push_back(Tile(2, 2, Position(6, 4), Position(7, 5), 11));
		tiles.push_back(Tile(2, 2, Position(0, 6), Position(1, 7), 12));

		tiles.push_back(Tile(2, 3, Position(0, 1), Position(1, 3), 13));
		tiles.push_back(Tile(2, 3, Position(6, 1), Position(7, 3), 14));
		tiles.push_back(Tile(2, 3, Position(2, 6), Position(4, 7), 15));
		tiles.push_back(Tile(2, 3, Position(5, 6), Position(7, 7), 16));
	}
	else if (type == 3){
		tiles.push_back(Tile(1, 2, Position(6, 0), Position(7, 0), 0));
		tiles.push_back(Tile(1, 2, Position(2, 3), Position(2, 4), 1));
		tiles.push_back(Tile(1, 2, Position(7, 3), Position(7, 4), 2));
		tiles.push_back(Tile(1, 2, Position(3, 5), Position(3, 6), 3));

		tiles.push_back(Tile(1, 3, Position(2, 0), Position(2, 2), 4));
		tiles.push_back(Tile(1, 3, Position(5, 0), Position(5, 2), 5));
		tiles.push_back(Tile(1, 3, Position(0, 5), Position(2, 5), 6));
		tiles.push_back(Tile(1, 3, Position(3, 7), Position(5, 7), 7));

		tiles.push_back(Tile(2, 2, Position(3, 0), Position(4, 1), 8));
		tiles.push_back(Tile(2, 2, Position(6, 1), Position(7, 2), 9));
		tiles.push_back(Tile(2, 2, Position(0, 3), Position(1, 4), 10));
		tiles.push_back(Tile(2, 2, Position(5, 3), Position(6, 4), 11));
		tiles.push_back(Tile(2, 2, Position(4, 5), Position(5, 6), 12));

		tiles.push_back(Tile(2, 3, Position(0, 0), Position(1, 2), 13));
		tiles.push_back(Tile(2, 3, Position(3, 2), Position(4, 4), 14));
		tiles.push_back(Tile(2, 3, Position(0, 6), Position(2, 7), 15));
		tiles.push_back(Tile(2, 3, Position(6, 5), Position(7, 7), 16));
	}
	else if (type == 4){
		tiles.push_back(Tile(1, 2, Position(0, 2), Position(0, 3), 0));
		tiles.push_back(Tile(1, 2, Position(3, 3), Position(3, 4), 1));
		tiles.push_back(Tile(1, 2, Position(7, 3), Position(7, 4), 2));
		tiles.push_back(Tile(1, 2, Position(2, 6), Position(2, 7), 3));

		tiles.push_back(Tile(1, 3, Position(3, 0), Position(3, 2), 4));
		tiles.push_back(Tile(1, 3, Position(6, 3), Position(6, 5), 5));
		tiles.push_back(Tile(1, 3, Position(3, 5), Position(3, 7), 6));
		tiles.push_back(Tile(1, 3, Position(7, 5), Position(7, 7), 7));

		tiles.push_back(Tile(2, 2, Position(4, 0), Position(5, 1), 8));
		tiles.push_back(Tile(2, 2, Position(1, 2), Position(2, 3), 9));
		tiles.push_back(Tile(2, 2, Position(4, 2), Position(5, 3), 10));
		tiles.push_back(Tile(2, 2, Position(4, 4), Position(5, 5), 11));
		tiles.push_back(Tile(2, 2, Position(0, 6), Position(1, 7), 12));

		tiles.push_back(Tile(2, 3, Position(0, 0), Position(2, 1), 13));
		tiles.push_back(Tile(2, 3, Position(6, 0), Position(7, 2), 14));
		tiles.push_back(Tile(2, 3, Position(0, 4), Position(2, 5), 15));
		tiles.push_back(Tile(2, 3, Position(4, 6), Position(6, 7), 16));
	}
	else if (type == 5){
		tiles.push_back(Tile(1, 2, Position(2, 1), Position(3, 1), 0));
		tiles.push_back(Tile(1, 2, Position(0, 3), Position(1, 3), 1));
		tiles.push_back(Tile(1, 2, Position(2, 6), Position(2, 7), 2));
		tiles.push_back(Tile(1, 2, Position(4, 6), Position(5, 6), 3));

		tiles.push_back(Tile(1, 3, Position(0, 0), Position(2, 0), 4));
		tiles.push_back(Tile(1, 3, Position(3, 0), Position(5, 0), 5));
		tiles.push_back(Tile(1, 3, Position(3, 4), Position(3, 6), 6));
		tiles.push_back(Tile(1, 3, Position(3, 7), Position(5, 7), 7));

		tiles.push_back(Tile(2, 2, Position(6, 0), Position(7, 1), 8));
		tiles.push_back(Tile(2, 2, Position(0, 1), Position(1, 2), 9));
		tiles.push_back(Tile(2, 2, Position(4, 1), Position(5, 2), 10));
		tiles.push_back(Tile(2, 2, Position(2, 2), Position(3, 3), 11));
		tiles.push_back(Tile(2, 2, Position(0, 6), Position(1, 7), 12));

		tiles.push_back(Tile(2, 3, Position(0, 4), Position(2, 5), 13));
		tiles.push_back(Tile(2, 3, Position(4, 3), Position(5, 5), 14));
		tiles.push_back(Tile(2, 3, Position(6, 2), Position(7, 4), 15));
		tiles.push_back(Tile(2, 3, Position(6, 5), Position(7, 7), 16));
	}
	else if (type == 6){
		tiles.push_back(Tile(1, 2, Position(0, 1), Position(0, 2), 0));
		tiles.push_back(Tile(1, 2, Position(5, 0), Position(6, 0), 1));
		tiles.push_back(Tile(1, 2, Position(1, 7), Position(2, 7), 2));
		tiles.push_back(Tile(1, 2, Position(7, 5), Position(7, 6), 3));

		tiles.push_back(Tile(1, 3, Position(0, 0), Position(2, 0), 4));
		tiles.push_back(Tile(1, 3, Position(7, 0), Position(7, 2), 5));
		tiles.push_back(Tile(1, 3, Position(0, 5), Position(0, 7), 6));
		tiles.push_back(Tile(1, 3, Position(5, 7), Position(7, 7), 7));

		tiles.push_back(Tile(2, 2, Position(1, 1), Position(2, 2), 8));
		tiles.push_back(Tile(2, 2, Position(5, 1), Position(6, 2), 9));
		tiles.push_back(Tile(2, 2, Position(3, 3), Position(4, 4), 10));
		tiles.push_back(Tile(2, 2, Position(1, 5), Position(2, 6), 11));
		tiles.push_back(Tile(2, 2, Position(5, 5), Position(6, 6), 12));

		tiles.push_back(Tile(2, 3, Position(3, 0), Position(4, 2), 13));
		tiles.push_back(Tile(2, 3, Position(0, 3), Position(2, 4), 14));
		tiles.push_back(Tile(2, 3, Position(5, 3), Position(7, 4), 15));
		tiles.push_back(Tile(2, 3, Position(3, 5), Position(4, 7), 16));
	}
	else if (type == 7){
		tiles.push_back(Tile(1, 2, Position(6, 0), Position(7, 0), 0));
		tiles.push_back(Tile(1, 2, Position(2, 2), Position(2, 3), 1));
		tiles.push_back(Tile(1, 2, Position(0, 5), Position(1, 5), 2));
		tiles.push_back(Tile(1, 2, Position(6, 5), Position(7, 5), 3));

		tiles.push_back(Tile(1, 3, Position(5, 0), Position(5, 2), 4));
		tiles.push_back(Tile(1, 3, Position(2, 4), Position(4, 4), 5));
		tiles.push_back(Tile(1, 3, Position(4, 5), Position(4, 7), 6));
		tiles.push_back(Tile(1, 3, Position(5, 5), Position(5, 7), 7));

		tiles.push_back(Tile(2, 2, Position(0, 0), Position(1, 1), 8));
		tiles.push_back(Tile(2, 2, Position(3, 2), Position(4, 3), 9));
		tiles.push_back(Tile(2, 2, Position(6, 1), Position(7, 2), 10));
		tiles.push_back(Tile(2, 2, Position(0, 6), Position(1, 7), 11));
		tiles.push_back(Tile(2, 2, Position(6, 6), Position(7, 7), 12));

		tiles.push_back(Tile(2, 3, Position(2, 0), Position(4, 1), 13));
		tiles.push_back(Tile(2, 3, Position(5, 3), Position(7, 4), 14));
		tiles.push_back(Tile(2, 3, Position(0, 2), Position(1, 4), 15));
		tiles.push_back(Tile(2, 3, Position(2, 5), Position(3, 7), 16));
	}
	
	for (auto tile : tiles){
		for (auto marble : tile.marbles){
			//indexOfTileInPosition[marble.first] = tile.indexTile;
			//indexOfTileInPosition.insert((std::make_pair(marble.first, tile.indexTile)));
			tileInPosition[marble.first.horizontal][marble.first.vertical] = tile.indexTile;
			sizeTileInPosition[marble.first.horizontal][marble.first.vertical] = tile.size;
		}
	}
}


// 
void Board::setBit(Position p){
	taken.set((p.horizontal * 8) + p.vertical);
}

void Board::clearBit(Position p){
	taken.reset((p.horizontal * 8) + p.vertical);
}

int Board::getTileInPosition(Position p){
	return tileInPosition[p.horizontal][p.vertical];
}

int Board::getSizeTileInPosition(Position p){
	return sizeTileInPosition[p.horizontal][p.vertical];
}