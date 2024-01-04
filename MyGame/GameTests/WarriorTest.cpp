#include "gtest/gtest.h"

#include "Warrior.h"
#include "Board.h"


class WarriorTest : public testing::Test {

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

TEST_F(WarriorTest, InvalidMoveUpwards) {
	Board board;

	Position startPos(10, 6);
	Position endPos(8, 6);
	board.SetPiece(startPos, EPieceRole::Attacker, EPieceType::Warrior);
	bool canMove = warrior->CanMove(startPos, endPos, board);

	EXPECT_FALSE(canMove);
}