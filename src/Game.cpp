#include "Game.h"
#include <iostream>

Game::Game(Board* board):
	board_(board)
{}

void Game::run()
{
	board_->init();

	int moves = 0;
	while(moves < 9)
	{
		std::cout << "\n TicTacToe ! \n";
		board_->draw();
		std::cout << "\n Player " << (moves % 2 ? "2" : "1") << "\'s turn:\n";
		int position = 0;
		std::cin >> position;
		while (position > 9 || position < 1)
		{
			std::cout << "\nInvalid input. Please use numbers between 1 and 9!\n";
			std::cin >> position;
		};
		while (!board_->update(position))
		{
			// probably there is already X or O at the given position
			std::cout << "\nInvalid Input. Try again with a valid position!\n";
			std::cin >> position;
		}

		// check if somebody won only if more than 3 moves already
		if (moves > 3)
		{
			if (board_->check())
			{
				board_->draw();
				std::cout << "\nPlayer " << (moves % 2 ? "2" : "1") << " won!\n";
				break;
			} else if(moves == 8)
			{
				std::cout << "\nIt's a draw!\n";
			}
		}
		moves++;
	};

}
