#ifndef _GAME_H_
#define _GAME_H_

#include "Board.h"

class Game
{
public:
	Game(Board* board);
	~Game() = default;

	void run();

private:
	Board* board_;
};

#endif
