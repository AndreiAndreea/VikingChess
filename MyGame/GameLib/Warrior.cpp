#include "Warrior.h"
#include "Board.h"


Warrior::Warrior(EPieceRole role)
	: Piece(EPieceType::Warrior, role)
{

}

bool Warrior::CanMove(Position startPos, Position endPos, const Board& board)
{
	EPieceRole role = GetRole();

	//checking the direction of the movement
//trebuie sa implementam daca miscarea e una valida
	if (role == EPieceRole::Attacker) 
	{

	}
	else
	{

	}

	return true;
}
