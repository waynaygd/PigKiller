#pragma once
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include "wolf.h"
#include "allitems.h"

class CP_LevelBase {
public:
	// getr
	std::string Level_GetName();
	std::string Level_GetDescription();

	int Level_GetID();
	int Level_GetNPCCount();
	int Level_GetEXP();
	int Level_GetEXPtoTravel();
	int Level_GetWolfTeamSize();

	CP_CharacterBase* Level_GetTeamBot(int Bot_ID);

	bool Level_GetIsCompleted();
	bool Level_GetPlayer_Is_On_Location();

	// setr
	void Level_SetIsCompleted(bool Level_CState);
	void Level_SetPlayer_Is_On_Location(bool Level_CState);

	// other

	void Level_AddWolfToVector(CP_CharacterBase* CP_Wolf);
	void Level_GenerateWolfTeam(int L_NPC_Count);
	void Level_WolfTeamClear();
	virtual void Level_Gameplay();
	virtual void Level_AfterGameplay();

	CP_LevelBase() {
		Level_ID = -1;
		Level_EXP = 0;
		NPC_Count = 0;
		Level_Exp_To_Travel = 0;
		Level_Name = "default";
		Level_Description = "default";
		Level_IsCompleted = false;
		Player_Is_On_Location = false;
	}

	CP_LevelBase(int Level_NID, int Level_NEXP, int Level_NPCC, int Level_REXP, std::string Level_NName, std::string Level_ND, bool Level_NIC, bool Level_POL) {
		Level_ID = Level_NID;
		Level_EXP = Level_NEXP;
		NPC_Count = Level_NPCC;
		Level_Exp_To_Travel = Level_REXP;
		Level_Name = Level_NName;
		Level_Description = Level_ND;
		Level_IsCompleted = Level_NIC;
		Player_Is_On_Location = Level_POL;
	};

protected:
	// int
	int Level_ID;
	int NPC_Count;
	int Level_Exp_To_Travel;
	int Level_EXP;

	// string
	std::string Level_Name;
	std::string Level_Description;

	// bool
	bool Level_IsCompleted = false;
	bool Player_Is_On_Location = false;

	std::vector<CP_CharacterBase*> L_WolfTeam;
};