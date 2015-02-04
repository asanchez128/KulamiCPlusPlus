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
	while (!game.isGameOver()){
		if (sum % 2 == 1){
			do{
				printf("Please enter move for player 1\n");
				std::cin >> x >> y;
				if (sum == 1){
					game.lastPlayedPosition.horizontal = x;
					game.lastPlayedPosition.vertical = y;
				}
			}
			while(!game.makeMove(player1, Position(x, y)));
		}
		else{
			//printf("Please enter move for player 2\n");
			
			//std::cin >> x >> y;
			printf("Computer will make a move\n");
			game.computerMakeMove(player2);
		}
		game.board.printBoard();
		std::cout << std::endl << std::endl;
		++sum;
	}
	game.getWinner();
	return 0;
}