#pragma once
#include "Player.h"
#include "Position.h"
#include "Board.h"
#include <vector>
class Game
{
private:
	
	
public:
	Position lastPlayedPosition;
	int indexLastPlayedTile;
	int indexSecondToLastPlayedTile;
	Board board;
	Game();
	~Game();
	bool isGameOver();
	bool makeMove(Player, Position);
	bool positionIsInLastPlayedTile(Position);
	bool positionIsInSecondToLastPlayedTile(Position);
	bool positionIsInSameHorizontal(Position);
	bool positionIsInSameVertical(Position);
	std::vector<std::pair<int, int>> posibleNextMoves();
	void getWinner();
};

