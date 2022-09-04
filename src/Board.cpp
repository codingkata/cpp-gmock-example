#include "Board.h"

#include <iostream>

void Board::init()
{
	mark_ = 'X';
	int digit = 1;
	for (auto line = 0; line < SIZE; line++)
	{
		for (auto column = 0; column < SIZE; column++)
		{
			board_[line][column] = DIGITS[digit++];
		}
	}	
}

void Board::draw()
{
	std::cout << "-   -   -   -\n";
	for (auto line = 0; line < SIZE; line++)
	{
		for (auto column = 0; column < SIZE; column++)
		{
			std::cout << "| " << board_[line][column] << " ";
		}
		std::cout << "| \n";
		std::cout << "-   -   -   -\n";
	}
}

bool Board::check()
{
	// check rows
	for (auto i = 0; i < 3; i++)
	{
		if (board_[i][0] == board_[i][1] && board_[i][1] == board_[i][2])
			return true;
	}

	// check columns
	for (auto j = 0; j < 3; j++)
	{
		if (board_[0][j] == board_[1][j] && board_[1][j] == board_[2][j])
			return true;
	}
	// check back-slash
	if (board_[0][0] == board_[1][1] && board_[1][1] == board_[2][2])
		return true;
	// check slash
	return board_[0][2] == board_[1][1] && board_[1][1] == board_[2][0];
}

bool Board::update(int position)
{
	bool updated = false;
	for (auto line = 0; line < SIZE; line++)
	{
		for (auto column = 0; column < SIZE; column++)
		{
			if(board_[line][column] == DIGITS[position])
			{
				board_[line][column] = mark_;
				updated = true;
			}
		}
	}

	// change mark only if updated
	if (updated)
	{
		if (mark_ == 'X')
			mark_ = 'O';
		else
	   		mark_ = 'X';
	}

	return updated;
}

