#pragma once

#include "Piece.h"
#include "King.h"
#include "Warrior.h"


#include<memory>
#include<vector>

//using Position = std::pair<int, int>;
using BoardType = std::vector<std::vector<PiecePtr>>;

class Board
{
public:
	Board();
	Board(BoardType board);
	void InitializeBoard();
	bool MakeMove(Position startPos, Position endPos);
	BoardType GetBoard() const;
	//void printBoard();

private:
	BoardType m_board;
};