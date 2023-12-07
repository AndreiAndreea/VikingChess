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
