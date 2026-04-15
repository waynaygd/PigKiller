#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <random>
#include <cstdlib>
#include "travelsystem.h"
#include "fightsystem.h"
#include "shop.h"
#include "asciirenderer.h"
#include "consoleutils.h"
#include "allitems.h"

std::vector <CP_LevelBase*> Level = { new CP_LevelPigBase, new CP_LevelKabak, new CP_LevelShop, new CP_LevelBank, new CP_LevelWolfBase };
CP_Shop Shop;

namespace {
struct TravelConfig {
    int CooldownSeconds = 3;
    int AmbushChancePercent = 25;
    int AmbushMaxEnemies = 2;
    int AmbushMaxEnemyTier = 1;
};

std::vector<std::string> GetTravelConfigRoots()
{
    std::vector<std::string> Roots;
    Roots.push_back("data/config");
    Roots.push_back("pigkillerfromzero/data/config");
    Roots.push_back("../data/config");
    Roots.push_back("../pigkillerfromzero/data/config");
    Roots.push_back("../../data/config");
    Roots.push_back("../../pigkillerfromzero/data/config");
    return Roots;
}

std::string JoinPath(const std::string& Left, const std::string& Right)
{
    if (Left.empty()) {
        return Right;
    }

    const char LastChar = Left[Left.size() - 1];
    if (LastChar == '/' || LastChar == '\\') {
        return Left + Right;
    }

    return Left + "/" + Right;
}

int ParseIntForKey(const std::string& JsonText, const std::string& Key, int DefaultValue)
{
    const std::string QuotedKey = "\"" + Key + "\"";
    const std::size_t KeyPos = JsonText.find(QuotedKey);
    if (KeyPos == std::string::npos) {
        return DefaultValue;
    }

    const std::size_t ColonPos = JsonText.find(':', KeyPos);
    if (ColonPos == std::string::npos) {
        return DefaultValue;
    }

    std::size_t ValueStart = ColonPos + 1;
    while (ValueStart < JsonText.size() && (JsonText[ValueStart] == ' ' || JsonText[ValueStart] == '\n' || JsonText[ValueStart] == '\r' || JsonText[ValueStart] == '\t')) {
        ValueStart++;
    }

    bool IsNegative = false;
    if (ValueStart < JsonText.size() && JsonText[ValueStart] == '-') {
        IsNegative = true;
        ValueStart++;
    }

    std::size_t ValueEnd = ValueStart;
    while (ValueEnd < JsonText.size() && JsonText[ValueEnd] >= '0' && JsonText[ValueEnd] <= '9') {
        ValueEnd++;
    }

    if (ValueEnd == ValueStart) {
        return DefaultValue;
    }

    const int Parsed = std::atoi(JsonText.substr(ValueStart, ValueEnd - ValueStart).c_str());
    if (IsNegative) {
        return -Parsed;
    }
    return Parsed;
}

const TravelConfig& GetTravelConfig()
{
    static TravelConfig Config;
    static bool IsLoaded = false;
    if (IsLoaded) {
        return Config;
    }

    const std::vector<std::string> Roots = GetTravelConfigRoots();
    for (std::size_t i = 0; i < Roots.size(); i++) {
        std::ifstream Input(JoinPath(Roots[i], "travel_settings.json").c_str());
        if (!Input.is_open()) {
            continue;
        }

        std::ostringstream Buffer;
        Buffer << Input.rdbuf();
        const std::string JsonText = Buffer.str();

        Config.CooldownSeconds = ParseIntForKey(JsonText, "travel_cooldown_seconds", Config.CooldownSeconds);
        Config.AmbushChancePercent = ParseIntForKey(JsonText, "ambush_chance_percent", Config.AmbushChancePercent);
        Config.AmbushMaxEnemies = ParseIntForKey(JsonText, "ambush_max_enemies", Config.AmbushMaxEnemies);
        Config.AmbushMaxEnemyTier = ParseIntForKey(JsonText, "ambush_max_enemy_tier", Config.AmbushMaxEnemyTier);
        break;
    }

    if (Config.CooldownSeconds < 0) Config.CooldownSeconds = 0;
    if (Config.AmbushChancePercent < 0) Config.AmbushChancePercent = 0;
    if (Config.AmbushChancePercent > 100) Config.AmbushChancePercent = 100;
    if (Config.AmbushMaxEnemies < 1) Config.AmbushMaxEnemies = 1;
    if (Config.AmbushMaxEnemies > 2) Config.AmbushMaxEnemies = 2;
    if (Config.AmbushMaxEnemyTier < 0) Config.AmbushMaxEnemyTier = 0;
    if (Config.AmbushMaxEnemyTier > 1) Config.AmbushMaxEnemyTier = 1;

    IsLoaded = true;
    return Config;
}

CP_CharacterBase* CreateAmbushWolfByTier(int MaxTier)
{
    static std::mt19937 Rng(std::random_device{}());
    std::uniform_int_distribution<int> Dist(0, MaxTier);
    const int Tier = Dist(Rng);
    if (Tier == 0) {
        CP_CharacterBase* Wolf = new CP_WolfDefault;
        Wolf->Character_AddToInventory(new CP_ItemSword);
        return Wolf;
    }

    CP_CharacterBase* Wolf = new CP_WolfPro;
    Wolf->Character_AddToInventory(new CP_ItemAxe);
    return Wolf;
}
} // namespace

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
            if (TS_ProcessTravelRisks(player) == false) {
                P_BackToPigBase();
                return;
            }
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

bool TravelSystem::TS_ProcessTravelRisks(CP_Player& player)
{
    const TravelConfig& Config = GetTravelConfig();

    if (Config.CooldownSeconds > 0) {
        std::cout << "Travel started..." << std::endl;
        for (int i = Config.CooldownSeconds; i > 0; i--) {
            std::cout << "Arriving in " << i << " sec..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    static std::mt19937 Rng(std::random_device{}());
    std::uniform_int_distribution<int> ChanceDist(1, 100);
    const int Roll = ChanceDist(Rng);
    if (Roll > Config.AmbushChancePercent) {
        return true;
    }

    std::uniform_int_distribution<int> CountDist(1, Config.AmbushMaxEnemies);
    const int EnemyCount = CountDist(Rng);

    CP_LevelBase AmbushLevel(-1, 0, EnemyCount, 0, "Road Ambush", "A small wolf gang attacks during travel", false, false);
    for (int i = 0; i < EnemyCount; i++) {
        AmbushLevel.Level_AddWolfToVector(CreateAmbushWolfByTier(Config.AmbushMaxEnemyTier));
    }

    system("cls");
    std::cout << "<- Pig Killer ->" << std::endl << std::endl;
    std::cout << "Ambush! A wolf gang attacks your team on the road." << std::endl;
    CP_PauseForContinue();

    FightSystem TravelFight;
    return TravelFight.FS_StartSkirmish(player, &AmbushLevel);
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
