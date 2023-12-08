#include "Piece.h"

EPieceType Piece::GetType() const
{
	return m_type;
}

Piece::Piece(EPieceType type, EPieceRole role)
{
	m_type = type;
	m_role = role;
}

EPieceRole Piece::GetRole() const
{
	return m_role;
}

bool Piece::Is(EPieceType type, EPieceRole role) const
{
	return m_type == type && m_role == role;
}

bool Piece::IsOpposite(EPieceRole role, std::initializer_list<EPieceType> list) const
{
	if (m_role == role)
		return false;

	for (const auto& el : list)
		if (m_type == el)
			return true;

	return false;
}