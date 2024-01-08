#include "GameRules.h"
#include <iostream>

GameRules* GameRules::instance = nullptr;

void GameRules::displayRules()
{
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
