#include<iostream>
#include <iomanip>

#include "IGame.h"

std::string PieceToStr(IPieceInfoPtr pieceInfo)
{
	std::string result;

	switch (pieceInfo->GetType())
	{
	case EPieceType::King:
		result = "  K";
		break;
	case EPieceType::Warrior:
		result = "  W";
		break;
	}
	return result;
}

std::string PlayerToStr(EPlayer player)
{
	if (player == EPlayer::Attacker)
		return "PlayerAttacker";
	else
		if (player == EPlayer::Defender)
			return "PlayerDefender";
	return "None";
}

void PrintBoard(const IGamePtr& game) {
	// ANSI color 
	const std::string resetColor = "\033[0m";
	const std::string blackColor = "\033[30m";
	const std::string lightTextColor = "\033[37m"; // Lighter text color for white pieces
	const std::string backgroundColor1 = "\033[48;2;205;133;63m"; // Lighter brown background for the light squares (RGB: 205, 133, 63)
	const std::string backgroundColor2 = "\033[48;2;139;69;19m"; // Darker brown background for the dark squares (RGB: 139, 69, 19)

	const int cellWidth = 5; // Width of each cell (including spaces)

	for (int i = 1; i <= 11; i++)
	{
		for (int j = 1; j <= 11; j++)
		{
			auto pieceInfo = game->GetPieceInfo(i, j);

			//piece info or empty id there is nullptr
			std::string pieceStr = pieceInfo ? PieceToStr(pieceInfo) : "";

			// Determine the background color based on the square's position
			std::string bgColor = (i + j) % 2 == 0 ? backgroundColor1 : backgroundColor2;

			// Determine the text color based on the piece's color
			std::string textColor = pieceInfo && pieceInfo->GetRole() == EPieceRole::Attacker ? lightTextColor : blackColor;

			// Print the cell with colored background and centered piece
			std::cout << bgColor << textColor << std::left << std::setw(cellWidth) << pieceStr << resetColor;
		}
		std::cout << "\n";
	}
}

int main()
{
	IGamePtr game = IGame::Produce();
	PrintBoard(game);
	std::cout << "\n";
	while (game->IsGameOver() == false)
	{
		std::string startPos, endPos;
		std::cout << "Insert your move " << PlayerToStr(game->GetCurrentPlayer()) << ": ";
		std::cin >> startPos; std::cin >> endPos;
		std::cout << "\n";
		while (!game->MakeMove(startPos, endPos))
		{
			std::cout << "Invalid Move\n";
			std::cout << "Insert your move " << PlayerToStr(game->GetCurrentPlayer()) << ": ";
			std::cin >> startPos; std::cin >> endPos;
			std::cout << "\n";
		}
		PrintBoard(game);
		std::cout << "\n";
	}

	std::cout << "Winner is: " << PlayerToStr(game->GetWinner()) << " !!!";

	return 0;
}