#include <iostream>
#include <vector>
#include <string>
#include "levelkabak.h"

std::vector <std::string> DialogueStartKabak = { "- Ну и он там выпендривался, я такой крутой, я такой сякой! И знаете что?" , "- Что?" ,
"- Он нажрался и уснул в бочке с пивом! Вот умора была с мужиками на утро, смотреть как он выбирался из неё", 
"Это был обычный день, Эрольд и его лучшие друзья сидели в баре и вспоминали рабочую неделю и ничего не предвещало беды...", 
"*Грохот, входная дверь разлетается в щепки от силы открытия*", 
"- Чертовы свиньи... Я вчера *указывает на случайного посетителя* твою мать съел, она была очень вкусная...",
"- Ну что ж, недорогие недрузья! Просим вас всех покинуть данное заведение! Сейчас здесь будет Волчий пир! И это приказ вашего короля! Повинуйтесь!",
"- Хуже коров могут быть только волки...", "- Эй! Животинка в серой шубке! Да, я тебе! Ты точно знаешь куда ты пришёл?",
"- Эрольд! Мой дорогой друг! Сколько лет прошло с нашей последней встречи! На самом деле я думал, что мы обойдемся без мечей, но видимо...",
"Рядовой игрок, сейчас вы окажетесь в бою. Так как это ваш первый бой, он не будет сложным, а вы сможете ознакомиться с базовым управлением"
};

std::vector <std::string> DialogueAfterKabak = { "- Фух, спасибо вам друзья! Чтобы мы без вас делали! Пиво за счёт заведения всем!"
};

void CP_LevelKabak::Level_Gameplay()
{
	int vector_index = 0;
	while (vector_index != DialogueStartKabak.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueStartKabak[vector_index] << std::endl << std::endl;
		vector_index++;
		system("pause");
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
		system("pause");
	}
}
