#include "King.h"
#include "Board.h"


King::King(EPieceRole role)
    : Piece(EPieceType::King, role)
{

}

bool King::CanMove(Position startPos, Position endPos, const Board& board)
{
	PositionList possibleMoves;
	possibleMoves = GetPossibleMoves(startPos, board);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), endPos) != possibleMoves.end())
		return true;

	return false;
}


PositionList King::GetPossibleMoves(Position piecePos, const Board& board)
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
