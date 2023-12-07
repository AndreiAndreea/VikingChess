#include "Board.h"
#include <stdexcept>
#include<iostream>

Board::Board() {
    InitializeBoard();
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

    m_board[6][4] = std::make_shared<Warrior>(EPieceRole::Defender);
    m_board[6][5] = std::make_shared<Warrior>(EPieceRole::Defender);
    m_board[6][6] = std::make_shared<Warrior>(EPieceRole::Defender);

    m_board[7][5] = std::make_shared<Warrior>(EPieceRole::Defender);

    // Set up the king
    m_board[5][5] = std::make_shared<King>(EPieceRole::Defender);
}

bool Board::MakeMove(Position startPos, Position endPos)
{
    auto piece = m_board[startPos.first][startPos.second];
    //piece->canMove()
    return true;
}

BoardType Board::GetBoard() const
{
    return m_board;
}