#ifndef _BOARD_H_
#define _BOARD_H_

constexpr int SIZE = 3;
constexpr char DIGITS[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

class Board
{
public:
	Board() = default;
	virtual ~Board() = default;

	virtual void init(); // init board
	virtual void draw(); // draw board on screen
	virtual bool check(); // check win condition
	virtual bool update(int position); // populate with mark 

	virtual char* getBoard()
	{
		return &board_[0][0];
	}

	virtual char getMark()
	{
		return mark_;
	}

private:
	char board_[SIZE][SIZE];
	char mark_;
};

#endif
