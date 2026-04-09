#pragma once
#include <string>

class CP_ItemBase {
public:
	// getr
	std::string Item_GetName();
	std::string Item_GetDescription();
	std::string Item_GetClass();
	int Item_GetID();
	int Item_GetCost();
	int Item_GetDMG();
	int Item_GetHealUP();

	CP_ItemBase() {
		Item_Name = "default";
		Item_Description = "default";
		Item_Class = "default";
		Item_ID = 0;
		Item_Cost = 0;
		Item_DMG = 0;
		Item_HealUP = 0;
	}

	CP_ItemBase(std::string I_NName, std::string I_ND, std::string I_NC, int I_NID, int I_C, int I_DMG, int I_HUP) {
		Item_Name = I_NName;
		Item_Description = I_ND;
		Item_Class = I_NC;
		Item_ID = I_NID;
		Item_Cost = I_C;
		Item_DMG = I_DMG;
		Item_HealUP = I_HUP;
	};

protected:
	// string
	std::string Item_Name;
	std::string Item_Description;
	std::string Item_Class;

	// int
	int Item_ID;
	int Item_Cost;
	int Item_DMG;
	int Item_HealUP;
};