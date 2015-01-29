#include "Game.h"
#include "Board.h"
#include <vector>
#include <algorithm>

Game::Game()
{
	indexLastPlayedTile = -1;
	indexSecondToLastPlayedTile = -1;
	lastPlayedPosition.horizontal = -1;
	lastPlayedPosition.vertical - 1;
}


Game::~Game()
{
}

bool Game::isGameOver(){
	bool result = false;
	std::vector<std::pair<int, int>> _nextMoves = posibleNextMoves();
	if (_nextMoves.empty()){
		result = true;
	}
	return result;
}

bool Game::makeMove(Player player, Position position){
	// if position is empty
	bool result = false;
	if (!board.isPositionTaken(position)){
		if (!(positionIsInLastPlayedTile(position) || positionIsInSecondToLastPlayedTile(position))){
			if ((positionIsInSameHorizontal(position) || positionIsInSameVertical(position) ) ){
				board.taken[position] = true;
				lastPlayedPosition = position;
				indexSecondToLastPlayedTile = indexLastPlayedTile;
				indexLastPlayedTile = board.indexOfTileInPosition[position];
				board.tiles[indexLastPlayedTile].marbles[position] = player.color;
				return true;
			}
		}
	}

		// if position is not either in last played tile or second to last played tile
			// If position is either in the same horizontal or the same vertical as last played position
	return false;
}

bool Game::positionIsInLastPlayedTile(Position position){
	// check for out-of-bounds position
	bool result = false;
	if (board.indexOfTileInPosition[position] == indexLastPlayedTile){
		result = true;
	}
	return result;
}

bool Game::positionIsInSameVertical(Position position){
	return lastPlayedPosition.vertical == position.vertical;
}

bool Game::positionIsInSameHorizontal(Position position){
	return lastPlayedPosition.horizontal == position.horizontal;
}
bool Game::positionIsInSecondToLastPlayedTile(Position position){
	// check for out-of-bounds position
	bool result = false;
	if (board.indexOfTileInPosition[position] == indexSecondToLastPlayedTile){
		result = true;
	}
	return result;
}

std::vector<std::pair<int, int>> Game::posibleNextMoves(){
	std::vector<std::pair<int, int>> v;
	for (int i = 1; i < lastPlayedPosition.horizontal; ++i){
		Position p(i, lastPlayedPosition.vertical);
		if (!board.isPositionTaken(p)){
			if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
				v.push_back(std::make_pair(p.horizontal, p.vertical));
			}
		}
	}

	for (int i = lastPlayedPosition.horizontal + 1; i <= 8; ++i){
		Position p(i, lastPlayedPosition.vertical);
		if (!board.isPositionTaken(p)){
			if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
				v.push_back(std::make_pair(p.horizontal, p.vertical));
			}
		}
	}

	for (int i = lastPlayedPosition.vertical + 1; i <= 8; ++i){
		Position p(lastPlayedPosition.horizontal, i);
		if (!board.isPositionTaken(p)){
			if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
				v.push_back(std::make_pair(p.horizontal, p.vertical));
			}
		}
	}
	
	for (int i = 1; i < lastPlayedPosition.vertical; ++i){
		Position p(lastPlayedPosition.horizontal, i);
		if (!board.isPositionTaken(p)){
			if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
				v.push_back(std::make_pair(p.horizontal, p.vertical));
			}
		}
	}
	return v;
}

void Game::getWinner(){
	int counter1, counter2;
	int points1 = 0, points2 = 0;
	for (auto tile : board.tiles){
		counter1 = 0; counter2 = 0;
		for (auto marble : tile.marbles){
			if (marble.second == 1)counter1++;
			else if (marble.second == 2)counter2++;
		}
		if (counter1 > counter2){
			points1 += tile.size;
		}
		else if (counter1 < counter2){
			points2 += tile.size;
		}
	}

	if (counter1 > counter2){
		printf("Player 1 won by %d\n", counter1);
		printf("The score of player 2 was\n", counter2);
	}
	else if (counter2 > counter1){
		printf("Player 2 won by %d\n", counter1);
		printf("The score of player 1 was\n", counter2);
	}
	else {
		printf("There was a tie!\n");
	}
}
