#include <iostream>
#include <vector>
#include "travelsystem.h"
#include "shop.h"

std::vector <CP_LevelBase*> Level = { new CP_LevelPigBase, new CP_LevelKabak, new CP_LevelShop, new CP_LevelBank, new CP_LevelWolfBase };
CP_Shop Shop;

void TravelSystem::TS_ShowAllLevels()
{
    std::cout << "<- Pig Killer ->" << std::endl << std::endl;
    std::cout << "Уровень вашей команды: " << P_Test() << std::endl;

    for (int i = 1; i < Level.size(); i++) {
        std::cout << i << ". " << Level[i]->Level_GetName() << " / ";
        if (Level[i]->Level_GetIsCompleted() == true) {
            std::cout << "Зачищен";
            if (Level[i]->Level_GetName() == "Bazar") {
                std::cout << " / Можно прикупить новых предметов на базаре" << std::endl;
            }
            else {
                std::cout << "\n";
            }
        }
        if (Level[i]->Level_GetIsCompleted() == false) {
            std::cout << "Не зачищен" << " / Необходимый общий уровень команды: " << Level[i]->Level_GetEXPtoTravel() << std::endl;;
        }

    }
    std::cout << "0. Вернуться обратно" << std::endl;

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
    std::cout << "Выберите уровень, куда вы хотите переместиться: ";
    std::cin >> P_LevelChoosed;
    if (P_LevelChoosed == 0) {
        system("cls");
        P_BackToPigBase();
    }
    if (TS_CanPBTravel(player, Level[P_LevelChoosed]) == true) {
        if (Level[P_LevelChoosed - 1]->Level_GetIsCompleted() == false) {
            std::cout << "Нужно прежде зачистить локацию " << Level[P_LevelChoosed - 1]->Level_GetName() << std::endl;
            system("pause");
            system("cls");
            TS_UITravel(player);
        }
        else {
            TS_TravelToLevel(player, Level[P_LevelChoosed]);
        }
    }
    if (TS_CanPBTravel(player, Level[P_LevelChoosed]) == false) {
        if (Level[P_LevelChoosed - 1]->Level_GetIsCompleted() == false) {
            std::cout << "Нужно прежде зачистить локацию " << Level[P_LevelChoosed - 1]->Level_GetName() << std::endl;
            system("pause");
            system("cls");
            TS_UITravel(player);
        }
        else {
            std::cout << "Мы пока не можем туда отправиться..." << std::endl;
            system("pause");
            system("cls");
            TS_UITravel(player);
        }
    }
    if (Level[P_LevelChoosed]->Level_GetIsCompleted() == true) {
        if (Level[P_LevelChoosed]->Level_GetName() == "Bazar") {
            Shop.Shop_Gameplay(player);
        }
        else {
            std::cout << "Мы уже зачистили эту местность от волков..." << std::endl;
            system("pause");
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
