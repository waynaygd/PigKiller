#pragma once
#include "character.h"
#include "pig.h"
#include <vector>

class CP_Player : public CP_CharacterBase {
public:

	CP_Player() : CP_CharacterBase("Valera", "Player", 50, 0, 25, 50, 500, 0 , 0, true) {
		Player_Balance = 50;
		Player_Turn = false;
		Player_CurrentLocation = 1;
	};

	void Player_AddToBalance(int Money);
	void Player_RemoveFromBalance(int Money);
	void Player_RemoveEXP(int REXP);
	void Player_AddToInventory(CP_ItemBase* Item);
	void NPC_AddToAvailable(CP_CharacterBase* Bot);

	void Player_ChangeBandUI();
	void Player_ChangeBand(int bot1, int bot2);
	void Player_UpgradeBotsUI();
	void Player_UpgradeBot(int bot1);
	void Player_ChangeWeaponUI();
	void Player_ChangeWeapon(int pc, int ic);

	std::string Player_GetInventoryItem(int Item_ID);
	CP_CharacterBase* Player_GetTeamBot(int Bot_ID);
	CP_CharacterBase* Player_GetAvailableBot(int Bot_ID);
	CP_ItemBase* Player_GetItemFINV(int Item_ID);
	
	int Player_GetBalance();
	int Player_GetInventorySize();
	int Player_GetPTSize();
	int Player_GetAvailableSize();
	int Player_GetCurrentLocation();
	bool Player_GetTurn();

	void Player_SetTurn(bool Player_NState);
	void Player_SetCurrentLocation(int Level_ID);

protected:
	bool Player_Turn;
	int Player_Balance;
	int Player_CurrentLocation;

	std::vector<CP_CharacterBase*> Player_Team = { new CP_PigDefault, new CP_PigDefault, new CP_PigDefault };
	std::vector<CP_CharacterBase*> Player_Available_NPC;
	std::vector<CP_ItemBase*> Player_Inventory;
};

