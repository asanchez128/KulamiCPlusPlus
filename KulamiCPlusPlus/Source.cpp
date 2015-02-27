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
	int optionPlayer1, optionPlayer2, boardOption;
	printf("Please choose a board (1-7)\n");
	scanf("%d", &boardOption);
	while (boardOption < 1 || boardOption > 7){
		printf("Please enter a valid number to choose a board (1-7)\n");
		printf("Please choose a board (1-7)\n");
		scanf("%d", boardOption);
	}
	game.board.setTypeBoard(boardOption);
	printf("Please choose kind of player for player1\n");
	printf("1.- Human\n2.- Easy AI\n3.- Minimax AI\n4.- Alpha-beta AI\n");
	scanf("%d", &optionPlayer1);
	while (optionPlayer1 < 1 || optionPlayer1 > 3)
	{
		printf("Please enter a valid kind of player\n");
		printf("Please choose kind of player for player1");
		printf("1.- Human\n2.- Easy AI\n3.- Hard AI\n");
		scanf("%d", &optionPlayer1);
	} 

	printf("Please choose kind of player for player2\n");
	printf("1.- Human\n2.- Easy AI\n3.- Minimax AI\n4.- Alpha-beta AI\n");
	scanf("%d", &optionPlayer2);
	while (optionPlayer1 < 1 || optionPlayer1 > 3)
	{
		printf("Please enter a valid kind of player\n");
		printf("Please choose kind of player for player2");
		printf("1.- Human\n2.- Easy AI\n3.- Hard AI\n");
		scanf("%d", &optionPlayer2);
	}


	while (!game.isGameOver() && sum <= 56){
		if (sum % 2 == 1)
		{
			game.currentPlayer = 1;
			if (optionPlayer1 == 1)
			{
				do{
					printf("Please enter move for player 1\n");
					std::cin >> x >> y;
					if (sum == 1){
						game.lastPlayedPosition.horizontal = x;
						game.lastPlayedPosition.vertical = y;
					}
				} while (!game.makeMove(player1, Position(x, y)));
			}
			else if (optionPlayer1 == 2)
			{
				printf("Computer will make a move for player 1\n");
				game.computerMakeMove(player1);
			}
			else if (optionPlayer1 == 3)
			{
				printf("Computer will make a move for player 1\n");
				game.computerMakeMoveMinimax(player1);
			}
			else if (optionPlayer1 == 4)
			{
				printf("Computer will make a move for player 1\n");
				game.computerMakeMovealphaBeta(player1);
			}
		}
		else
		{
			game.currentPlayer = 2;
			if (optionPlayer2 == 1)
			{
				do{
					printf("Please enter move for player 2\n");
					std::cin >> x >> y;
					if (sum == 1){
						game.lastPlayedPosition.horizontal = x;
						game.lastPlayedPosition.vertical = y;
					}
				} while (!game.makeMove(player1, Position(x, y)));
			}
			else if (optionPlayer2 == 2)
			{
				printf("Computer will make a move for player 2\n");
				game.computerMakeMove(player2);
			}
			else if (optionPlayer2 == 3)
			{
				printf("Computer will make a move for player 2\n");
				game.computerMakeMoveMinimax(player2);
			}
			else if (optionPlayer2 == 4)
			{
				printf("Computer will make a move for player 2\n");
				game.computerMakeMovealphaBeta(player2);
			}
		}
		game.board.printBoard();
		std::cout << std::endl << std::endl;
		++sum;
		game.getWinner();
		getchar();
	}
	printf("Done!\n");
	game.getWinner();
	return 0;
}