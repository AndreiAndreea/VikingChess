#include "Game.h"
#include<iostream>

Game::Game() : m_turn(0),
m_state(EGameState::Playing)
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
	// Perform actions based on the current state
	if (IsStatePlaying())
	{
		// Implement the logic for player moves or other actions in the "Playing" state
		// For now, you can just print a message:
		std::cout << "Playing...\n";
	}
	else if (IsState(EGameState::DefendersWon))
	{
		// Implement the logic for the "DefendersWon" state
		std::cout << "Defenders won!\n";
	}
	else if (IsState(EGameState::AttackersWon))
	{
		// Implement the logic for the "AttackersWon" state
		std::cout << "Attackers won!\n";
	}
}

void Game::PlayerMove(const std::string& startPos, const std::string& endPos)
{
	if (MakeMove(startPos, endPos))
	{
		// Check for game state transitions and update the state
		if (m_board.IsKingInCheckmate())
		{
			UpdateState(EGameState::AttackersWon);
		}
		else
			if (m_board.IsKingWinning())
			{
				UpdateState(EGameState::DefendersWon);
			}
		else
		{
			// Update the state to "Playing" if the game is still in progress
			UpdateState(EGameState::Playing);
		}
	}
}

EPlayer Game::GetWinner() const
{
	if (IsGameOver())
	{
		if (m_turn)
			return EPlayer::Defender;
		return EPlayer::Attacker;
	}

	return EPlayer::None;
}

bool Game::IsGameOver() const
{
	if (m_board.IsKingInCheckmate() || m_board.IsKingWinning())
	{
		return true;
	}
	return false;
}

bool Game::IsStatePlaying() const
{
	return m_state == EGameState::Playing;
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
	{
		std::cout << "Pozitia initiala nu este valida!";
		return false;
	}
	if (m_board.GetBoard()[startPos.first][startPos.second])
		if (m_turn)
		{
			if (m_board.GetBoard()[startPos.first][startPos.second]->GetRole() != EPieceRole::Attacker)
				std::cout << "Piesa aleasa este a adversarului!";
				return false;
		}
		else
		{
			if (m_board.GetBoard()[startPos.first][startPos.second]->GetRole() != EPieceRole::Defender)
				std::cout << "Piesa aleasa este a adversarului!";
				return false;
		}

	if (endPos.first < 1 || endPos.first > 11 || endPos.second < 1 || endPos.second > 11)
	{
		std::cout << "Pozitia finala nu este valida!";
		return false;
	}

	return true;
}

bool Game::IsState(EGameState state) const
{
	return m_state == state;
}

void Game::UpdateState(EGameState state)
{
	if (state == EGameState::DefendersWon || state == EGameState::AttackersWon)
	{
		m_state = state;
	}
	else
	{
		m_state = EGameState::Playing;
	}
}
bool Game::MakeMove(const std::string& startPosStr, const std::string& endPosStr)
{
	Position startPos = ConvertToPos(startPosStr);
	Position endPos = ConvertToPos(endPosStr);

	if (IsInputValid(startPos, endPos))
		//endpos to be different than startpos, so the piece can move somewhere else, 
		// //endpos to be an empty space and startpos to be a piece
		if (startPos != endPos && m_board.GetBoard()[startPos.first][startPos.second] != nullptr &&
			m_board.GetBoard()[endPos.first][endPos.second] == nullptr)
			//check if the move is valid
			if (m_board.MakeMove(startPos, endPos))
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