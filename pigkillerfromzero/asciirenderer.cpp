#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "asciirenderer.h"
#include "character.h"

CP_AsciiRenderer GP_AsciiRenderer;

namespace {
std::vector<std::string> GetAsciiSearchRoots()
{
    std::vector<std::string> Roots;
    Roots.push_back("data/ascii");
    Roots.push_back("pigkillerfromzero/data/ascii");
    Roots.push_back("../data/ascii");
    Roots.push_back("../../data/ascii");
    Roots.push_back("../pigkillerfromzero/data/ascii");
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

std::string BuildFighterLine(CP_CharacterBase* Fighter, int Index)
{
    if (Fighter == nullptr) {
        return "[Empty slot]";
    }

    CP_ItemBase* Weapon = Fighter->Character_GetItemFINV(0);

    std::string WeaponLabel = "No weapon";
    if (Weapon != nullptr) {
        WeaponLabel = Weapon->Item_GetName() + " (" + std::to_string(Weapon->Item_GetDMG()) + " DMG)";
    }

    std::ostringstream Out;
    Out << "[" << Index + 1 << "] " << Fighter->Character_GetName() << '\n';
    Out << "    Class: " << Fighter->Character_GetDescription() << '\n';
    Out << "    HP/Weapon: " << Fighter->Character_GetCHP() << "/" << Fighter->Character_GetHP() << " | " << WeaponLabel;
    return Out.str();
}
} // namespace

CP_AsciiRenderer::CP_AsciiRenderer()
{
    LoadSceneFromJson("main_menu", "main_menu.json");
    LoadSceneFromJson("base_tavern_interior", "base_tavern_interior.json");
    LoadSceneFromJson("travel_map", "travel_map.json");
    LoadSceneFromJson("upgrade_party_overview", "upgrade_party_overview.json");
    LoadSceneFromJson("battle_left_right", "battle_left_right.json");
}

bool CP_AsciiRenderer::LoadSceneFromJson(const std::string& SceneKey, const std::string& FileName)
{
    const std::vector<std::string> Roots = GetAsciiSearchRoots();
    for (std::size_t i = 0; i < Roots.size(); i++) {
        const std::string FullPath = JoinPath(Roots[i], FileName);

        std::ifstream Input(FullPath.c_str());
        if (!Input.is_open()) {
            continue;
        }

        std::ostringstream Buffer;
        Buffer << Input.rdbuf();
        std::vector<std::string> Lines = ParseLinesArrayFromJson(Buffer.str());
        if (!Lines.empty()) {
            ASCII_Scenes[SceneKey] = Lines;
            return true;
        }
    }

    return false;
}

std::vector<std::string> CP_AsciiRenderer::ParseLinesArrayFromJson(const std::string& JsonText)
{
    std::vector<std::string> Result;

    const std::string Key = "\"lines\"";
    const std::size_t KeyPos = JsonText.find(Key);
    if (KeyPos == std::string::npos) {
        return Result;
    }

    const std::size_t ArrayStart = JsonText.find('[', KeyPos);
    const std::size_t ArrayEnd = JsonText.find(']', ArrayStart);
    if (ArrayStart == std::string::npos || ArrayEnd == std::string::npos || ArrayEnd <= ArrayStart) {
        return Result;
    }

    bool InString = false;
    bool Escaping = false;
    std::string Current;

    for (std::size_t i = ArrayStart + 1; i < ArrayEnd; i++) {
        const char Ch = JsonText[i];
        if (!InString) {
            if (Ch == '"') {
                InString = true;
                Current.clear();
            }
            continue;
        }

        if (Escaping) {
            switch (Ch) {
            case 'n': Current += '\n'; break;
            case 't': Current += '\t'; break;
            case '"': Current += '"'; break;
            case '\\': Current += '\\'; break;
            default: Current += Ch; break;
            }
            Escaping = false;
            continue;
        }

        if (Ch == '\\') {
            Escaping = true;
            continue;
        }

        if (Ch == '"') {
            InString = false;
            Result.push_back(Current);
            continue;
        }

        Current += Ch;
    }

    return Result;
}

void CP_AsciiRenderer::RenderScene(const std::string& SceneKey) const
{
    std::unordered_map<std::string, std::vector<std::string>>::const_iterator Scene = ASCII_Scenes.find(SceneKey);
    if (Scene == ASCII_Scenes.end()) {
        return;
    }

    std::cout << "==============================================" << std::endl;
    for (std::size_t i = 0; i < Scene->second.size(); i++) {
        std::cout << Scene->second[i] << std::endl;
    }
    std::cout << "==============================================" << std::endl << std::endl;
}

void CP_AsciiRenderer::RenderBattleScene(int SelectedPig, int SelectedWolf) const
{
    std::string PigLine;
    std::string WolfLine;

    for (int i = 0; i < 3; i++) {
        if (i == SelectedPig) {
            PigLine += "\033[1m[Pig]\033[0m";
        }
        else {
            PigLine += "[Pig]";
        }

        if (i == SelectedWolf) {
            WolfLine += "\033[1m[Wolf]\033[0m";
        }
        else {
            WolfLine += "[Wolf]";
        }
    }

    std::cout << "==============================================" << std::endl;
    std::cout << " PLAYER GANG                     WOLF GANG " << std::endl;
    std::cout << " " << std::left << std::setw(29) << PigLine << " " << WolfLine << std::endl;
    std::cout << "==============================================" << std::endl << std::endl;
}

void CP_AsciiRenderer::RenderBattleScene(const std::vector<CP_CharacterBase*>& PigTeam,
                                         const std::vector<CP_CharacterBase*>& WolfTeam,
                                         int SelectedPig,
                                         int SelectedWolf) const
{
    std::cout << "==============================================" << std::endl;
    std::cout << " PLAYER GANG" << std::endl;

    for (std::size_t i = 0; i < PigTeam.size(); i++) {
        if (static_cast<int>(i) == SelectedPig) {
            std::cout << "\033[1m";
        }
        std::cout << BuildFighterLine(PigTeam[i], static_cast<int>(i)) << std::endl;
        if (static_cast<int>(i) == SelectedPig) {
            std::cout << "\033[0m";
        }
    }

    std::cout << std::endl;
    std::cout << " WOLF GANG" << std::endl;

    for (std::size_t i = 0; i < WolfTeam.size(); i++) {
        if (static_cast<int>(i) == SelectedWolf) {
            std::cout << "\033[1m";
        }
        std::cout << BuildFighterLine(WolfTeam[i], static_cast<int>(i)) << std::endl;
        if (static_cast<int>(i) == SelectedWolf) {
            std::cout << "\033[0m";
        }
    }

    std::cout << "==============================================" << std::endl << std::endl;
}
