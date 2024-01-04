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

	// check left
	for (int j = piecePos.second - 1; j >= 1 && board.GetBoard()[piecePos.first][j] == nullptr; j--)
		possibleMoves.push_back(Position(piecePos.first, j));

	// check right
	for (int j = piecePos.second + 1; j <= 11 && board.GetBoard()[piecePos.first][j] == nullptr; j++)
		possibleMoves.push_back(Position(piecePos.first, j));

	// check up
	for (int i = piecePos.first - 1; i >= 1 && board.GetBoard()[i][piecePos.second] == nullptr; i--)
		possibleMoves.push_back(Position(i, piecePos.second));

	// check down
	for (int i = piecePos.first + 1; i <= 11 && board.GetBoard()[i][piecePos.second] == nullptr; i++)
		possibleMoves.push_back(Position(i, piecePos.second));

	return possibleMoves;
}
