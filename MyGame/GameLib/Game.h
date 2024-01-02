#pragma once
#include<iostream>
#include "Board.h"
#include "Player.h"
#include "IGame.h"

class PieceInfo : public IPieceInfo
{
public:
	PieceInfo(EPieceType type, EPieceRole Role);

	EPieceRole GetRole() const override;
	EPieceType GetType() const override;

private:
	EPieceType m_type;
	EPieceRole m_role;
};

class Game : public IGame
{

public:
	Game();

	Board GetBoard() const;


	void Play() override;
	EPlayer GetWinner() override;
	bool IsGameOver() override;

private:
	Board m_board;
	int m_turn;

};