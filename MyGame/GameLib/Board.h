#pragma once

#include "Piece.h"
#include "King.h"
#include "Warrior.h"


#include<memory>
#include<vector>

//using Position = std::pair<int, int>;
using PieceMatrix = std::vector<std::vector<PiecePtr>>;
using ConfigMatrix = std::vector<std::pair<PiecePtr, Position>>;

class Board
{
public:
	Board();
	Board(ConfigMatrix piecePos);

	void InitializeBoard();

	PieceMatrix GetBoard() const;
	void SetPiece(Position pos, EPieceRole role, EPieceType type);
	void SetPieceToNullptr(Position pos);

	bool MakeMove(Position startPos, Position endPos);
	bool IsKingInCheck(Position startPos, Position endPos, EPieceRole pieceRole) const;

private:
	PieceMatrix m_board;
};