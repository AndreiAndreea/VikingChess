#pragma once

#include <utility>

class Board;

enum class EPieceRole
{
	Attacker,
	Defender
};


enum class EPieceType
{
	Warrior,
	King
};

using Position = std::pair<int, int>;

class IPiece
{
public:
	virtual EPieceRole GetRole() const = 0;
	virtual EPieceType GetType() const = 0;
	virtual bool CanMove(Position startPos, Position endPos, const Board& board) = 0;

	virtual ~IPiece() = default;
};