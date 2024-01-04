#include "Board.h"
#include <stdexcept>
#include <iostream>

Board::Board() {
	InitializeBoard();
}

Board::Board(ConfigMatrix piecePos)
{
	//InitializeBoard();
	for (auto it : piecePos)
	{
		switch (it.first->GetType())
		{
		case EPieceType::Warrior:
			m_board[it.second.first][it.second.second] = std::make_shared<Warrior>(it.first->GetRole());
			break;
		case EPieceType::King:
			m_board[it.second.first][it.second.second] = std::make_shared<King>(it.first->GetRole());
			break;
		default:
			break;
		}
	}
}

Board::Board(int)
{
	m_board.resize(11);
	for (int i = 1; i <= 11; i++)
	{
		m_board[i].resize(12);
	}

	for (int x = 1; x <= 11; x++)
		for (int y = 1; y <= 11; y++)
			m_board[x][y] = nullptr;
}

Board::Board(const Board& ob)
{
	m_board = ob.GetBoard();
}

//indexarea de la 1 la 11
void Board::InitializeBoard() {
	m_board.resize(12);
	for (int i = 1; i <= 11; i++) {
		m_board[i].resize(12);
	}

	// Initialize empty squares
	for (int x = 1; x <= 11; x++) {
		for (int y = 1; y <= 11; y++) {
			m_board[x][y] = nullptr;
		}
	}

	// Set up attackers (black pieces)
//N
	m_board[1][4] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[1][5] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[1][6] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[1][7] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[1][8] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[2][6] = std::make_shared<Warrior>(EPieceRole::Attacker);
	//V
	m_board[4][1] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[5][1] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[6][1] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[7][1] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[8][1] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[6][2] = std::make_shared<Warrior>(EPieceRole::Attacker);
	//E
	m_board[4][11] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[5][11] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[6][11] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[7][11] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[8][11] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[6][10] = std::make_shared<Warrior>(EPieceRole::Attacker);
	//S
	m_board[11][4] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[11][5] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[11][6] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[11][7] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[11][8] = std::make_shared<Warrior>(EPieceRole::Attacker);
	m_board[10][6] = std::make_shared<Warrior>(EPieceRole::Attacker);


	// Set up defenders (white pieces)
	m_board[4][6] = std::make_shared<Warrior>(EPieceRole::Defender);

	m_board[5][5] = std::make_shared<Warrior>(EPieceRole::Defender);
	m_board[5][6] = std::make_shared<Warrior>(EPieceRole::Defender);
	m_board[5][7] = std::make_shared<Warrior>(EPieceRole::Defender);

	m_board[6][4] = std::make_shared<Warrior>(EPieceRole::Defender);
	m_board[6][5] = std::make_shared<Warrior>(EPieceRole::Defender);
	m_board[6][5] = std::make_shared<Warrior>(EPieceRole::Defender);
	m_board[6][7] = std::make_shared<Warrior>(EPieceRole::Defender);
	m_board[6][8] = std::make_shared<Warrior>(EPieceRole::Defender);

	m_board[7][5] = std::make_shared<Warrior>(EPieceRole::Defender);
	m_board[7][6] = std::make_shared<Warrior>(EPieceRole::Defender);
	m_board[7][7] = std::make_shared<Warrior>(EPieceRole::Defender);

	m_board[8][6] = std::make_shared<Warrior>(EPieceRole::Defender);

	// Set up the king
	m_board[6][6] = std::make_shared<King>(EPieceRole::Defender);
}

PieceMatrix Board::GetBoard() const
{
	return m_board;
}

PiecePtr Board::GetPiece(const Position& pos) const
{
	return m_board[pos.first][pos.second];
}

void Board::SetPiece(const Position& pos, EPieceRole role, EPieceType type)
{

	switch (type)
	{
	case EPieceType::Warrior:
		m_board[pos.first][pos.second] = std::make_shared<Warrior>(role);
		break;
	case EPieceType::King:
		m_board[pos.first][pos.second] = std::make_shared<King>(role);
		break;
	default:
		break;
	}
}

void Board::SetPieceToNullptr(const Position& pos)
{
	m_board[pos.first][pos.second] = nullptr;
}

static bool IsOpposite(PiecePtr piece, EPieceRole role, std::vector<EPieceType> types)
{
	if (piece)
		if (piece->IsOpposite(role, types))
			return true;

	return false;
}


bool Board::MakeMove(Position startPos, Position endPos)
{
	auto piece = m_board[startPos.first][startPos.second];
	if (piece->CanMove(startPos, endPos, *this))
	{
		if (piece->GetType() == EPieceType::Warrior)
		{
			// Check if king is in check - TO DO
			//if (IsKingLeftInCheck(startPos, endPos, piece->GetColor()))
			//	{
			//		std::cout << "Regele e in sah! Nu se poate face mutarea.";
			//		return false;
			//	}

			// Move warrior to new position
			SetPiece(endPos, piece->GetRole(), piece->GetType());
			SetPieceToNullptr(startPos);
			// ---------------------------------

			// Check if any opponents piece is captured in our sandwich
			// Check opponent horizontally left
			if (endPos.second - 2 >= 1 &&
				m_board[endPos.first][endPos.second - 1] && m_board[endPos.first][endPos.second - 2] &&
				IsOpposite(m_board[endPos.first][endPos.second - 1], piece->GetRole(), { EPieceType::Warrior ,EPieceType::King }) &&
				!IsOpposite(m_board[endPos.first][endPos.second - 2], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
			{
				SetPieceToNullptr(Position(endPos.first, endPos.second - 1));
			}

			// Check opponent horizontally right
			if (endPos.second + 2 <= 11 &&
				m_board[endPos.first][endPos.second + 1] && m_board[endPos.first][endPos.second + 2] &&
				IsOpposite(m_board[endPos.first][endPos.second + 1], piece->GetRole(), { EPieceType::Warrior ,EPieceType::King }) &&
				!IsOpposite(m_board[endPos.first][endPos.second + 2], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
			{
				SetPieceToNullptr(Position(endPos.first, endPos.second + 1));
			}

			// Check opponent vertically up
			if (endPos.first - 2 >= 1 &&
				m_board[endPos.first - 1][endPos.second] && m_board[endPos.first - 2][endPos.second] &&
				IsOpposite(m_board[endPos.first - 1][endPos.second], piece->GetRole(), { EPieceType::Warrior ,EPieceType::King }) &&
				!IsOpposite(m_board[endPos.first - 2][endPos.second], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
			{
				SetPieceToNullptr(Position(endPos.first - 1, endPos.second));
			}

			// Check opponent vertically down
			if (endPos.first + 2 <= 11 &&
				m_board[endPos.first + 1][endPos.second] && m_board[endPos.first + 2][endPos.second] &&
				IsOpposite(m_board[endPos.first + 1][endPos.second], piece->GetRole(), { EPieceType::Warrior, EPieceType::King }) &&
				!IsOpposite(m_board[endPos.first + 2][endPos.second], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
			{
				SetPieceToNullptr(Position(endPos.first + 1, endPos.second));
			}
			// ---------------------------------

			// Check special case sandwich - trap a piece in a corner
			// Top left corner - trap from bottom
			if (endPos.first == 2 && endPos.second == 1 &&
				m_board[endPos.first - 1][endPos.second] && m_board[endPos.first - 1][endPos.second + 1] &&
				IsOpposite(m_board[endPos.first - 1][endPos.second], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }) &&
				!IsOpposite(m_board[endPos.first - 1][endPos.second + 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
			{
				SetPieceToNullptr(Position(endPos.first - 1, endPos.second));
			}
			else // - trap from right
				if (endPos.first == 1 && endPos.second == 2 &&
					m_board[endPos.first][endPos.second - 1] && m_board[endPos.first + 1][endPos.second - 1] &&
					IsOpposite(m_board[endPos.first][endPos.second - 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }) &&
					!IsOpposite(m_board[endPos.first + 1][endPos.second - 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
				{
					SetPieceToNullptr(Position(endPos.first, endPos.second - 1));
				}

			// Top right corner - trap from bottom
			if (endPos.first == 2 && endPos.second == 11 &&
				m_board[endPos.first - 1][endPos.second] && m_board[endPos.first - 1][endPos.second - 1] &&
				IsOpposite(m_board[endPos.first - 1][endPos.second], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }) &&
				!IsOpposite(m_board[endPos.first - 1][endPos.second - 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
			{
				SetPieceToNullptr(Position(endPos.first - 1, endPos.second));
			}
			else // - trap from left
				if (endPos.first == 1 && endPos.second == 10 &&
					m_board[endPos.first][endPos.second + 1] && m_board[endPos.first + 1][endPos.second + 1] &&
					IsOpposite(m_board[endPos.first][endPos.second + 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }) &&
					!IsOpposite(m_board[endPos.first + 1][endPos.second + 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
				{
					SetPieceToNullptr(Position(endPos.first, endPos.second + 1));
				}

			// Bottom left corner - trap from top
			if (endPos.first == 10 && endPos.second == 1 &&
				m_board[endPos.first + 1][endPos.second] && m_board[endPos.first + 1][endPos.second + 1] &&
				IsOpposite(m_board[endPos.first + 1][endPos.second], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }) &&
				!IsOpposite(m_board[endPos.first + 1][endPos.second + 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
			{
				SetPieceToNullptr(Position(endPos.first + 1, endPos.second));
			}
			else // - trap from right
				if (endPos.first == 11 && endPos.second == 2 &&
					m_board[endPos.first][endPos.second - 1] && m_board[endPos.first - 1][endPos.second - 1] &&
					IsOpposite(m_board[endPos.first][endPos.second - 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }) &&
					!IsOpposite(m_board[endPos.first - 1][endPos.second - 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
				{
					SetPieceToNullptr(Position(endPos.first, endPos.second - 1));
				}

			// Bottom right corner - trap from top
			if (endPos.first == 10 && endPos.second == 11 &&
				m_board[endPos.first + 1][endPos.second] && m_board[endPos.first + 1][endPos.second - 1] &&
				IsOpposite(m_board[endPos.first + 1][endPos.second], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }) &&
				!IsOpposite(m_board[endPos.first + 1][endPos.second - 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
			{
				SetPieceToNullptr(Position(endPos.first + 1, endPos.second));
			}
			else // trap from left
				if (endPos.first == 11 && endPos.second == 10 &&
					m_board[endPos.first][endPos.second + 1] && m_board[endPos.first - 1][endPos.second + 1] &&
					IsOpposite(m_board[endPos.first][endPos.second + 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }) &&
					!IsOpposite(m_board[endPos.first - 1][endPos.second + 1], piece->GetRole(), { EPieceType::Warrior,EPieceType::King }))
				{
					SetPieceToNullptr(Position(endPos.first, endPos.second + 1));
				}

		}
		else if (piece->GetType() == EPieceType::King)
		{
			// Move king to new position
			SetPiece(endPos, piece->GetRole(), piece->GetType());
			SetPieceToNullptr(startPos);
			// ---------------------------------

			// Check if any opponents piece is captured in our sandwich
			// Check opponent horizontally left
			if (endPos.second - 2 >= 1 &&
				m_board[endPos.first][endPos.second - 1] && m_board[endPos.first][endPos.second - 2] &&
				IsOpposite(m_board[endPos.first][endPos.second - 1], piece->GetRole(), { EPieceType::Warrior }) &&
				!IsOpposite(m_board[endPos.first][endPos.second - 2], piece->GetRole(), { EPieceType::Warrior }))
			{
				SetPieceToNullptr(Position(endPos.first, endPos.second - 1));
			}

			// Check opponent horizontally right
			if (endPos.second + 2 <= 11 &&
				m_board[endPos.first][endPos.second + 1] && m_board[endPos.first][endPos.second + 2] &&
				IsOpposite(m_board[endPos.first][endPos.second + 1], piece->GetRole(), { EPieceType::Warrior }) &&
				!IsOpposite(m_board[endPos.first][endPos.second + 2], piece->GetRole(), { EPieceType::Warrior }))
			{
				SetPieceToNullptr(Position(endPos.first, endPos.second + 1));
			}

			// Check opponent vertically up
			if (endPos.first - 2 >= 1 &&
				m_board[endPos.first - 1][endPos.second] && m_board[endPos.first - 2][endPos.second] &&
				IsOpposite(m_board[endPos.first - 1][endPos.second], piece->GetRole(), { EPieceType::Warrior }) &&
				!IsOpposite(m_board[endPos.first - 2][endPos.second], piece->GetRole(), { EPieceType::Warrior }))
			{
				SetPieceToNullptr(Position(endPos.first - 1, endPos.second));
			}

			// Check opponent vertically down
			if (endPos.first + 2 <= 11 &&
				m_board[endPos.first + 1][endPos.second] && m_board[endPos.first + 2][endPos.second] &&
				IsOpposite(m_board[endPos.first + 1][endPos.second], piece->GetRole(), { EPieceType::Warrior }) &&
				!IsOpposite(m_board[endPos.first + 2][endPos.second], piece->GetRole(), { EPieceType::Warrior }))
			{
				SetPieceToNullptr(Position(endPos.first + 1, endPos.second));
			}
			// ---------------------------------
		}

		return true;
	}
	return false;
}


bool Board::IsKingInCheck(Position startPos, Position endPos, EPieceRole pieceRole) const
{
	Position kingPos;

	// Search king position on board
	bool found = 0;
	for (int i = 1; i <= 11 && found == 0; i++)
	{
		for (int j = 1; j <= 11 && found == 0; j++)
		{
			if (m_board[i][j] && m_board[i][j]->Is(EPieceType::King, pieceRole))
			{
				kingPos.first = i;
				kingPos.second = j;
				found = 1;
			}
		}
	}

	// Check if king is in check - threatend by 3 attackers
	// down pos open - 3 pos closed
	if (kingPos.second - 1 >= 1 && kingPos.first - 1 >= 1 && kingPos.second + 1 <= 11)
	{
		if (m_board[kingPos.first][kingPos.second - 1]->Is(EPieceType::Warrior, EPieceRole::Attacker) &&
			m_board[kingPos.first - 1][kingPos.second]->Is(EPieceType::Warrior, EPieceRole::Attacker) &&
			m_board[kingPos.first][kingPos.second + 1]->Is(EPieceType::Warrior, EPieceRole::Attacker))
		{
			for (int i = kingPos.first + 2; i <= 11; i++)
			{
				if (m_board[i][kingPos.second]->Is(EPieceType::Warrior, EPieceRole::Attacker))
				{
					return true;
				}
				else if (m_board[i][kingPos.second]->Is(EPieceType::Warrior, EPieceRole::Defender))
				{
					return false;
				}
			}
		}
	}
	// left pos open - 3 pos closed
	if (kingPos.second - 1 >= 1 && kingPos.first + 1 >= 1 && kingPos.second + 1 <= 11)
	{
		if (m_board[kingPos.first - 1][kingPos.second]->Is(EPieceType::Warrior, EPieceRole::Attacker) &&
			m_board[kingPos.first][kingPos.second + 1]->Is(EPieceType::Warrior, EPieceRole::Attacker) &&
			m_board[kingPos.first + 1][kingPos.second]->Is(EPieceType::Warrior, EPieceRole::Attacker))
		{
			for (int i = kingPos.second - 2; i >= 1; i--)
			{
				if (m_board[kingPos.first][i]->Is(EPieceType::Warrior, EPieceRole::Attacker))
				{
					return true;
				}
				else if (m_board[kingPos.first][i]->Is(EPieceType::Warrior, EPieceRole::Defender))
				{
					return false;
				}
			}
		}
	}


}