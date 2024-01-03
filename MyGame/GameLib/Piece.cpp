#include "Piece.h"

EPieceType Piece::GetType() const
{
	return m_type;
}

EPieceRole Piece::GetRole() const
{
	return m_role;
}

Piece::Piece(EPieceType type, EPieceRole role)
{
	m_type = type;
	m_role = role;
}

bool Piece::Is(EPieceType type, EPieceRole role) const
{
	return m_type == type && m_role == role;
}

bool Piece::IsOpposite(EPieceRole role, std::vector<EPieceType> list) const
{
	if (m_role == role)
		return false;

	for (const auto& el : list)
		if (m_type == el)
			return true;

	return false;
}