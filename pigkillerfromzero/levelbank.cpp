#include <iostream>
#include <vector>
#include <string>
#include "levelbank.h"

std::vector <std::string> DialogueStartBank = { "- Ты мне свою туфту не неси! У нас в Волковске такую низкую ставку на 10 лет никто не предлагает! НА-ДУ-ВА-ТЕЛЬ-СТВО",
"*звук пробития стекла и последовательного тыкания острым предметом в тело*", "- Свины на подходе, всем быть готовым!"
};

std::vector <std::string> DialogueAfterBank = { "- Здравствуйте, я консультант СвинБанка Валерий, хочу узнать номер вашего счёта и секретный пароль, чтобы отдать все деньги вашим детям после вашей кончины, которая наступит...",
"...", "- Прямо сейчас!", "*звук убийства волка*", "- Спасибо, что воспользовались услугами СвинБанка, не будем ждать вас ещё!"
};

void CP_LevelBank::Level_Gameplay()
{
	int vector_index = 0;
	while (vector_index != DialogueStartBank.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueStartBank[vector_index] << std::endl << std::endl;
		vector_index++;
		system("pause");
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
		system("pause");
	}
}
