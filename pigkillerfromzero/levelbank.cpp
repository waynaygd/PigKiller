#include <iostream>
#include <vector>
#include <string>
#include "levelbank.h"
#include "consoleutils.h"

std::vector<std::string> DialogueStartBank = {
    "- Welcome to the acorn bank. Keep your winnings safe.",
    "- Paperwork first, jokes later.",
    "- Don't lose this place to wolves."
};

std::vector<std::string> DialogueAfterBank = {
    "- Your account is in good shape.",
    "- Earn more, spend wisely, and come back stronger."
};

void CP_LevelBank::Level_Gameplay()
{
	int vector_index = 0;
	while (vector_index != DialogueStartBank.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueStartBank[vector_index] << std::endl << std::endl;
		vector_index++;
		CP_PauseForContinue();
	}
}

void CP_LevelBank::Level_AfterGameplay()
{
	int vector_index = 0;
	while (vector_index != DialogueAfterBank.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueAfterBank[vector_index] << std::endl << std::endl;
		vector_index++;
		CP_PauseForContinue();
	}
}
