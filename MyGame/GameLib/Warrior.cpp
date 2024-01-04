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

bool Warrior::IsSandwich(Position endPos, const Board& board)
{
	// Surrounded vertically
	if (endPos.first - 1 >= 1 && endPos.first + 1 <= 11 &&
		board.GetPiece(Position(endPos.first - 1, endPos.second)) &&
		board.GetPiece(Position(endPos.first + 1, endPos.second)) &&
		IsOpposite(board.GetPiece(Position(endPos.first - 1, endPos.second))->GetRole(), { EPieceType::Warrior,EPieceType::King }) &&
		IsOpposite(board.GetPiece(Position(endPos.first + 1, endPos.second))->GetRole(), { EPieceType::Warrior,EPieceType::King }))
		return true;
	else // Surrounded horizontally
		if (endPos.second - 1 >= 1 && endPos.second + 1 <= 11 &&
			board.GetPiece(Position(endPos.first, endPos.second - 1)) &&
			board.GetPiece(Position(endPos.first, endPos.second + 1)) &&
			IsOpposite(board.GetPiece(Position(endPos.first, endPos.second - 1))->GetRole(), { EPieceType::Warrior,EPieceType::King }) &&
			IsOpposite(board.GetPiece(Position(endPos.first, endPos.second + 1))->GetRole(), { EPieceType::Warrior,EPieceType::King }))
			return true;

	return false;
}


PositionList Warrior::GetPossibleMoves(Position piecePos, const Board& board)
{
	PositionList possibleMoves;

	// check left
	for (int j = piecePos.second - 1; j >= 1 && board.GetBoard()[piecePos.first][j] == nullptr; j--)
		if (!IsSandwich(Position(piecePos.first, j), board))
			possibleMoves.push_back(Position(piecePos.first, j));

	// check right
	for (int j = piecePos.second + 1; j <= 11 && board.GetBoard()[piecePos.first][j] == nullptr; j++)
		if (!IsSandwich(Position(piecePos.first, j), board))
			possibleMoves.push_back(Position(piecePos.first, j));

	// check up
	for (int i = piecePos.first - 1; i >= 1 && board.GetBoard()[i][piecePos.second] == nullptr; i--)
		if (!IsSandwich(Position(i, piecePos.second), board))
			possibleMoves.push_back(Position(i, piecePos.second));

	// check down
	for (int i = piecePos.first + 1; i <= 11 && board.GetBoard()[i][piecePos.second] == nullptr; i++)
		if (!IsSandwich(Position(i, piecePos.second), board))
			possibleMoves.push_back(Position(i, piecePos.second));

	return possibleMoves;
}
