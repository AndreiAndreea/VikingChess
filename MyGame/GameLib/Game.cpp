#include "Game.h"
#include<iostream>

Game::Game() : m_turn(0)
{

}

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}

Board Game::GetBoard() const
{
	return m_board;
}

void Game::Play()
{
	std::cout << "Test";
}

EPlayer Game::GetWinner() const
{
	if (IsGameOver())
	{
		if (m_turn)
			return EPlayer::Attacker;
		return EPlayer::Defender;
	}

	return EPlayer::None;
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

EPlayer Game::GetCurrentPlayer() const
{
	if (m_turn)
		return EPlayer::Attacker;
	return EPlayer::Defender;

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
	if (pos.length() == 2)
	{
		convertedPos.first = 11 - (pos[1] - '0') + 1; // linie
		convertedPos.second = pos[0] - 'A' + 1;   // coloana
	}
	else
	{
		//coloana 
		convertedPos.second = pos[0] - 'A' + 1;
		//linie - pos[1] si pos[2]
		convertedPos.first = 11 - ((pos[1] - '0') * 10 + (pos[2] - '0')) + 1;
	}

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
		//se schimba randul si se returneaza true daca mutarea a fost valida
		m_turn = 1 - m_turn;
		return true;
	}
	return false;

}

PieceInfo::PieceInfo(EPieceType type, EPieceRole role)
	: m_type(type), m_role(role)
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