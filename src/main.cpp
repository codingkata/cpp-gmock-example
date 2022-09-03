#include <iostream>
#include "Board.h"
#include "Game.h"

int main()
{
	Board* board = new Board();
	Game game(board);
	game.run();

	delete board;
	return 0;
}
