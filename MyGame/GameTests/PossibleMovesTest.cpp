#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include<vector>

#include "Warrior.h"
#include "Board.h"


class PossibleMovesTest : public testing::Test {

	void SetUp() override
	{
		warrior = new Warrior(EPieceRole::Attacker);
	}

	void TearDown() override
	{
		delete warrior;
	}

protected:
	Warrior* warrior;

};

TEST_F(PossibleMovesTest, AttackerWestWarrior) {
	Board board;
	Position startPos(6, 2);
	std::vector<Position> vector = { Position(6,3),Position(5,2),Position(4,2) ,Position(3,2),Position(2,2) ,
		Position(1,2),Position(7,2), Position(8,2),Position(9,2),Position(10,2),Position(11,2) };
	EXPECT_EQ(board.GetBoard()[6][2]->GetPossibleMoves(startPos, board), vector);
}