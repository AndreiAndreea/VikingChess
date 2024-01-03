#include "Warrior.h"
#include "Board.h"


Warrior::Warrior(EPieceRole role)
	: Piece(EPieceType::Warrior, role)
{

}

bool Warrior::CanMove(Position startPos, Position endPos, const Board& board)
{
	EPieceRole role = GetRole();

	//checking the direction of the movement
//trebuie sa implementam daca miscarea e una valida
	if (role == EPieceRole::Attacker) 
	{

	}
	else
	{

	}

	return true;
}


PositionList Warrior::GetPossibleMoves(Position piecePos, const Board& board)
{
	PositionList possibleMoves;


	//for (int i = piecePos.first - 1; i <= piecePos.first + 1; i++)
	//	for (int j = piecePos.second - 1; j <= piecePos.second + 1; j++)
	//	{
	//		if (i >= 1 && i <= 8 && j <= 8 && j >= 1)
	//		{
	//			if (board.GetBoard()[i][j] != nullptr && board.GetBoard()[i][j]->GetColor() != GetColor() && !VerifyKingMovmentCheck(piecePos, Position(i, j), board))
	//				possibleMoves.push_back(Position(i, j));
	//			if (board.GetBoard()[i][j] == nullptr && !VerifyKingMovmentCheck(piecePos, Position(i, j), board))
	//				possibleMoves.push_back(Position(i, j));
	//		}

	//	}
	return possibleMoves;
}
