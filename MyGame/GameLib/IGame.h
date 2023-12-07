#pragma once
#include <memory>

enum class EPlayer
{
	Attacker,
	Defender,
	None
};

using IGamePtr = std::shared_ptr<class IGame>;

class IGame
{

public:
	static IGamePtr Produce();

	virtual void Play() = 0;
	virtual EPlayer GetWinner() = 0;
	virtual bool IsGameOver() = 0;

	virtual ~IGame() = default;
};

