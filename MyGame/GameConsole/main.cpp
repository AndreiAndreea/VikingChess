#include <iostream>
#include <iomanip>
#include<conio.h>

#include "IGame.h"

struct ColorTheme {
	std::string backgroundColor1;
	std::string backgroundColor2;
};

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

static void DisplayGameRules() {
	std::string userResponse;
	std::cout << "Would you like to view the rules of Viking Chess (Hnefatafl)? (Yes/No): ";
	std::cin >> userResponse;

	if (userResponse == "Yes" || userResponse == "yes" || userResponse == "Y" || userResponse == "y") {
		std::cout << "Viking Chess Rules:\n";
		std::cout << "1. The game begins with 24 attackers, 12 defenders, and 1 king.\n";
		std::cout << "2. Attackers win by capturing the king; defenders win by moving the king to a corner.\n";
		std::cout << "3. Pieces move horizontally or vertically.\n";
		std::cout << "4. The king is captured when surrounded on four sides or when surrounded on three sides and against a border.\n";
		std::cout << "5. Warriors are captured when sandwiched between two enemy pieces.\n";
		std::cout << "6. Warriors can also be captured when sandwiched in a corner between two enemy pieces.\n";
		std::cout << "7. The king can also capture warriors between himself and another defender.\n";
		std::cout << "8. You can capture more than one piece at a time.\n";
		std::cout << "9. A piece cannot be intentionally moved in the middle of a sandwich.\n";
		std::cout << "10. A piece cannot be moved to a square occupied by another piece.\n";
		std::cout << "11. The king must be moved when he is threatened (the king is threatened when surrounded on three sides).\n";
	}
	else {
		std::cout << "You have chosen not to view the rules.\n";
	}
	std::cout << "\n";
}

static ColorTheme ChooseColorTheme() {
	char themeChoice;
	std::cout << "Choose a board color theme:\n";
	std::cout << "C - Classic\nW - Winter\nS - Spring\nU - Summer\nA - Autumn\n";
	std::cout << "Enter your choice: ";
	std::cin >> themeChoice;

	switch (themeChoice) {
	case 'C': // Classic
		return { "\033[48;2;205;133;63m", "\033[48;2;139;69;19m" };
	case 'W': // Winter
		return { "\033[48;2;128;0;128m", "\033[48;2;100;149;237m" };
	case 'S': // Spring
		return { "\033[48;2;255;20;147m", "\033[48;2;100;149;237m" };
	case 'U': // Summer
		return { "\033[48;2;204;119;34m", "\033[48;2;0;100;0m" };
	case 'A': // Autumn
		return { "\033[48;2;255;165;0m", "\033[48;2;139;0;0m" };
	default: // Default to classic theme
		return { "\033[48;2;205;133;63m", "\033[48;2;139;69;19m" };
	}
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

			//piece info or empty id there is nullptr
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
	DisplayGameRules();
	IGamePtr game = IGame::Produce();
	ColorTheme theme = ChooseColorTheme();
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