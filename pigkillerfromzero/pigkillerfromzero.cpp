#include <iostream>
#include <vector>

#include <windows.h>
#include <shellapi.h>
#include "menubasefunctions.h"
#include "fightsystem.h"

CP_Player Player;
FightSystem GP_Fight;
TravelSystem GP_Travel;

int user_menuchoice;

void mainmenu() {
	std::cout << "<- Pig Killer ->" << std::endl << std::endl;

	std::cout << "- 1. Начать игру - \n";
	std::cout << "- 2. Смешная кнопка - \n";
	std::cout << "- 3. Tитры - \n";
	std::cout << "- 4. Выход - \n \n";

	std::cout << "- Выберите опцию: ";
	std::cin >> user_menuchoice;
	menuaction(user_menuchoice);
}

void GP_PigBase() {
	int player_action;

	std::cout << "<- Pig Killer ->" << std::endl << std::endl;
	std::cout << "- 1. Отправиться на битву - \n";
	std::cout << "- 2. Поменять члена команды - \n";
	std::cout << "- 3. Прокачать членов команды - \n";
	std::cout << "- 4. Сменить оружие себе или членам команды - \n\n";

	std::cout << "- Выберите опцию: ";
	std::cin >> player_action;

	switch (player_action) {
	case 1:
		system("cls");
		GP_Travel.TS_UITravel(Player);
		system("pause");
		GP_Travel.TS_GetLevel(Player.Player_GetCurrentLocation())->Level_Gameplay();
		GP_Fight.FS_StartFight(Player, GP_Travel.TS_GetLevel(Player.Player_GetCurrentLocation()));
		break;
	case 2:
		system("cls");
		Player.Player_ChangeBandUI();
		break;
	case 3:
		system("cls");
		Player.Player_UpgradeBotsUI();
		break;
	case 4:
		system("cls");
		Player.Player_ChangeWeaponUI();
		break;
	default:
		exit(true);
		break;
	}
}

int P_Test() {
	int CP_PlayerTeamStrength = 0;

	for (int i = 0; i < Player.Player_GetPTSize(); i++) {
		CP_PlayerTeamStrength += Player.Player_GetTeamBot(i)->Character_GetLevel();
	}

	CP_PlayerTeamStrength = CP_PlayerTeamStrength / Player.Player_GetPTSize();

	return CP_PlayerTeamStrength;
}

void P_BackToPigBase() {
	system("cls");
	GP_Travel.TS_TravelToLevel(Player, GP_Travel.TS_GetLevel(0));
	GP_Travel.TS_GetLevel(Player.Player_GetCurrentLocation())->Level_Gameplay();
}

void P_GameEnding() {
	std::vector <std::string> DialogueEnd = { "Волчий король пал!", "Главный свин и его отважная банда стала героями не только деревни, но близ лежащих городов!",
		"Свиной король лично приехал в деревню, чтобы поблагодарить главу за его отвагу и честь", "С тех пор жили они долго и счастливо..."
	};

	int vector_index = 0;
	while (vector_index != DialogueEnd.size()) {	
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueEnd[vector_index] << std::endl << std::endl;
		vector_index++;
		system("pause");
	}
	exit(true);
}

void P_GameEndingBegin() {
	std::vector <std::string> DialogueBegin = { "Банда не справилась с натиском в кабаке...", "О какой защите деревни может быть и речь?",
	"Волчий король отдал приказ нападения на вашу базу, свины пытались отбиться, но ничего не вышло...", "Вы предали нас всех."
	};

	int vector_index = 0;
	while (vector_index != DialogueBegin.size()) {
		system("cls");
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << DialogueBegin[vector_index] << std::endl << std::endl;
		vector_index++;
		system("pause");
	}
	exit(true);
}

void game() {
	int massive_id[5];

	for (int i = 0; i < Player.Player_GetPTSize(); i++)
	{
		std::random_device rd;
		std::uniform_int_distribution<int> dist(1, 3);

		int newRanomValue = dist(rd);

		massive_id[i] = newRanomValue;
	}

	for (int i = 0; i < Player.Player_GetPTSize(); i++) {
		if (massive_id[i] == 1) {
			Player.Player_GetTeamBot(i)->Character_AddToInventory(new CP_ItemSword);
		}
		if (massive_id[i] == 2) {
			Player.Player_GetTeamBot(i)->Character_AddToInventory(new CP_ItemBulava);
		}
		if (massive_id[i] == 3) {
			Player.Player_GetTeamBot(i)->Character_AddToInventory(new CP_ItemSekira);
		}
	}
	GP_Travel.TS_TravelToLevel(Player, GP_Travel.TS_GetLevel(1));
	GP_Travel.TS_GetLevel(Player.Player_GetCurrentLocation())->Level_Gameplay();
	GP_Fight.FS_StartFight(Player, GP_Travel.TS_GetLevel(Player.Player_GetCurrentLocation())); 
}

void menuaction(int user_menuchoice) {
	system("cls");
	std::cout << "<- Pig Killer ->" << std::endl << std::endl;

	int user_choice;

	switch (user_menuchoice) {
	case 1:
		game();
		break;
	case 2:
		system("cls");
		ShellExecute(0, 0, L"https://clck.ru/3AwQ5r", 0, 0, SW_SHOW); 
		exit(true);
	case 3:
		std::cout << "<- Pig Killer ->" << std::endl << std::endl;
		std::cout << "Автор кода, нарратива и геймдизайна: Тимофей Журавлев" << std::endl;
		system("pause");
		backtomainmenu();
		break;
	case 4:
		exit(true);
	default:
		exit(true);
	}
}

void backtomainmenu()
{
	system("cls");
	mainmenu();
}

int main() {
	setlocale(LC_ALL, "Russian");
	mainmenu();

	return 0;
}