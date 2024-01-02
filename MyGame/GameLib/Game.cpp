#include "Game.h"

Game::Game() : m_turn(0)
{

}

Board Game::GetBoard() const
{
	return m_board;
}

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
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

IPieceInfoPtr Game::GetPieceInfo(int i, int j) const
{
	if (auto piece = m_board.GetBoard()[i][j])
		return std::make_shared<PieceInfo>(piece->GetType(), piece->GetRole());
	return {};
}

void Game::Play()
{
	std::cout << "Test";
}