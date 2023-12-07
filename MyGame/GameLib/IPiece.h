#pragma once

#include <utility>

class Board;

enum class EPieceType
{
	Attacker,
	Defender,
	King
};

using Position = std::pair<int, int>;

class IPiece
{
public:
	virtual EPieceType GetType() const = 0;
	virtual bool CanMove(Position startPos, Position endPos, const Board& board) = 0;

	virtual ~IPiece() = default;
};