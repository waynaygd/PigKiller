#include <iostream>
#include <vector>
#include <string>
#include "levelwolfbase.h"

std::vector <std::string> DialogueWolfBase = { "- Ну вот и пришло время для последней битвы, Волков!", "- Вы, малолетние доблесные бойцы! Вы ещё глупы, чтобы понять одну вещь...",
"- И какую же?", "- Что я вас отвлекаю! В АТАКУ ВОЛКИ!"
};

void CP_LevelWolfBase::Level_Gameplay()
{
	int vector_index = 0;
	while (vector_index != DialogueWolfBase.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueWolfBase[vector_index] << std::endl << std::endl;
		vector_index++;
		system("pause");
	}
}