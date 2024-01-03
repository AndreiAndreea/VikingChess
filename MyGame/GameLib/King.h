#pragma once

#include "Piece.h"

class Board;

class King : public Piece
{
public:
	King(EPieceRole role);
	PositionList GetPossibleMoves(Position piecePos, const Board& board);

	bool CanMove(Position startPos, Position endPos, const Board& board);
};

