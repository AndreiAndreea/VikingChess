#include "King.h"
#include "Board.h"


King::King(EPieceRole role)
    : Piece(EPieceType::King, role)
{

}

bool King::CanMove(Position startPos, Position endPos, const Board& board)
{
    return false;
}
