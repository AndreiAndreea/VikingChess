#pragma once

#include "IPiece.h"

#include <string>
#include <memory>
#include <cmath>

class Board;

class Piece : public IPiece
{
public:
	Piece(EPieceType type, EPieceRole role);

	// IPiece implementation
	EPieceRole GetRole() const override;
	EPieceType GetType() const override;

	bool Is(EPieceType type, EPieceRole role) const override;
	bool IsOpposite(EPieceRole role, std::vector<EPieceType> list) const;
	
private:
	EPieceType m_type;
	EPieceRole m_role;
	std::vector<Position> m_possibleMoves;
};

using PiecePtr = std::shared_ptr<Piece>;

//role - defenter or attacker
//type - warrior or king