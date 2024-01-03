#include "Warrior.h"
#include "Board.h"


Warrior::Warrior(EPieceRole role)
	: Piece(EPieceType::Warrior, role)
{

}

bool Warrior::CanMove(Position startPos, Position endPos, const Board& board)
{
	PositionList possibleMoves;
	possibleMoves = GetPossibleMoves(startPos, board);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), endPos) != possibleMoves.end())
		return true;

	return false;
}


PositionList Warrior::GetPossibleMoves(Position piecePos, const Board& board)
{
	PositionList possibleMoves;

	// check left
	for (int j = piecePos.second - 1; j >= 0 && board.GetBoard()[piecePos.first][j] != nullptr; j--)
	{
		if (board.GetBoard()[piecePos.first][j] == nullptr)
			possibleMoves.push_back(Position(piecePos.first, j));
	}

	// check right
	for (int j = piecePos.second + 1; j < 11 && board.GetBoard()[piecePos.first][j] != nullptr; j++)
	{
		if (board.GetBoard()[piecePos.first][j] == nullptr)
			possibleMoves.push_back(Position(piecePos.first, j));
	}

	// check up
	for (int i = piecePos.first + 1; i < 11 && board.GetBoard()[i][piecePos.second] != nullptr; i++)
	{
		if (board.GetBoard()[i][piecePos.second] == nullptr)
			possibleMoves.push_back(Position(i, piecePos.second));
	}

	//check down
	for (int i = piecePos.first - 1; i >= 0 && board.GetBoard()[i][piecePos.second] != nullptr; i--)
	{
		if (board.GetBoard()[i][piecePos.second] == nullptr)
			possibleMoves.push_back(Position(i, piecePos.second));
	}

	return possibleMoves;
}
