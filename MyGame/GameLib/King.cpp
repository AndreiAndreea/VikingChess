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

bool King::IsThreatened(Position piecePos, const Board& board)
{
	// The king is threatened if it is surrounded by 3 attackers
	// Down position open
	if (piecePos.second - 1 >= 1 && piecePos.first - 1 >= 1 && piecePos.second + 1 <= 11 &&
		board.GetPiece(Position(piecePos.first, piecePos.second - 1)) &&
		board.GetPiece(Position(piecePos.first - 1, piecePos.second)) &&
		board.GetPiece(Position(piecePos.first, piecePos.second + 1)) &&
		board.GetBoard()[piecePos.first][piecePos.second - 1]->Is(EPieceType::Warrior, EPieceRole::Attacker) &&
		board.GetBoard()[piecePos.first - 1][piecePos.second]->Is(EPieceType::Warrior, EPieceRole::Attacker) &&
		board.GetBoard()[piecePos.first][piecePos.second + 1]->Is(EPieceType::Warrior, EPieceRole::Attacker))
		return true;	

	// Up position open
	if (piecePos.second - 1 >= 1 && piecePos.first + 1 <= 11 && piecePos.second + 1 <= 11 &&
		board.GetPiece(Position(piecePos.first, piecePos.second - 1)) &&
		board.GetPiece(Position(piecePos.first + 1, piecePos.second)) &&
		board.GetPiece(Position(piecePos.first, piecePos.second + 1)) &&
		board.GetBoard()[piecePos.first][piecePos.second - 1]->Is(EPieceType::Warrior, EPieceRole::Attacker) &&
		board.GetBoard()[piecePos.first + 1][piecePos.second]->Is(EPieceType::Warrior, EPieceRole::Attacker) &&
		board.GetBoard()[piecePos.first][piecePos.second + 1]->Is(EPieceType::Warrior, EPieceRole::Attacker))
		return true;

	return false;
}


PositionList King::GetPossibleMoves(Position piecePos, const Board& board)
{
	PositionList possibleMoves;

	// check left
	for (int j = piecePos.second - 1; j >= 1 && board.GetBoard()[piecePos.first][j] == nullptr; j--)
		if (!IsThreatened(Position(piecePos.first, j), board))
			possibleMoves.push_back(Position(piecePos.first, j));

	// check right
	for (int j = piecePos.second + 1; j <= 11 && board.GetBoard()[piecePos.first][j] == nullptr; j++)
		if (!IsThreatened(Position(piecePos.first, j), board))
			possibleMoves.push_back(Position(piecePos.first, j));

	// check up
	for (int i = piecePos.first - 1; i >= 1 && board.GetBoard()[i][piecePos.second] == nullptr; i--)
		if (!IsThreatened(Position(i, piecePos.second), board))
			possibleMoves.push_back(Position(i, piecePos.second));

	// check down
	for (int i = piecePos.first + 1; i <= 11 && board.GetBoard()[i][piecePos.second] == nullptr; i++)
		if (!IsThreatened(Position(i, piecePos.second), board))
			possibleMoves.push_back(Position(i, piecePos.second));

	return possibleMoves;
}
