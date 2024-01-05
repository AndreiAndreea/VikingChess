#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include<vector>

#include "Board.h"
#include "King.h"


class KingTest : public testing::Test {

	void SetUp() override
	{
		king = new King(EPieceRole::Defender);
	}

	void TearDown() override
	{
		delete king;
	}

protected:
	King* king;

};

TEST_F(KingTest, KingWins) {
	Board board;
	//set another king on the board	
	board.SetPiece(Position(11, 11),EPieceRole::Defender,EPieceType::King);
	board.SetPieceToNullptr(Position(6, 6));
	EXPECT_TRUE(board.IsKingWinning());
}

TEST_F(KingTest, IsCheckMate) {
	Board board;
	//set another king on the board	
	board.SetPiece(Position(11, 8), EPieceRole::Attacker, EPieceType::Warrior);
	board.SetPiece(Position(10, 8), EPieceRole::Attacker, EPieceType::Warrior);
	board.SetPiece(Position(11, 9), EPieceRole::Attacker, EPieceType::Warrior);
	board.SetPiece(Position(11, 8), EPieceRole::Defender, EPieceType::King);
	board.SetPieceToNullptr(Position(6, 6));
	EXPECT_TRUE(board.IsKingInCheckmate());
}