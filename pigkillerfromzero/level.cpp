#include "level.h"

std::string CP_LevelBase::Level_GetName()
{
    return Level_Name;
}

std::string CP_LevelBase::Level_GetDescription()
{
    return Level_Description;
}

int CP_LevelBase::Level_GetID()
{
    return Level_ID;
}

int CP_LevelBase::Level_GetNPCCount()
{
    return NPC_Count;
}

int CP_LevelBase::Level_GetEXP()
{
    return Level_EXP;
}

int CP_LevelBase::Level_GetEXPtoTravel()
{
    return Level_Exp_To_Travel;
}

int CP_LevelBase::Level_GetWolfTeamSize()
{
    return L_WolfTeam.size();
}

CP_CharacterBase* CP_LevelBase::Level_GetTeamBot(int Bot_ID)
{
    return L_WolfTeam[Bot_ID];
}

bool CP_LevelBase::Level_GetIsCompleted()
{
    return Level_IsCompleted;
}

bool CP_LevelBase::Level_GetPlayer_Is_On_Location()
{
    return Player_Is_On_Location;
}

void CP_LevelBase::Level_SetIsCompleted(bool Level_CState)
{
    Level_IsCompleted = Level_CState;
}

void CP_LevelBase::Level_SetPlayer_Is_On_Location(bool Level_CState)
{
    Player_Is_On_Location = Level_CState;
}

void CP_LevelBase::Level_AddWolfToVector(CP_CharacterBase* CP_Wolf)
{
    L_WolfTeam.push_back(CP_Wolf);
}

void CP_LevelBase::Level_GenerateWolfTeam(int L_NPC_Count)
{
    int massive_id[5];

    for (int i = 0; i < L_NPC_Count; i++)
    {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 2);

        int newRanomValue = dist(rd);

        massive_id[i] = newRanomValue;
    }

    while (Level_GetWolfTeamSize() != L_NPC_Count) {
        for (int i = 0; i < L_NPC_Count; i++) {
            if (massive_id[i] == 0) {
                Level_AddWolfToVector(new CP_WolfDefault);
            }
            else if (massive_id[i] == 1) {
                Level_AddWolfToVector(new CP_WolfPro);
            }
            else if (massive_id[i] == 2) {
                Level_AddWolfToVector(new CP_WolfMPro);
            }
        }
    }

    for (int i = 0; i < Level_GetWolfTeamSize(); i++) {
        if (Level_GetTeamBot(i)->Character_GetName() == "Default Wolf") {
            Level_GetTeamBot(i)->Character_AddToInventory(new CP_ItemSword);
        }
        if (Level_GetTeamBot(i)->Character_GetName() == "Pro Wolf") {
            Level_GetTeamBot(i)->Character_AddToInventory(new CP_ItemAxe);
        }
        if (Level_GetTeamBot(i)->Character_GetName() == "Mega Pro Wolf") {
            Level_GetTeamBot(i)->Character_AddToInventory(new CP_ItemKatana);
        }
    }
}

void CP_LevelBase::Level_WolfTeamClear()
{
    L_WolfTeam.clear();
}

void CP_LevelBase::Level_Gameplay()
{
}

void CP_LevelBase::Level_AfterGameplay()
{
}

