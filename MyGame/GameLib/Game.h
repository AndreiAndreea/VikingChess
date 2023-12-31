#pragma once
//#include<iostream>

#include "IGame.h"
#include "Board.h"
#include "Player.h"
#include "EGameState.h"


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

	//methods from interface IGame
	void Play() override;

	void PlayerMove(const std::string& startPos, const std::string& endPos) override;

	EPlayer GetWinner() const override;
	EPlayer GetCurrentPlayer() const override;
	bool IsGameOver() const override;
	bool IsStatePlaying() const override;

	IPieceInfoPtr GetPieceInfo(int i, int j) const override;

	bool MakeMove(const std::string& startPosStr, const std::string& endPosStr) override;


private:
	Position ConvertToPos(const std::string& pos);
	bool IsInputValid(const Position& startPos, const Position& endPos);
	bool IsState(EGameState state) const;
	void UpdateState(EGameState state);

private:
	Board m_board;
	int m_turn;
	EGameState m_state;
};