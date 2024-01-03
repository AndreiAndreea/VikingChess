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

//verifica daca coordonatele sunt valide pentru tabla de 11 pe 11
Position Game::ConvertToPos(const std::string& pos)
{
	Position convertedPos;
	convertedPos.second = pos[0] - 'A' + 1;
	convertedPos.first = 9 - (pos[1] - '0');
	return convertedPos;
}

bool Game::IsInputValid(const Position& startPos, const Position& endPos)
{
	if (startPos.first < 1 || startPos.first > 11 || startPos.second < 1 || startPos.second > 11)
		return false;
	if (m_board.GetBoard()[startPos.first][startPos.second])
		if (m_turn)
		{
			if (m_board.GetBoard()[startPos.first][startPos.second]->GetRole() != EPieceRole::Attacker)
				return false;
		}
		else
		{
			if (m_board.GetBoard()[startPos.first][startPos.second]->GetRole() != EPieceRole::Defender)
				return false;
		}

	if (endPos.first < 1 || endPos.first > 11 || endPos.second < 1 || endPos.second > 11)
		return false;

	return true;
}

bool Game::MakeMove(const std::string& startPosStr, const std::string& endPosStr)
{
	Position startPos = ConvertToPos(startPosStr);
	Position endPos = ConvertToPos(endPosStr);

	if (IsInputValid(startPos, endPos) && m_board.MakeMove(startPos, endPos))
	{
		m_turn = 1 - m_turn;
		return true;
	}
	return false;

}


PieceInfo::PieceInfo(EPieceType type, EPieceRole role)
	: m_type(type)
	, m_role(role)
{

}

EPieceRole PieceInfo::GetRole() const
{
	return m_role;
}

EPieceType PieceInfo::GetType() const
{
	return m_type;
}

void Game::Play()
{
	std::cout << "Test";
}