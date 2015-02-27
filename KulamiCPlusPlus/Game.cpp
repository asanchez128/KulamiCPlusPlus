// Author: Amadeus Sanchez
#include "Game.h"
#include "Board.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>     /* srand, rand */
#include <ctime>    
#define START 0
#define END 7
Game::Game()
{
	indexLastPlayedTile = -1;
	indexSecondToLastPlayedTile = -1;
	lastPlayedPosition.horizontal = -1;
	lastPlayedPosition.vertical =  - 1;
}

Game::~Game()
{
}

bool Game::isGameOver(){
	bool result = false;
	std::vector<Position> _nextMoves;
	posibleNextMoves(_nextMoves);
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
				thirdToLastPlayedPosition = secondToLastPlayedPosition;
				secondToLastPlayedPosition = lastPlayedPosition;
				lastPlayedPosition = position;

				indexThirdToLastPlayedPosition = indexSecondToLastPlayedTile;
				indexSecondToLastPlayedTile = indexLastPlayedTile;
				indexLastPlayedTile = board.indexOfTileInPosition[position];
				board.tiles[indexLastPlayedTile].marbles[position] = player.color;
				if (player.color == 1)
					board.tiles[indexLastPlayedTile].marblesPlayer1++;
				else if (player.color == 2)
					board.tiles[indexLastPlayedTile].marblesPlayer2++;

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
	if (lastPlayedPosition.vertical == -1){
		return true;
	}
	else 
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

// v must be an empty vector of type Position
void Game::posibleNextMoves(std::vector<Position> &v){
	if (lastPlayedPosition.horizontal == -1 &&
		lastPlayedPosition.vertical == -1)
	{
		// We are starting off this game
		for (int i = START; i <= END; ++i){
			for (int j = START; j <= END; ++j){
				v.push_back(Position(i, j));
			}
		}
	}
	else
	{
		for (int i = START; i < lastPlayedPosition.horizontal; ++i){
			Position p(i, lastPlayedPosition.vertical);
			if (!board.isPositionTaken(p)){
				if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
					v.push_back(p);
				}
			}
		}

		for (int i = lastPlayedPosition.horizontal + 1; i <= END; ++i){
			Position p(i, lastPlayedPosition.vertical);
			if (!board.isPositionTaken(p)){
				if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
					v.push_back(p);
				}
			}
		}

		for (int i = lastPlayedPosition.vertical + 1; i <= END; ++i){
			Position p(lastPlayedPosition.horizontal, i);
			if (!board.isPositionTaken(p)){
				if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
					v.push_back(p);
				}
			}
		}

		for (int i = START; i < lastPlayedPosition.vertical; ++i){
			Position p(lastPlayedPosition.horizontal, i);
			if (!board.isPositionTaken(p)){
				if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
					v.push_back(p);
				}
			}
		}
	}
	
	return;
}

void Game::getWinner(){
	int counter1, counter2;
	int points1 = 0, points2 = 0;
	for (auto tile : board.tiles){
		counter1 = 0; counter2 = 0;
		for (auto marble : tile.marbles){
			if (marble.second == 1) counter1++;
			else if (marble.second == 2) counter2++;
		}
		if (counter1 > counter2)
		{
			points1 += tile.size;
		}
		else if (counter1 < counter2){
			points2 += tile.size;
		}
	}

	if (points1 > points2){
		printf("Player 1 won by %d\n", points1);
		printf("The score of player 2 was %d\n", points2);
	}
	else if (points2 > points1){
		printf("Player 2 won by %d\n", points2);
		printf("The score of player 1 was %d\n", points1);
	}
	else {
		printf("There was a tie!\n");
	}
	getchar();
	getchar();
}

bool Game::computerMakeMove(Player p){
	std::vector<Position> _v;
	posibleNextMoves(_v);
	if (!_v.empty()){
		srand(time(NULL));
		int randomIndex = rand() % _v.size();
		makeMove(p, Position(_v[randomIndex].horizontal, _v[randomIndex].vertical));
		printf("Computer move:\nhorizontal:%d\nvertical:%d\n", _v[randomIndex].horizontal, _v[randomIndex].vertical);
		return true;
	}
	return false;
}

void Game::getChildNodes(Position q, std::vector<Position> &v)
{
		for (int i = START; i < q.horizontal; ++i){
			Position p(i, q.vertical);
			if (!board.isPositionTaken(p)){
				if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
					v.push_back(p);
				}
			}
		}

		for (int i = q.horizontal + 1; i <= END; ++i){
			Position p(i, q.vertical);
			if (!board.isPositionTaken(p)){
				if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
					v.push_back(p);
				}
			}
		}

		for (int i = q.vertical + 1; i <= END; ++i){
			Position p(q.horizontal, i);
			if (!board.isPositionTaken(p)){
				if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
					v.push_back(p);
				}
			}
		}

		for (int i = START; i < q.vertical; ++i){
			Position p(q.horizontal, i);
			if (!board.isPositionTaken(p)){
				if (!(positionIsInLastPlayedTile(p) || positionIsInSecondToLastPlayedTile(p))){
				v.push_back(p);
			}
		}
	}
	return;

}

bool Game::computerMakeMovealphaBeta(Player p){ 
	bool result = false; 
	std::vector<Position> _v;
	posibleNextMoves(_v);
	int maximum = -INF;
	int minimum = INF;
	int alphaBetaMax, alphaBetaMin;
	Position nextMove;
	if (!_v.empty()){
		for (auto move : _v)
		{
			if (p.color == 1)
			{
				alphaBetaMax = alphaBeta(move, 2, -INF, INF, 1);
				if (maximum < alphaBetaMax)
				{
					maximum = alphaBetaMax;
					nextMove = move;
				}
			}
			else
			{
				alphaBetaMin = alphaBeta(move, 2, -INF, INF, 2);
				if (minimum > alphaBetaMin)
				{
					minimum = alphaBetaMin;
					nextMove = move;
				}
			}
				
		}
		printf("Player %d will move %d\n horizontal and %d\n vertical\n", p, nextMove.horizontal, nextMove.vertical);
		
		makeMove(p, nextMove);
		return true;
	}
	return false;

	return result;
}


// I am going to return the same value for any configuration in the meantime.
int Game::alphaBeta(Position node, int depth, int alpha, int beta, int color){
	
	// if depth = 0 or node is a terminal node
	// return the heuristic value of node
	if ((depth == 0) || isGameOver()){
		int sum1 = 0;
		int sum2 = 0;
		for (auto tile : board.tiles){
			if (tile.marblesPlayer1 > tile.marblesPlayer2)
				sum1 += tile.size;
			else if (tile.marblesPlayer1 < tile.marblesPlayer2)
				sum2 += tile.size;
		}
		if (color == 1)
			return sum1 - sum2;
		else
			return sum2 - sum1;
	}
	int val, bestValue;
	if (currentPlayer == color)
	{
		bestValue = -INF;
	}
	else
	{
		bestValue = INF;
	}
	std::vector<Position> _v;
	getChildNodes(node, _v);
	bool done = false;
	for (size_t t = 0; t < _v.size() && !done; ++t){
		Position position = _v[t];
		makeMove(color, position);
		if (color == 1)
			val = alphaBeta(position, depth - 1, alpha, beta, 2);
		else
			val = alphaBeta(position, depth - 1, alpha, beta, 1);
		if (currentPlayer == color){
			if (val > bestValue){
				bestValue = val;
			}
			alpha = std::max(alpha, bestValue);
		}
		else{
			if (val < bestValue){
				bestValue = val;
			}
			beta = std::min(beta, bestValue);
		}
		if (beta <= alpha)break;
		unmakeMove(position, color);
	}
	return bestValue;
}

void Game::unmakeMove(Position position, Player player){
	board.taken[position] = false;
	board.tiles[indexLastPlayedTile].marbles[position] = -1;
	indexLastPlayedTile = indexSecondToLastPlayedTile;
	indexSecondToLastPlayedTile = indexThirdToLastPlayedPosition;
	lastPlayedPosition = secondToLastPlayedPosition;
	secondToLastPlayedPosition = thirdToLastPlayedPosition;

	if (player.color == 1 && indexLastPlayedTile >= 0)
		board.tiles[indexLastPlayedTile].marblesPlayer1--;
	else if (player.color == 2 && indexLastPlayedTile >= 0)
		board.tiles[indexLastPlayedTile].marblesPlayer2--;
}

bool Game::computerMakeMoveMinimax(Player p){
	bool result = false;
	std::vector<Position> _v;
	posibleNextMoves(_v);
	int maximum = -INF;
	int minimum = INF;
	int minimaxMax, minimaxMin;
	Position nextMove;
	if (!_v.empty()){
		for (auto move : _v)
		{
			if (p.color == 1)
			{
				minimaxMax = minimax(move, 2, 1);
				if (maximum < minimaxMax)
				{
					maximum = minimaxMax;
					nextMove = move;
				}
			}
			else
			{
				minimaxMin = minimax(move, 2, 2);
				if (minimum > minimaxMin)
				{
					minimum = minimaxMin;
					nextMove = move;
				}
			}

		}
		printf("Player %d will move %d\n horizontal and %d\n vertical\n", p, nextMove.horizontal, nextMove.vertical);

		makeMove(p, nextMove);
		return true;
	}
	return false;

	return result;
}


// I am going to return the same value for any configuration in the meantime.
int Game::minimax(Position node, int depth, int color){

	// if depth = 0 or node is a terminal node
	// return the heuristic value of node
	if ((depth == 0) || isGameOver()){
		int sum1 = 0;
		int sum2 = 0;
		for (auto tile : board.tiles){
			if (tile.marblesPlayer1 > tile.marblesPlayer2)
				sum1 += tile.size;
			else if (tile.marblesPlayer1 < tile.marblesPlayer2)
				sum2 += tile.size;
		}
		if (color == 1)
			return sum1 - sum2;
		else
			return sum2 - sum1;
	}
	int val, bestValue;
	if (currentPlayer == color)
	{
		bestValue = -INF;
	}
	else
	{
		bestValue = INF;
	}
	std::vector<Position> _v;
	getChildNodes(node, _v);
	bool done = false;
	for (size_t t = 0; t < _v.size() && !done; ++t){
		Position position = _v[t];
		makeMove(color, position);
		if (color == 1)
			val = minimax(position, depth - 1, 2);
		else
			val = minimax(position, depth - 1, 1);
		if (currentPlayer == color){
			if (val > bestValue){
				bestValue = val;
			}
		}
		else{
			if (val < bestValue){
				bestValue = val;
			}
		}
		unmakeMove(position, color);
	}
	return bestValue;
}