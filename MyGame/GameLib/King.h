#pragma once

#include "Piece.h"

class Board;

class King : public Piece
{
public:
	King(EPieceRole role);
	bool CanMove(Position startPos, Position endPos, const Board& board);
};

