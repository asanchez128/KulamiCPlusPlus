// Author: Amadeus Sanchez

#pragma once
#include "Player.h"
#include "Position.h"
#include "Board.h"
#include <vector>
class Game
{
private:
	enum PlayerNumber{PLAYER_1, PLAYER_2};
	int const INF = 1000000000;
public:
	Position lastPlayedPosition;
	Position secondToLastPlayedPosition;
	Position thirdToLastPlayedPosition;
	int indexLastPlayedTile;
	int indexSecondToLastPlayedTile;
	int indexThirdToLastPlayedPosition;
	Board board;
	Game();
	~Game();
	bool isGameOver();
	bool makeMove(Player, Position);
	bool positionIsInLastPlayedTile(Position);
	bool positionIsInSecondToLastPlayedTile(Position);
	bool positionIsInSameHorizontal(Position);
	bool positionIsInSameVertical(Position);
	void posibleNextMoves(std::vector<Position> &v);
	void getWinner();
	bool computerMakeMove(Player);
	bool computerMakeMoveMinimax(Player);
	int minimax(Position, int, bool, int);
	void unmakeMove(Position, Player);
    void getChildNodes(Position p, std::vector<Position> &v);
};
