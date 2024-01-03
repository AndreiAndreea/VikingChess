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
    for (int i = 1; i <= 10; i++)
    {
        m_board[i].resize(11);
    }

    for (int x = 1; x <= 10; x++)
        for (int y = 1; y <= 10; y++)
            m_board[x][y] = nullptr;
}

Board::Board(const Board& ob)
{
    m_board = ob.GetBoard();
}

//indexarea de la 0 la 10
void Board::InitializeBoard() {
    m_board.resize(11);
    for (int i = 0; i < 11; i++) {
        m_board[i].resize(11);
    }

    // Initialize empty squares
    for (int x = 0; x < 11; x++) {
        for (int y = 0; y < 11; y++) {
            m_board[x][y] = nullptr;
        }
    }

    // Set up attackers (black pieces)
//N
    m_board[0][3] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[0][4] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[0][5] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[0][6] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[0][7] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[1][5] = std::make_shared<Warrior>(EPieceRole::Attacker);
    //V
    m_board[3][0] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[4][0] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[5][0] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[6][0] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[7][0] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[5][1] = std::make_shared<Warrior>(EPieceRole::Attacker);
    //E
    m_board[3][10] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[4][10] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[5][10] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[6][10] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[7][10] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[5][9] = std::make_shared<Warrior>(EPieceRole::Attacker);
    //S
    m_board[10][3] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[10][4] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[10][5] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[10][6] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[10][7] = std::make_shared<Warrior>(EPieceRole::Attacker);
    m_board[9][5] = std::make_shared<Warrior>(EPieceRole::Attacker);


    // Set up defenders (white pieces)
    m_board[3][5] = std::make_shared<Warrior>(EPieceRole::Defender);

    m_board[4][4] = std::make_shared<Warrior>(EPieceRole::Defender);
    m_board[4][5] = std::make_shared<Warrior>(EPieceRole::Defender);
    m_board[4][6] = std::make_shared<Warrior>(EPieceRole::Defender);

    m_board[5][3] = std::make_shared<Warrior>(EPieceRole::Defender);
    m_board[5][4] = std::make_shared<Warrior>(EPieceRole::Defender);
    m_board[5][5] = std::make_shared<Warrior>(EPieceRole::Defender);
    m_board[5][6] = std::make_shared<Warrior>(EPieceRole::Defender);
    m_board[5][7] = std::make_shared<Warrior>(EPieceRole::Defender);

    m_board[6][4] = std::make_shared<Warrior>(EPieceRole::Defender);
    m_board[6][5] = std::make_shared<Warrior>(EPieceRole::Defender);
    m_board[6][6] = std::make_shared<Warrior>(EPieceRole::Defender);

    m_board[7][5] = std::make_shared<Warrior>(EPieceRole::Defender);

    // Set up the king
    m_board[5][5] = std::make_shared<King>(EPieceRole::Defender);
}

PieceMatrix Board::GetBoard() const
{
    return m_board;
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
    if (!piece)
        return false;
    if(piece->IsOpposite(role, types))
		return true;

    return false;
}


bool Board::MakeMove(Position startPos, Position endPos)
{
    auto piece = m_board[startPos.first][startPos.second];
    //piece->canMove()
    return true;
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
                else if(m_board[i][kingPos.second]->Is(EPieceType::Warrior, EPieceRole::Defender))
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
