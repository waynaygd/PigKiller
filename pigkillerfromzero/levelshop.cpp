#include <iostream>
#include <vector>
#include <string>
#include "levelshop.h"
#include "consoleutils.h"

std::vector<std::string> DialogueStartShop = {
    "- Welcome to the market district.",
    "- Supplies are scarce, prices are not friendly.",
    "- Still, good steel wins fights."
};

std::vector<std::string> DialogueAfterShop = {
    "- Smart buying keeps the team alive.",
    "- Come back any time you need better gear."
};

void CP_LevelShop::Level_Gameplay()
{
	int vector_index = 0;
	while (vector_index != DialogueStartShop.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueStartShop[vector_index] << std::endl << std::endl;
		vector_index++;
		CP_PauseForContinue();
	}
}

void CP_LevelShop::Level_AfterGameplay()
{
	int vector_index = 0;
	while (vector_index != DialogueAfterShop.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueAfterShop[vector_index] << std::endl << std::endl;
		vector_index++;
		CP_PauseForContinue();
	}
}
