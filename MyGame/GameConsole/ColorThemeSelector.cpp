#include "ColorThemeSelector.h"
#include <iostream>

ColorThemeSelector* ColorThemeSelector::instance = nullptr;

ColorTheme ColorThemeSelector::chooseTheme()
{
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
