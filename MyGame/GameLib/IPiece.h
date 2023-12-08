#pragma once

#include <utility>
#include <vector>

#include "EPieceRole.h"
#include "EPieceType.h"

class Board;

using Position = std::pair<int, int>;
using PositionList = std::vector<Position>;

class IPiece
{
public:
	virtual EPieceRole GetRole() const = 0;
	virtual EPieceType GetType() const = 0;
	virtual bool CanMove(Position startPos, Position endPos, const Board& board) = 0;
	virtual PositionList GetPossibleMoves(Position piecePos, const Board& board) = 0;
	virtual bool Is(EPieceType type, EPieceRole role) const = 0;

	virtual ~IPiece() = default;
};