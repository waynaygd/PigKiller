#include <iostream>
#include <vector>
#include <string>
#include "levelwolfbase.h"
#include "consoleutils.h"

std::vector<std::string> DialogueWolfBase = {
    "- So, you finally reached the Wolf Base.",
    "- Turn back now, or be torn apart.",
    "- We are done running.",
    "- Then come and face the Wolf King!"
};

void CP_LevelWolfBase::Level_Gameplay()
{
	int vector_index = 0;
	while (vector_index != DialogueWolfBase.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueWolfBase[vector_index] << std::endl << std::endl;
		vector_index++;
		CP_PauseForContinue();
	}
}
