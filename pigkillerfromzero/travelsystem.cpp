#include <iostream>
#include <vector>
#include "travelsystem.h"
#include "shop.h"
#include "asciirenderer.h"
#include "consoleutils.h"

std::vector <CP_LevelBase*> Level = { new CP_LevelPigBase, new CP_LevelKabak, new CP_LevelShop, new CP_LevelBank, new CP_LevelWolfBase };
CP_Shop Shop;

void TravelSystem::TS_ShowAllLevels()
{
    GP_AsciiRenderer.RenderScene("travel_map");
    std::cout << "<- Pig Killer ->" << std::endl << std::endl;
    std::cout << "Your team level: " << P_Test() << std::endl;

    for (int i = 1; i < Level.size(); i++) {
        std::cout << i << ". " << Level[i]->Level_GetName() << " / ";
        if (Level[i]->Level_GetIsCompleted() == true) {
            std::cout << "Cleared";
            if (Level[i]->Level_GetName() == "Bazar") {
                std::cout << " / You can buy new items at the bazaar" << std::endl;
            }
            else {
                std::cout << "\n";
            }
        }
        if (Level[i]->Level_GetIsCompleted() == false) {
            std::cout << "Not cleared" << " / Required team level: " << Level[i]->Level_GetEXPtoTravel() << std::endl;;
        }

    }
    std::cout << "0. Go back" << std::endl;

    std::cout << std::endl;
}

void TravelSystem::TS_TravelToLevel(CP_Player& player, CP_LevelBase* level)
{
    player.Player_SetCurrentLocation(level->Level_GetID());
}

CP_LevelBase* TravelSystem::TS_GetLevel(int Level_ID)
{
    return Level[Level_ID];
}

void TravelSystem::TS_UITravel(CP_Player& player)
{
    int P_LevelChoosed;
    TS_ShowAllLevels();
    std::cout << "Choose a destination level: ";
    std::cin >> P_LevelChoosed;
    if (P_LevelChoosed == 0) {
        system("cls");
        P_BackToPigBase();
    }
    if (TS_CanPBTravel(player, Level[P_LevelChoosed]) == true) {
        if (Level[P_LevelChoosed - 1]->Level_GetIsCompleted() == false) {
            std::cout << "You need to clear this location first: " << Level[P_LevelChoosed - 1]->Level_GetName() << std::endl;
            CP_PauseForContinue();
            system("cls");
            TS_UITravel(player);
        }
        else {
            TS_TravelToLevel(player, Level[P_LevelChoosed]);
        }
    }
    if (TS_CanPBTravel(player, Level[P_LevelChoosed]) == false) {
        if (Level[P_LevelChoosed - 1]->Level_GetIsCompleted() == false) {
            std::cout << "You need to clear this location first: " << Level[P_LevelChoosed - 1]->Level_GetName() << std::endl;
            CP_PauseForContinue();
            system("cls");
            TS_UITravel(player);
        }
        else {
            std::cout << "We cannot travel there yet..." << std::endl;
            CP_PauseForContinue();
            system("cls");
            TS_UITravel(player);
        }
    }
    if (Level[P_LevelChoosed]->Level_GetIsCompleted() == true) {
        if (Level[P_LevelChoosed]->Level_GetName() == "Bazar") {
            Shop.Shop_Gameplay(player);
        }
        else {
            std::cout << "We already cleared this area of wolves..." << std::endl;
            CP_PauseForContinue();
            system("cls");
            TS_UITravel(player);
        }
    }
}

bool TravelSystem::TS_CanPBTravel(CP_Player& player, CP_LevelBase* level)
{
    int CP_PlayerTeamStrength = 0;
    
    for (int i = 0; i < player.Player_GetPTSize(); i++) {
        CP_PlayerTeamStrength += player.Player_GetTeamBot(i)->Character_GetLevel();
    }

    CP_PlayerTeamStrength = CP_PlayerTeamStrength / player.Player_GetPTSize();

    if (CP_PlayerTeamStrength >= level->Level_GetEXPtoTravel()) {
        return TS_ConfirmTravel = true;
    }
    else if (CP_PlayerTeamStrength < level->Level_GetEXPtoTravel()) {
        return TS_ConfirmTravel = false;
    }
}
