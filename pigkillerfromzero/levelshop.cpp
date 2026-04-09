#include <iostream>
#include <vector>
#include <string>
#include "levelshop.h"

std::vector <std::string> DialogueStartShop = { "- Эй, Серый, пробовал эти яблоки?", "- Какие яблоки? Нам надо найти главу рынка, а ты все про какие-то яблоки...", "...",
"- Ну и зря", "...", "- У рынка свины! Срочно на оборону!"
};

std::vector <std::string> DialogueAfterShop = {"- Ну ребят, может договоримся не знаю... Вон, яблоки! Я попробовал, очень вкусные!", "...",
"- Он реально настолько дурной?", "- Да, не понятно почему Волков его вообще с нами послал...", "- *ест яблоко*", "- Ну, с кем не бывает", "*звук протыкания мечом туловища*",
"...", "- Ой, родненькие! Что ж я без вас бы делал!", "- Да не за что, дядь Свин, вон, покупатели уже пришли, мы ваш рынок теперь под защитой держать будем, можете спокойно торговать",
"- Ох, ой! Не знаю даже как отблагодарить вас, можете теперь ко мне приходить, покупать всё что нужно, примем как родных!"
};

void CP_LevelShop::Level_Gameplay()
{
	int vector_index = 0;
	while (vector_index != DialogueStartShop.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueStartShop[vector_index] << std::endl << std::endl;
		vector_index++;
		system("pause");
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
		system("pause");
	}
}