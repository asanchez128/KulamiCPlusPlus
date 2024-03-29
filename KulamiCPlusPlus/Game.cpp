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
#define MAX_SIZE 6

Game::Game()
{
	indexLastPlayedTile = -1;
	indexSecondToLastPlayedTile = -1;
	lastPlayedPosition.horizontal = -1;
	lastPlayedPosition.vertical = -1;
	indexMoves = -1;
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
				board.setBit(position);
				//thirdToLastPlayedPosition = secondToLastPlayedPosition;
				//secondToLastPlayedPosition = lastPlayedPosition;
				lastPlayedPosition = position;

				//indexThirdToLastPlayedPosition = indexSecondToLastPlayedTile;
				//indexSecondToLastPlayedTile = indexLastPlayedTile;
				int indexPlayedTile = board.getTileInPosition(position);
				board.tiles[indexPlayedTile].marbles[position] = player.color;
				if (player.color == 1)
					board.tiles[indexPlayedTile].marblesPlayer1++;
				else if (player.color == 2)
					board.tiles[indexPlayedTile].marblesPlayer2++;
				moves[++indexMoves] = (Move(position, indexPlayedTile, player.color));
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
	if (indexMoves >= 0){
		indexLastPlayedTile = moves[indexMoves].tileNumber;
	}
	else{
		indexLastPlayedTile = -1;
	}

	if (board.getTileInPosition(position) == indexLastPlayedTile){
		result = true;
	}
	return result;
}

bool Game::positionIsInSameVertical(Position position){
	// No moves yet.
	if (indexMoves < 0){
		return true;
	}
	else 
		return moves[indexMoves].position.vertical == position.vertical;
}

bool Game::positionIsInSameHorizontal(Position position){
	if (indexMoves < 0){
		return true;
	}
	else
		return moves[indexMoves].position.horizontal == position.horizontal;
}
bool Game::positionIsInSecondToLastPlayedTile(Position position){
	// check for out-of-bounds position
	bool result = false;
	if (indexMoves > 0)
	if (board.getTileInPosition(position) == moves[indexMoves - 1].tileNumber){
		result = true;
	}
	return result;
}

// v must be an empty vector of type Position
void Game::posibleNextMoves(std::vector<Position> &v){
	if (indexMoves < 0)
	{
		// We are starting off this game
		for (int i = START; i <= END; ++i){
			for (int j = START; j <= END; ++j){
				if (board.getSizeTileInPosition(Position(i, j)) == MAX_SIZE){
					v.push_back(Position(i, j));
				}
			}
		}
	}

	else
	{
		lastPlayedPosition = moves[indexMoves].position;
		// Assume that 
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
	sort(v.begin(), v.end(), [&](const Position & a, const Position & b) -> bool{
		return board.getSizeTileInPosition(a) > board.getSizeTileInPosition(b);
	});

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
//	getchar();
//	getchar();
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

	sort(v.begin(), v.end(), [&](const Position & a, const Position & b) -> bool{
		return board.getSizeTileInPosition(a) > board.getSizeTileInPosition(b);
	});
	return;

}

bool Game::computerMakeMovealphaBeta(Player p){ 
	bool result = false; 
	std::vector<Position> _v;
	posibleNextMoves(_v);
	int maximum = -INF;
	//int minimum = INF;
	int alphaBetaMax, alphaBetaMin;
	Position nextMove;
	if (!_v.empty()){
		for (auto move : _v)
		{
			makeMove(p.color, move);
			if (p.color == 1)
			 alphaBetaMax = alphaBeta(move, 3, -INF, INF, 2);
			else
				alphaBetaMax = alphaBeta(move, 3, -INF, INF, 1);
			alphaBetaMax += board.getSizeTileInPosition(move);
			if (maximum < alphaBetaMax)
			{
				maximum = alphaBetaMax;
				nextMove = move;
			}
			unmakeMove(move, p.color);
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
		if (currentPlayer == 1)
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
	//makeMove(color, node);
	getChildNodes(node, _v);
	//bool done = false;
	for (size_t t = 0; t < _v.size(); ++t){
		Position position = _v[t];
		if (color == 1){
			makeMove(1, position);
			val = alphaBeta(position, depth - 1, alpha, beta, 2);
		}
		else{
			makeMove(2, position);
			val = alphaBeta(position, depth - 1, alpha, beta, 1);
		}
		
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
		unmakeMove(position, color);
		if (beta <= alpha)break;
	}
	//unmakeMove(node, color);
	return bestValue;
}

// This function is giving me a lot of trouble.
void Game::unmakeMove(Position position, Player player){
	board.clearBit(position);
	// Safeguard vs possible invalid values.
	indexLastPlayedTile = board.getTileInPosition(position);
	
	board.tiles[indexLastPlayedTile].marbles[position] = -1;
	/*indexLastPlayedTile = indexSecondToLastPlayedTile;
	indexSecondToLastPlayedTile = indexThirdToLastPlayedPosition;
	indexThirdToLastPlayedPosition = -1;
	lastPlayedPosition = secondToLastPlayedPosition; 
	secondToLastPlayedPosition = thirdToLastPlayedPosition;
	thirdToLastPlayedPosition = Position(-1, -1);*/

	if (indexMoves >= 0){
		indexMoves--;
	}
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
		if (currentPlayer == 1)
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