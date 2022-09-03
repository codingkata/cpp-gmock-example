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
	int i = 0;
	int j = 0;
	// check lines
	for (auto i = 0; i < 3; i++)
	{
		if (board_[i][j] == board_[i][++j] && board_[i][j] == board_[i][++j])
			return true;
		j = 0;
	}

	// check columns
	for (auto j = 0; j < 3; j++)
	{
		if (board_[i][j] == board_[++i][j] && board_[i][j] == board_[++i][j])
			return true;
		i=0;
	}

	// check diags
	if (board_[i][j] == board_[++i][++j] && board_[i][j] == board_[++i][++j])
		return true;

	i = 0;
	j = SIZE - 1;
	return board_[i][j] == board_[++i][--j] && board_[i][j] == board_[++i][--j];
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

