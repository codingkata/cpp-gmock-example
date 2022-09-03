#include "gtest/gtest.h"
#include "Game.h"

#include "BoardMock.h"

struct GameTest : public testing::Test
{
	GameTest():
		game_(&board_)
	{}

	void SetUp() {}
	void TearDown() {}

	Game game_;
	BoardMock board_;
};

TEST_F(GameTest, TheGameShouldRun)
{
	EXPECT_CALL(board_, init()).Times(1);
	EXPECT_CALL(board_, draw()).Times(6);
	EXPECT_CALL(board_, update(testing::_))
		.WillOnce(testing::Return(false))
		.WillRepeatedly(testing::Return(true));
	EXPECT_CALL(board_, check())
		.WillOnce(testing::Return(true));

	std::streambuf* orig = std::cin.rdbuf();
	std::istringstream input("10 1 1 2 3 4 5");
	std::cin.rdbuf(input.rdbuf());

	game_.run();

	std::cin.rdbuf(orig);
}
