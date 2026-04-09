#include <iostream>
#include <random>
#include <ctime>
#include "menubasefunctions.h"
#include "fightsystem.h"
#include "asciirenderer.h"

const int SIZE = 2;
int toattack[SIZE];

const int money = 1;
int coins[money];

const int ddsize = 1;
int DD[ddsize];

const int hitsize = 1;
int hitc[hitsize];

const int psize = 2;
int pigc[psize];

const int wpsize = 2;
int weapc[wpsize];

void CP_RanGenBotToAttack() {

    for (int i = 0; i < SIZE; )
    {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 2);

        int newRanomValue = dist(rd);

        toattack[i] = newRanomValue;
        i++;

    }
}

void CP_RanGenDDChance() {
    srand(time(NULL));

    bool alreadyThere;

    for (int i = 0; i < ddsize; )
    {
        alreadyThere = false;
        int newRanomValue = rand() % 100;

        for (int j = 0; j < i; j++)
        {
            if (DD[j] == newRanomValue)
            {
                alreadyThere = true;
                break;
            }
        }

        if (!alreadyThere)
        {
            DD[i] = newRanomValue;
            i++;
        }

    }
}

void CP_RanGenPigBotChance() {
    srand(time(NULL));

    bool alreadyThere;

    for (int i = 0; i < psize; )
    {
        alreadyThere = false;
        int newRanomValue = rand() % 2;

        for (int j = 0; j < i; j++)
        {
            if (pigc[j] == newRanomValue)
            {
                alreadyThere = true;
                break;
            }
        }

        if (!alreadyThere)
        {
            pigc[i] = newRanomValue;
            i++;
        }

    }
}

void CP_RanGenWeaponChance() {
    srand(time(NULL));

    bool alreadyThere;

    for (int i = 0; i < wpsize; )
    {
        alreadyThere = false;
        int newRanomValue = rand() % 6;

        for (int j = 0; j < i; j++)
        {
            if (weapc[j] == newRanomValue)
            {
                alreadyThere = true;
                break;
            }
        }

        if (!alreadyThere)
        {
            weapc[i] = newRanomValue;
            i++;
        }

    }
}

void CP_RanGenHitChance() {
    srand(time(NULL));

    bool alreadyThere;

    for (int i = 0; i < hitsize; )
    {
        alreadyThere = false;
        int newRanomValue = rand() % 100;

        for (int j = 0; j < i; j++)
        {
            if (hitc[j] == newRanomValue)
            {
                alreadyThere = true;
                break;
            }
        }

        if (!alreadyThere)
        {
            hitc[i] = newRanomValue;
            i++;
        }

    }
}

void CP_RanGenMoney() {
    srand(time(NULL));

    bool alreadyThere;

    for (int i = 0; i < money; )
    {
        alreadyThere = false;
        int newRanomValue = rand() % 50;

        for (int j = 0; j < i; j++)
        {
            if (coins[j] == newRanomValue)
            {
                alreadyThere = true;
                break;
            }
        }

        if (!alreadyThere)
        {
            coins[i] = newRanomValue;
            i++;
        }

    }
}

void FightSystem::FS_StartFight(CP_Player& player, CP_LevelBase* level)
{
    FS_PlayerTeamWin = false;
    FS_BotTeamWin = false;

    if (player.Player_GetPTSize() == 0) {
        system("cls");
        std::cout << "<- Pig Killer ->" << std::endl << std::endl;
        std::cout << "Pick your fighters first!" << std::endl << std::endl;
        system("pause");
        P_BackToPigBase();
    }
    else {
        level->Level_GenerateWolfTeam(level->Level_GetNPCCount());
        player.Player_SetTurn(true);

        if (level->Level_GetID() == 3) {
            for (int i = 0; i < level->Level_GetWolfTeamSize(); i++) {
                level->Level_GetTeamBot(i)->Character_LevelUP();
            }
        }

        if (level->Level_GetID() == 4) {
            for (int i = 0; i < level->Level_GetWolfTeamSize(); i++) {
                level->Level_GetTeamBot(i)->Character_LevelUP();
                level->Level_GetTeamBot(i)->Character_LevelUP();
            }
        }

        FS_FightUI(player, level);

        system("pause");
    }
}

void FightSystem::FS_AttackByPig(CP_Player& player, CP_LevelBase* level, int CP_PigC, int CP_WolfC, int type_dmg)
{
    if (level->Level_GetTeamBot(CP_WolfC)->Character_GetIsAlive() == true) {
        if (type_dmg == 1) {
            level->Level_GetTeamBot(CP_WolfC)->Character_TakeDamage(player.Player_GetTeamBot(CP_PigC)->Character_GetItemFINV(0)->Item_GetDMG());
        }
        if (type_dmg == 2) {
            level->Level_GetTeamBot(CP_WolfC)->Character_TakeDamage(player.Player_GetTeamBot(CP_PigC)->Character_GetItemFINV(0)->Item_GetDMG() * 2);
        }
    }
    else if (level->Level_GetTeamBot(CP_WolfC)->Character_GetIsAlive() == false) {
        std::cout << level->Level_GetTeamBot(CP_WolfC)->Character_GetName() << " is dead!" << std::endl;
        FS_FightUI(player, level);
    }
}

void FightSystem::FS_AttackByWolf(CP_Player& player, CP_LevelBase* level, int CP_PigC, int CP_WolfC)
{
    int chance_to_hit = level->Level_GetTeamBot(CP_WolfC)->Character_GetCHit();
    CP_RanGenHitChance();
    if (hitc[0] < chance_to_hit) {
        if (player.Player_GetTeamBot(CP_WolfC)->Character_GetIsAlive() == true) {
            player.Player_GetTeamBot(CP_WolfC)->Character_TakeDamage(0);
        }
    }
    else if (hitc[0] >= chance_to_hit) {
        if (player.Player_GetTeamBot(CP_WolfC)->Character_GetIsAlive() == true) {
            player.Player_GetTeamBot(CP_WolfC)->Character_TakeDamage(level->Level_GetTeamBot(CP_PigC)->Character_GetItemFINV(0)->Item_GetDMG());
        }
    }
}

void FightSystem::FS_PlayerAttacks(CP_Player& player, CP_LevelBase* level, int CP_PigC, int CP_WolfC) {
    int UserAction;

    std::cout << "Your pig: " << player.Player_GetTeamBot(CP_PigC)->Character_GetName() << std::endl << std::endl;

    std::cout << "Enemy wolf: " << level->Level_GetTeamBot(CP_WolfC)->Character_GetName() << std::endl << std::endl;

    std::cout << "1. Attack" << std::endl;
    std::cout << "2. Double damage attack (chance: " << player.Player_GetTeamBot(CP_PigC)->Character_GetLevel() * 5 << "%)" << std::endl << std::endl;

    std::cout << "Choose an action: ";
    std::cin >> UserAction;
    std::cout << std::endl;

    if (UserAction == 1 and level->Level_GetTeamBot(CP_WolfC)->Character_GetIsAlive() == true) {
        FS_AttackByPig(player, level, CP_PigC, CP_WolfC, UserAction);
        std::cout << "You dealt " << player.Player_GetTeamBot(CP_PigC)->Character_GetItemFINV(0)->Item_GetDMG() << "!" << std::endl;

        std::cout << level->Level_GetTeamBot(CP_WolfC)->Character_GetName() << " now has " << level->Level_GetTeamBot(CP_WolfC)->Character_GetCHP() << " health points." << std::endl << std::endl;
        system("pause");
        player.Player_SetTurn(false);
        FS_FightUI(player, level);
    }
    if (UserAction == 2 and level->Level_GetTeamBot(CP_WolfC)->Character_GetIsAlive() == true) {
        CP_RanGenDDChance();
        if (DD[0] < player.Player_GetTeamBot(CP_PigC)->Character_GetLevel() * 5) {
            FS_AttackByPig(player, level, CP_PigC, CP_WolfC, UserAction);
            std::cout << "You dealt " << player.Player_GetTeamBot(CP_PigC)->Character_GetItemFINV(0)->Item_GetDMG() << "!" << std::endl;

            std::cout << level->Level_GetTeamBot(CP_WolfC)->Character_GetName() << " now has " << level->Level_GetTeamBot(CP_WolfC)->Character_GetCHP() << " health points." << std::endl << std::endl;
            system("pause");
            player.Player_SetTurn(false);
            FS_FightUI(player, level);
        }
        if (DD[0] > player.Player_GetTeamBot(CP_PigC)->Character_GetLevel() * 5) {
            std::cout << "Double damage failed, you dealt 0 damage." << std::endl;

            std::cout << level->Level_GetTeamBot(CP_WolfC)->Character_GetName() << " now has " << level->Level_GetTeamBot(CP_WolfC)->Character_GetCHP() << " health points." << std::endl << std::endl;
            system("pause");
            player.Player_SetTurn(false);
            FS_FightUI(player, level);
        }
    }
}

void FightSystem::FS_BotAttacks(CP_Player& player, CP_LevelBase* level) {
    while (level->Level_GetTeamBot(toattack[0])->Character_GetIsAlive() == false || player.Player_GetTeamBot(toattack[1])->Character_GetIsAlive() == false) {
        CP_RanGenBotToAttack();
    }

    std::cout << "Enemy wolf: " << level->Level_GetTeamBot(toattack[0])->Character_GetName() << std::endl << std::endl;

    std::cout << "Your pig: " << player.Player_GetTeamBot(toattack[1])->Character_GetName() << std::endl << std::endl;

    FS_AttackByWolf(player, level, toattack[0], toattack[1]);
    if (hitc[0] >= level->Level_GetTeamBot(toattack[1])->Character_GetCHit()) {
        std::cout << "Enemy wolf " << level->Level_GetTeamBot(toattack[0])->Character_GetName() << " attacks!" << std::endl;
        GP_AsciiRenderer.RenderScene("battle_left_right");
        std::cout << "Your pig " << player.Player_GetTeamBot(toattack[1])->Character_GetName() + std::to_string(toattack[1] + 1) << " received " << level->Level_GetTeamBot(toattack[0])->Character_GetItemFINV(0)->Item_GetDMG() << " damage" << std::endl;
        std::cout << "Health remaining: " << player.Player_GetTeamBot(toattack[1])->Character_GetCHP() << std::endl << std::endl;
    }

    if (hitc[0] < level->Level_GetTeamBot(toattack[1])->Character_GetCHit()) {
        std::cout << "Enemy wolf " << level->Level_GetTeamBot(toattack[0])->Character_GetName() << " missed!" << std::endl;
        std::cout << "Your pig " << player.Player_GetTeamBot(toattack[1])->Character_GetName() + std::to_string(toattack[1] + 1) << " received no damage" << std::endl;
        std::cout << "Health remaining: " << player.Player_GetTeamBot(toattack[1])->Character_GetCHP() << std::endl << std::endl;
    }

    system("pause");
    player.Player_SetTurn(true);
    FS_FightUI(player, level);
}

void FightSystem::FS_FightUI(CP_Player& player, CP_LevelBase* level)
{
    int player_choice;
    int player_wolf_choice;

    FS_CheckPlayerTeamIsDead(player);
    FS_CheckBotTeamIsDead(level);

    system("cls");
    if (FS_PlayerTeamWin == false and FS_BotTeamWin == false) {
        std::cout << "<- Pig Killer ->" << std::endl << std::endl;
        if (player.Player_GetTurn() == true) {
            std::cout << "Your gang: " << std::endl;
            for (int i = 0; i < player.Player_GetPTSize(); i++) {
                std::cout << i + 1 << ". " << player.Player_GetTeamBot(i)->Character_GetName() << " [" << player.Player_GetTeamBot(i)->Character_GetCHP() << "/" << player.Player_GetTeamBot(i)->Character_GetHP() << "] | Weapon: " << player.Player_GetTeamBot(i)->Character_GetItemFINV(0)->Item_GetName() << " with damage: " << player.Player_GetTeamBot(i)->Character_GetItemFINV(0)->Item_GetDMG() << std::endl;
            }

            std::cout << std::endl;
            std::cout << "Choose a pig to attack an enemy wolf: ";
            std::cin >> player_choice;

            while (player.Player_GetTeamBot(player_choice - 1)->Character_GetIsAlive() == false) {
                std::cout << "This pig is dead, choose another one: ";
                std::cin >> player_choice;
            }

            system("cls");
            std::cout << "<- Pig Killer ->" << std::endl << std::endl;

            std::cout << "Wolf gang: " << std::endl;
            for (int i = 0; i < level->Level_GetWolfTeamSize(); i++) {
                std::cout << i + 1 << ". " << level->Level_GetTeamBot(i)->Character_GetName() << " [" << level->Level_GetTeamBot(i)->Character_GetCHP() << "/" << level->Level_GetTeamBot(i)->Character_GetHP() << "] | Weapon: " << level->Level_GetTeamBot(i)->Character_GetItemFINV(0)->Item_GetName() << " with damage: " << level->Level_GetTeamBot(i)->Character_GetItemFINV(0)->Item_GetDMG() << std::endl;
            }

            std::cout << std::endl;
            std::cout << "Choose a wolf to attack: ";
            std::cin >> player_wolf_choice;
            std::cout << std::endl;

            while (level->Level_GetTeamBot(player_wolf_choice - 1)->Character_GetIsAlive() == false) {
                std::cout << "That wolf is already dead, choose another one: ";
                std::cin >> player_wolf_choice;
            }

            system("cls");

            std::cout << "<- Pig Killer ->" << std::endl << std::endl;
            FS_PlayerAttacks(player, level, player_choice - 1, player_wolf_choice - 1);
        }

        if (player.Player_GetTurn() == false) {
            FS_BotAttacks(player, level);
        }
    }
    if (FS_PlayerTeamWin == true or FS_BotTeamWin == true) {
        FS_BattleEnds(player, level);
    }
}



void FightSystem::FS_CheckPlayerTeamIsDead(CP_Player& player)
{
    int FS_CurrentPlayerTeamHP = {};

    for (int i = 0; i < player.Player_GetPTSize(); i++) {
        FS_CurrentPlayerTeamHP += player.Player_GetTeamBot(i)->Character_GetCHP();
    }

    if (FS_CurrentPlayerTeamHP == 0) {
        FS_BotTeamWin = true;
    }
    else {
        FS_BotTeamWin = false;
    }
}

void FightSystem::FS_CheckBotTeamIsDead(CP_LevelBase* level)
{
    int FS_CurrentBotTeamHP = {};

    for (int i = 0; i < level->Level_GetWolfTeamSize(); i++) {
        FS_CurrentBotTeamHP += level->Level_GetTeamBot(i)->Character_GetCHP();
    }

    if (FS_CurrentBotTeamHP == 0) {
        FS_PlayerTeamWin = true;
    }
    else {
        FS_PlayerTeamWin = false;
    }
}

void FightSystem::FS_BattleEnds(CP_Player& player, CP_LevelBase* level)
{
    if (FS_PlayerTeamWin == true) {
        if (level->Level_GetName() == "Wolf Base") {
            P_GameEnding();
        }
        else {
            system("cls");
            CP_RanGenMoney();

            CP_RanGenPigBotChance();
            CP_RanGenWeaponChance();
            for (int i = 0; i < psize; i++) {
                if (pigc[i] == 0) {
                    player.NPC_AddToAvailable(new CP_PigDefault);
                    if (weapc[i] == 0) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemSword);
                    }
                    if (weapc[i] == 1) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemBulava);
                    }
                    if (weapc[i] == 2) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemSekira);
                    }
                    if (weapc[i] == 3) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemAxe);
                    }
                    if (weapc[i] == 4) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemKatana);
                    }
                    if (weapc[i] == 5) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemMorgenshtern);
                    }
                    if (weapc[i] == 6) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemArbalet);
                    }
                }
                if (pigc[i] == 1) {
                    player.NPC_AddToAvailable(new CP_PigPro);
                    if (weapc[i] == 0) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemSword);
                    }
                    if (weapc[i] == 1) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemBulava);
                    }
                    if (weapc[i] == 2) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemSekira);
                    }
                    if (weapc[i] == 3) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemAxe);
                    }
                    if (weapc[i] == 4) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemKatana);
                    }
                    if (weapc[i] == 5) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemMorgenshtern);
                    }
                    if (weapc[i] == 6) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemArbalet);
                    }
                }
                if (pigc[i] == 2) {
                    player.NPC_AddToAvailable(new CP_PigMPro);
                    if (weapc[i] == 0) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemSword);
                    }
                    if (weapc[i] == 1) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemBulava);
                    }
                    if (weapc[i] == 2) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemSekira);
                    }
                    if (weapc[i] == 3) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemAxe);
                    }
                    if (weapc[i] == 4) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemKatana);
                    }
                    if (weapc[i] == 5) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemMorgenshtern);
                    }
                    if (weapc[i] == 6) {
                        player.Player_GetAvailableBot(player.Player_GetAvailableSize() - 1)->Character_AddToInventory(new CP_ItemArbalet);
                    }
                }
            }

            std::cout << "<- Pig Killer ->" << std::endl << std::endl;
            std::cout << "Congratulations! You cleared location " << level->Level_GetName() << " from wolves! As a reward you get " << coins[0] << " acorns in your wallet!" << std::endl;
            std::cout << "You also get " << level->Level_GetEXP() << " experience points that can be used to upgrade your pigs" << std::endl << std::endl;
            std::cout << "New members joined your team: " << std::endl;
            for (int i = -2 + (level->Level_GetID() * 2); i < player.Player_GetAvailableSize(); i++) {
                std::cout << player.Player_GetAvailableBot(i)->Character_GetName() << " / HP: " << player.Player_GetAvailableBot(i)->Character_GetHP() << " / Weapon in inventory: " << player.Player_GetAvailableBot(i)->Character_GetItemFINV(0)->Item_GetName() << " with damage " << player.Player_GetAvailableBot(i)->Character_GetItemFINV(0)->Item_GetDMG() << std::endl;
            }

            player.Player_AddToBalance(coins[0]);
            level->Level_SetIsCompleted(true);
            FS_PlayerTeamWin = false;
            FS_BotTeamWin = false;
            player.Player_SetTurn(false);
            level->Level_WolfTeamClear();


            player.Character_GainEXP(level->Level_GetEXP());

            std::cout << std::endl;
            system("pause");
            system("cls");
            for (int i = 0; i < player.Player_GetPTSize(); i++) {
                player.Player_GetTeamBot(i)->Character_SetCHP(player.Player_GetTeamBot(i)->Character_GetHP());
                player.Player_GetTeamBot(i)->Character_SetIsAlive(true);
            }
            level->Level_AfterGameplay();
            system("cls");
            P_BackToPigBase();
        }
    }

    if (FS_BotTeamWin == true) {
        if (level->Level_GetName() == "Kabak") {
            P_GameEndingBegin();
        }
        else {
            system("cls");
            CP_RanGenMoney();
            std::cout << "<- Pig Killer ->" << std::endl << std::endl;
            std::cout << "You lost! This is terrible, location " << level->Level_GetName() << " is still under wolf control! You receive " << (coins[0] * 0, 25) << " acorns in your wallet!" << std::endl;

            player.Player_AddToBalance((coins[0] * 0, 5));
            FS_PlayerTeamWin = false;
            FS_BotTeamWin = false;
            player.Player_SetTurn(false);
            level->Level_WolfTeamClear();

            system("pause");
            system("cls");

            for (int i = 0; i < player.Player_GetPTSize(); i++) {
                player.Player_GetTeamBot(i)->Character_SetCHP(player.Player_GetTeamBot(i)->Character_GetHP());
                player.Player_GetTeamBot(i)->Character_SetIsAlive(true);
            }
            P_BackToPigBase();
        }
    }
}

void FightSystem::FS_BackToGame(CP_Player& player, TravelSystem& Travel)
{
    if (Travel.TS_GetLevel(player.Player_GetCurrentLocation())->Level_GetIsCompleted() == true) {
        return;
    }
}
