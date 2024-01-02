#include "Game.h"

Game::Game() : m_turn(0)
{

}

Board Game::GetBoard() const
{
	return m_board;
}

EPlayer Game::GetWinner() const
{
	if (IsGameOver())
	{
		if (m_turn)
			return EPlayer::Attacker;
		return EPlayer::Defender;
	}
	//exception or 
	return EPlayer::None;
}

EPlayer Game::GetCurrentPlayer() const
{
	if (m_turn)
		return EPlayer::Attacker;
	return EPlayer::Defender;

}

bool Game::IsGameOver() const
{
	EPieceRole role;
	if (m_turn)
		role = EPieceRole::Attacker;
	else
		role = EPieceRole::Defender;
	/*if (m_board.IsCheckmate(role))
		return true;*/
	return false;
}


void Game::Play()
{
	std::cout << "Test";
}