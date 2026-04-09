#include <iostream>
#include <vector>
#include <string>
#include "levelkabak.h"
#include "consoleutils.h"

std::vector<std::string> DialogueStartKabak = {
    "- Hey! You look like village fighters. Looking for trouble?",
    "- Trouble found us first.",
    "- Wolves are pressing hard from the forest. They raid every night.",
    "- If you want to protect your base, prove it here and now.",
    "*The tavern door slams open as armed wolves rush inside.*",
    "- Hold your ground... and don't let them surround you!",
    "- If we win here, the village will believe in us again.",
    "- Then we fight. Right now.",
    "- Together! For the base!"
};

std::vector<std::string> DialogueAfterKabak = {
    "- Nice work, captain. The tavern is safe for now."
};

void CP_LevelKabak::Level_Gameplay()
{
	int vector_index = 0;
	while (vector_index != DialogueStartKabak.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueStartKabak[vector_index] << std::endl << std::endl;
		vector_index++;
		CP_PauseForContinue();
	}
}

void CP_LevelKabak::Level_AfterGameplay()
{
	int vector_index = 0;
	while (vector_index != DialogueAfterKabak.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueAfterKabak[vector_index] << std::endl << std::endl;
		vector_index++;
		CP_PauseForContinue();
	}
}
