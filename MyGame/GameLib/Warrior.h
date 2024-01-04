#pragma once

#include "Piece.h"

class Board;


class Warrior : public Piece
{
public:
	Warrior(EPieceRole role);
	bool CanMove(Position startPos, Position endPos, const Board& board);
	bool IsSandwich(Position endPos, const Board& board);
	PositionList GetPossibleMoves(Position piecePos, const Board& board);
};


