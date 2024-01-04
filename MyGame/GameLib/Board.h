#pragma once

#include "Piece.h"
#include "King.h"
#include "Warrior.h"

#include<memory>
#include<vector>

using PieceMatrix = std::vector<std::vector<PiecePtr>>;
using ConfigMatrix = std::vector<std::pair<PiecePtr, Position>>;

class Board
{
public:
	Board();
	Board(int);
	Board(const Board& ob);
	Board(ConfigMatrix piecePos);

	void InitializeBoard();

	PieceMatrix GetBoard() const;
	PiecePtr GetPiece(const Position& pos) const;

	bool MakeMove(Position startPos, Position endPos);


	void SetPiece(const Position& pos, EPieceRole role, EPieceType type);
	void SetPieceToNullptr(const Position& pos);

	bool IsKingInCheck(Position startPos, Position endPos, EPieceRole pieceRole) const;

private:
	PieceMatrix m_board;
};