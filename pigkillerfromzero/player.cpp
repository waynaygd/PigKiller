#include <iostream>
#include "player.h"
#include "menubasefunctions.h"
#include "asciirenderer.h"

void CP_Player::Player_AddToBalance(int Money)
{
	Player_Balance += Money;
}

void CP_Player::Player_RemoveFromBalance(int Money)
{
	Player_Balance -= Money;
}

void CP_Player::Player_RemoveEXP(int REXP)
{
	if (Character_EXP - REXP < 0) {
		Character_EXP = 0;
	}
	Character_EXP -= REXP;
}

void CP_Player::Player_AddToInventory(CP_ItemBase* Item)
{
	Player_Inventory.push_back(Item);
}

void CP_Player::NPC_AddToAvailable(CP_CharacterBase* Bot)
{
	Player_Available_NPC.push_back(Bot);
}

void CP_Player::Player_ChangeBandUI()
{
	int player_choice_bot1;
	int player_choice_bot2;

	GP_AsciiRenderer.RenderScene("upgrade_party_overview");
	std::cout << "<- Pig Killer ->" << std::endl << std::endl;
	for (int i = 0; i < Player_Team.size(); i++) {
	GP_AsciiRenderer.RenderScene("upgrade_party_overview");
		std::cout << i + 1 << ". " << Player_Team[i]->Character_GetName() << " / HP: " << Player_Team[i]->Character_GetHP() << " / Weapon: "  << Player_Team[i]->Character_GetItemFINV(0)->Item_GetName() << " with damage: " << Player_Team[i]->Character_GetItemFINV(0)->Item_GetDMG() << std::endl;
	}
	std::cout << "0. Cancel fighter selection" << std::endl << std::endl;
	std::cout << "Choose a fighter to re-equip: ";
	std::cin >> player_choice_bot1;

	if (player_choice_bot1 == 0) {
		system("pause");
		system("cls");
		P_BackToPigBase();
	}

	system("cls");
	std::cout << "<- Pig Killer ->" << std::endl << std::endl;

	for (int i = 0; i < Player_Available_NPC.size(); i++) {
		std::cout << i + 1 << ". " << Player_Available_NPC[i]->Character_GetName() << " / HP: " << Player_Available_NPC[i]->Character_GetHP() << " / Weapon: " << Player_Available_NPC[i]->Character_GetItemFINV(0)->Item_GetName() << " with damage: " << Player_Available_NPC[i]->Character_GetItemFINV(0)->Item_GetDMG() << std::endl;
	}

	std::cout << "Choose a fighter to add: ";
	std::cin >> player_choice_bot2;

	Player_ChangeBand(player_choice_bot1 - 1, player_choice_bot2 - 1);
	system("pause");
	system("cls");
	P_BackToPigBase();
}

void CP_Player::Player_ChangeBand(int bot1, int bot2)
{
	auto iter1 = Player_Team.cbegin();
	Player_Available_NPC.push_back(Player_Team[bot1]);
	Player_Team.erase(iter1 + bot1);
	auto iter2 = Player_Available_NPC.cbegin();
	Player_Team.push_back(Player_Available_NPC[bot2]);
	Player_Available_NPC.erase(iter2 + bot2);
}

void CP_Player::Player_UpgradeBotsUI()
{
	int player_choice;
	std::cout << "<- Pig Killer ->" << std::endl << std::endl;
	std::cout << "You can spend " << Character_GetEXP() << " experience points to upgrade characters" << std::endl << std::endl;
	for (int i = 0; i < Player_Team.size(); i++) {
		std::cout << i + 1 << ". " << Player_Team[i]->Character_GetName() << " / " << Player_Team[i]->Character_GetLevel() << " LVL ";
		if (Player_Team[i]->Character_GetLevel() != 5) {
			std::cout << "/ Need " << Player_Team[i]->Character_GetEXP() + 10 << " for the next level upgrade" << std::endl;
		}
		if (Player_Team[i]->Character_GetLevel() == 5) {
			std::cout << "/ Max level reached" << std::endl;
		}
	}
	std::cout << "0. Cancel upgrading fighters" << std::endl << std::endl;
	std::cout << "Choose a fighter to upgrade: ";
	std::cin >> player_choice;

	if (player_choice == 0) {
		system("pause");
		system("cls");
		P_BackToPigBase();
	}
	else {
		if (Character_GetEXP() >= Player_Team[player_choice - 1]->Character_GetEXP() + 10) {
			if (Player_Team[player_choice - 1]->Character_GetLevel() != 5) {
				Player_UpgradeBot(player_choice - 1);
				system("pause");
				system("cls");
				Player_UpgradeBotsUI();
			}
			else {
				std::cout << "Character is already at max level" << std::endl;
				system("pause");
				system("cls");
				Player_UpgradeBotsUI();
			}
		}
		if (Character_GetEXP() < Player_Team[player_choice - 1]->Character_GetEXP() + 10) {
			if (Player_Team[player_choice - 1]->Character_GetLevel() == 5) {
				std::cout << "Character is already at max level" << std::endl;
				system("pause");
				system("cls");
				Player_UpgradeBotsUI();
			}
			else {
	GP_AsciiRenderer.RenderScene("upgrade_party_overview");
				std::cout << "You do not have enough experience!" << std::endl;
				system("pause");
				system("cls");
				Player_UpgradeBotsUI();
			}
		}
	}
}

void CP_Player::Player_UpgradeBot(int bot1)
{
	Player_RemoveEXP(Player_Team[bot1]->Character_GetEXP() + 10);
	Player_Team[bot1]->Character_GainEXP(Player_Team[bot1]->Character_GetEXP() + 10);
	Player_Team[bot1]->Character_LevelUP();
}

void CP_Player::Player_ChangeWeaponUI()
{
	int player_choice;
	int item_choice;

	std::cout << "<- Pig Killer ->" << std::endl << std::endl;
	for (int i = 0; i < Player_Team.size(); i++) {
		std::cout << i + 1 << ". " << Player_Team[i]->Character_GetName() << " / " << Player_Team[i]->Character_GetItemFINV(0)->Item_GetName() << std::endl;
	}
	std::cout << "0. Cancel weapon change" << std::endl << std::endl;
	std::cout << "Choose a fighter to re-equip: ";
	std::cin >> player_choice;

	if (player_choice == 0) {
		system("pause");
		system("cls");
		P_BackToPigBase();
	}
	
	system("cls");
	if (Player_Inventory.size() != 0) {
		for (int i = 0; i < Player_Inventory.size(); i++) {
			std::cout << i + 1 << ". " << Player_Inventory[i]->Item_GetName() << " / " << Player_Inventory[i]->Item_GetClass() << " / " << Player_Inventory[i]->Item_GetDMG() << " damage per hit" << std::endl;
		}

		std::cout << "Choose a weapon to equip: ";
		std::cin >> item_choice;

		Player_ChangeWeapon(player_choice - 1, item_choice - 1);
		system("pause");
		system("cls");
		P_BackToPigBase();
	}

	if (Player_Inventory.size() == 0) {
		std::cout << "Your inventory is empty" << std::endl;
		system("pause");
		system("cls");
		P_BackToPigBase();
	}
}

void CP_Player::Player_ChangeWeapon(int pc, int ic)
{
	Player_Team[pc]->Character_AddWeapon(Player_Inventory[ic]);
	Player_Inventory.erase(Player_Inventory.cbegin() + ic);
	Player_Inventory.push_back(Player_Team[pc]->Character_GetItemFINV(1));
	Player_Team[pc]->Character_RemoveFromInventory(1);
}


std::string CP_Player::Player_GetInventoryItem(int Item_ID)
{
	return Player_Inventory[Item_ID]->Item_GetName();
}

CP_CharacterBase* CP_Player::Player_GetTeamBot(int Bot_ID)
{
	return Player_Team[Bot_ID];
}

CP_CharacterBase* CP_Player::Player_GetAvailableBot(int Bot_ID)
{
	return Player_Available_NPC[Bot_ID];
}

CP_ItemBase* CP_Player::Player_GetItemFINV(int Item_ID)
{
	return Player_Inventory[Item_ID];
}

int CP_Player::Player_GetBalance()
{
	return Player_Balance;
}

int CP_Player::Player_GetInventorySize()
{
	return Player_Inventory.size();
}

int CP_Player::Player_GetPTSize()
{
	return Player_Team.size();
}

int CP_Player::Player_GetAvailableSize()
{
	return Player_Available_NPC.size();
}

int CP_Player::Player_GetCurrentLocation()
{
	return Player_CurrentLocation;
}

bool CP_Player::Player_GetTurn()
{
	return Player_Turn;
}

void CP_Player::Player_SetTurn(bool Player_NState)
{
	Player_Turn = Player_NState;
}

void CP_Player::Player_SetCurrentLocation(int Level_ID)
{
	Player_CurrentLocation = Level_ID;
}
