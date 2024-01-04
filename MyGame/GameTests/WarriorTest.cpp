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

TEST_F(WarriorTest, InvalidMoveDiagonally) {
	Board board;

	Position startPos(6, 1);
	Position endPos(5, 2);
	board.SetPiece(startPos, EPieceRole::Attacker, EPieceType::Warrior);
	bool canMove = warrior->CanMove(startPos, endPos, board);

	EXPECT_FALSE(canMove);
}

TEST_F(WarriorTest, InvalidMoveDownwards) {
	Board board;

	Position startPos(2, 6);
	Position endPos(4, 6);
	board.SetPiece(startPos, EPieceRole::Attacker, EPieceType::Warrior);
	bool canMove = warrior->CanMove(startPos, endPos, board);

	EXPECT_FALSE(canMove);
}

TEST_F(WarriorTest, ValidMoveUpwards) {
	Board board;

	Position startPos(11, 7);
	Position endPos(8, 7);
	board.SetPiece(startPos, EPieceRole::Attacker, EPieceType::Warrior);
	bool canMove = warrior->CanMove(startPos, endPos, board);

	EXPECT_TRUE(canMove);
}

TEST_F(WarriorTest, ValidMoveDownwards) {
	Board board;

	Position startPos(6, 10);
	Position endPos(11, 10);
	board.SetPiece(startPos, EPieceRole::Attacker, EPieceType::Warrior);
	bool canMove = warrior->CanMove(startPos, endPos, board);

	EXPECT_TRUE(canMove);
}