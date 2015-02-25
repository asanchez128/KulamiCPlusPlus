// Author: Amadeus Sanchez

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Game.h"
#include <iostream>

int main(){
	Game game;
	Player player1(1);
	Player player2(2);
	int sum = 1;
	int x, y;
	while (!game.isGameOver() && sum <= 56){
		if (sum % 2 == 1)
		{
			printf("Computer will make a move\n");
			game.computerMakeMoveMinimax(player1);
		}
		else
		{
			printf("Computer will make a move\n");
			game.computerMakeMoveMinimax(player2);
		}
		game.board.printBoard();
		std::cout << std::endl << std::endl;
		++sum;
	}
	game.getWinner();
	return 0;
}