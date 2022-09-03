#include "gtest/gtest.h"
#include "string.h"
#include "Board.h"

struct BoardBase : public ::testing::Test
{
	void SetUp()
	{
		board_.init();		
	}
	void TearDown()
	{
	}

	Board board_;
};

TEST_F(BoardBase, ShouldInit)
{
	EXPECT_EQ(board_.getMark(), 'X');
	char * actualBoard = board_.getBoard();
	int digit = 1;
	for (int i = 0; i < 9; i++)
		EXPECT_EQ(actualBoard[i], DIGITS[digit++]);
}

TEST_F(BoardBase, ShouldDraw)
{
	std::string expected;
	expected+="-   -   -   -\n";
	expected+="| 1 | 2 | 3 | \n";
	expected+="-   -   -   -\n";
	expected+="| 4 | 5 | 6 | \n";
	expected+="-   -   -   -\n";
	expected+="| 7 | 8 | 9 | \n";
	expected+="-   -   -   -\n";
	
	testing::internal::CaptureStdout();

	board_.draw();

	EXPECT_EQ(testing::internal::GetCapturedStdout(), expected);
}

TEST_F(BoardBase, ShouldUpdate)
{
	std::string expected;
	expected+="-   -   -   -\n";
	expected+="| 1 | 2 | 3 | \n";
	expected+="-   -   -   -\n";
	expected+="| 4 | X | 6 | \n";
	expected+="-   -   -   -\n";
	expected+="| 7 | 8 | 9 | \n";
	expected+="-   -   -   -\n";

	EXPECT_EQ(board_.getMark(), 'X');

	board_.update(5);

	EXPECT_EQ(board_.getMark(), 'O');

	testing::internal::CaptureStdout();

	board_.draw();

	EXPECT_EQ(testing::internal::GetCapturedStdout(), expected);
}

TEST_F(BoardBase, ShouldCheckReturnTrueForLine)
{
	board_.update(1); // X mark
	board_.update(4); // O mark
	board_.update(2); // X mark
	board_.update(5); // O mark
	board_.update(3); // X mark

	EXPECT_TRUE(board_.check());
}
	
TEST_F(BoardBase, ShouldCheckReturnTrueForColumn)
{
	board_.update(1); // X mark
	board_.update(2); // O mark
	board_.update(6); // X mark
	board_.update(5); // O mark
	board_.update(7); // X mark
	board_.update(8); // O mark

	EXPECT_TRUE(board_.check());
}

TEST_F(BoardBase, ShouldCheckReturnTrueForDiag)
{
	board_.update(1); // X mark
	board_.update(2); // O mark
	board_.update(5); // X mark
	board_.update(6); // O mark
	board_.update(9); // X mark

	EXPECT_TRUE(board_.check());
}

TEST_F(BoardBase, ShouldCheckReturnFalse)
{
	board_.update(1); // X mark
	board_.update(2); // O mark
	board_.update(3); // X mark

	EXPECT_FALSE(board_.check());
}
