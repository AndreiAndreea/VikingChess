#include <iostream>
#include <iomanip>
#include<conio.h>

#include "IGame.h"
#include "GameRules.h"
#include "ColorTheme.h"
#include "ColorThemeSelector.h"

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

static void PrintBoard(const IGamePtr& game, const ColorTheme& theme) {
	// ANSI color codes
	const std::string resetColor = "\033[0m";
	const std::string blackColor = "\033[30m";
	const std::string lightTextColor = "\033[37m"; // Light text color for 'white' pieces
	const std::string backgroundColorBorder = "\033[48;2;112;128;144m"; // Light cream background for the border

	const int cellWidth = 5; // Width of each cell (including spaces)
	int verticalIndex = 11;
	std::string horizontalIndex = "ABCDEFGHIJK";

	for (int i = 1; i <= 11; i++)
	{
		std::cout << backgroundColorBorder << blackColor << std::left << std::setw(cellWidth) << verticalIndex << resetColor;
		verticalIndex--;

		for (int j = 1; j <= 11; j++)
		{
			auto pieceInfo = game->GetPieceInfo(i, j);

			// Piece info or empty id there is nullptr
			std::string pieceStr = pieceInfo ? PieceToStr(pieceInfo) : "";

			// Determine the background color based on the square's position
			std::string bgColor = (i + j) % 2 == 0 ? theme.backgroundColor1 : theme.backgroundColor2;

			// Determine the text color based on the piece's color
			std::string textColor = pieceInfo && pieceInfo->GetRole() == EPieceRole::Attacker ? lightTextColor : blackColor;

			// Print the cell with colored background and centered piece
			std::cout << bgColor << textColor << std::left << std::setw(cellWidth) << pieceStr << resetColor;
		}
		std::cout << "\n";
	}
	std::cout << backgroundColorBorder << blackColor << std::left << std::setw(cellWidth) << " " << resetColor;
	for (int i = 0; i < 11; i++)
	{
		std::cout << backgroundColorBorder << blackColor << std::left << std::setw(cellWidth) << horizontalIndex[i] << resetColor;
	}
	std::cout << "\n";
}

int main()
{
	GameRules::getInstance()->displayRules(); // Call Singleton to display the rules
	IGamePtr game = IGame::Produce();
	ColorTheme theme = ColorThemeSelector::getInstance()->chooseTheme(); // Call Singleton class to choose the color theme
	PrintBoard(game, theme);
	game->Play();
	while (!game->IsGameOver())
	{
		std::string comand;
		std::cout << "Insert your move " << PlayerToStr(game->GetCurrentPlayer()) << ": ";
		std::string startPos, endPos;
		std::cin >> startPos >> endPos;
		std::cout << "\n";
		game->PlayerMove(startPos, endPos);
		system("cls");
		PrintBoard(game, theme);
		std::cout << "\n";
	}
	std::cout << "\n";
	game->Play();

	return 0;
}