#pragma once
#include <string>
#include <vector>
#include "item.h"

class CP_CharacterBase {
public:
	// getr
	std::string Character_GetName();
	std::string Character_GetDescription();
	int Character_GetHP();
	int Character_GetArmor();
	int Character_GetCHP();
	int Character_GetLevel();
	int Character_GetEXP();
	int Character_GetCHit();
	bool Character_GetIsAlive();

	// setr
	void Character_SetCHP(int Character_NHP);
	void Character_GainEXP(int Character_NEXP);
	void Character_LevelUP();
	void Character_SetIsAlive(bool Character_CState);

	// upgradestats
	void Character_UPGHP();
	void Character_UPGArmor();

	// other
	CP_ItemBase* Character_GetItemFINV(int Item_ID);
	void Character_AddToInventory(CP_ItemBase* Item);
	void Character_RemoveFromInventory(int Item_ID);
	void Character_AddWeapon(CP_ItemBase* Item);
	void Character_TakeDamage(int Weapon_Damage);

	CP_CharacterBase() {
		Character_Name = "default";
		Character_Description = "default";
		Character_HP = 0;
		Character_ChanceToHit = 0;
		Character_Armor = 0;
		Character_CHP = 0;
		Character_Level = 0;
		Character_MaxLevel = 0;
		Character_EXP = 0;
		Character_IsAlive = false;
	}

	CP_CharacterBase(std::string C_NName, std::string C_ND, int C_HP, int C_Hit, int C_Arm, int C_CHP, int C_LVL, int C_MLVL, int C_EXP, bool C_IA) {
		Character_Name = C_NName;
		Character_Description = C_ND;
		Character_HP = C_HP;
		Character_ChanceToHit = C_Hit;
		Character_Armor = C_Arm;
		Character_CHP = C_CHP;
		Character_Level = C_LVL;
		Character_MaxLevel = C_MLVL;
		Character_EXP = C_EXP;
		Character_IsAlive = C_IA;
	};

protected:
	// vector
	std::vector<CP_ItemBase*> Character_Inventory;

	// string
	std::string Character_Name;
	std::string Character_Description;

	// int
	int Character_HP;
	int Character_Armor;
	int Character_CHP;
	int Character_Level;
	int Character_EXP;
	int Character_ChanceToHit;

	int Character_MaxInventorySize = 5;
	int Character_MaxLevel;

	// bool
	bool Character_IsAlive;
};