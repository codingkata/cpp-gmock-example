#ifndef BOARD_MOCK_H_
#define BOARD_MOCK_H_

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Board.h"

struct BoardMock : public Board
{
	// MOCK_METHOD(ReturnType, MethodName, (Args..), (Specs...));
	MOCK_METHOD(void, init, ());
	MOCK_METHOD(void, draw, ());
	MOCK_METHOD(bool, check, ());	
	MOCK_METHOD(bool, update, (int));
};


#endif  // BOARD_MOCK_H_
