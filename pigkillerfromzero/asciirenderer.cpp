#include <iostream>
#include <iomanip>
#include "asciirenderer.h"

CP_AsciiRenderer GP_AsciiRenderer;

CP_AsciiRenderer::CP_AsciiRenderer()
{
    ASCII_Scenes["main_menu"] = {
        "   ____  _       _  ___ _ _ _           ",
        "  |  _ \\(_) __ _| |/ (_) | | | ___ _ __ ",
        "  | |_) | |/ _` | ' /| | | | |/ _ \\ '__|",
        "  |  __/| | (_| | . \\| | | | |  __/ |   ",
        "  |_|   |_|\\__, |_|\\_\\_|_|_|_|\\___|_|   ",
        "           |___/                           "
    };

    ASCII_Scenes["base_tavern_interior"] = {
        "  ______________________________________  ",
        " |  []  []  []       Tavern Base        | ",
        " |      ( )        ( )         ( )      | ",
        " |   ___|_|___   ___|_|___   ___|_|___   | ",
        " |  |  _   _  | |  _   _  | |  _   _  |  | ",
        " |__|_| |_| |_|_|_| |_| |_|_|_| |_| |_|__| "
    };

    ASCII_Scenes["travel_map"] = {
        " [BASE]* ---- [TAVERN] ---- [MARKET] ",
        "    |                         |     ",
        " [BANK] ---------------- [WOLF BASE]"
    };

    ASCII_Scenes["upgrade_party_overview"] = {
        "  [1] Leader [2] Fighter [3] Fighter [4] Fighter ",
        "  W: weapon and stats  | A: armor (future) "
    };

    ASCII_Scenes["battle_left_right"] = {
        " PLAYER GANG                     WOLF GANG ",
        " [Pig][Pig][Pig]               [Wolf][Wolf][Wolf]"
    };
}

void CP_AsciiRenderer::RenderScene(const std::string& SceneKey) const
{
    auto Scene = ASCII_Scenes.find(SceneKey);
    if (Scene == ASCII_Scenes.end()) {
        return;
    }

    std::cout << "==============================================" << std::endl;
    for (const std::string& SceneLine : Scene->second) {
        std::cout << SceneLine << std::endl;
    }
    std::cout << "==============================================" << std::endl << std::endl;
}

void CP_AsciiRenderer::RenderBattleScene(int SelectedPig, int SelectedWolf) const
{
    auto BuildTeamLine = [](const std::string& Name, int SelectedIndex) {
        std::string Result;
        for (int i = 0; i < 3; i++) {
            if (i == SelectedIndex) {
                Result += "\033[1m[" + Name + "]\033[0m";
            }
            else {
                Result += "[" + Name + "]";
            }
        }
        return Result;
    };

    std::string PigLine = BuildTeamLine("Pig", SelectedPig);
    std::string WolfLine = BuildTeamLine("Wolf", SelectedWolf);

    std::cout << "==============================================" << std::endl;
    std::cout << " PLAYER GANG                     WOLF GANG " << std::endl;
    std::cout << " " << std::left << std::setw(29) << PigLine << " " << WolfLine << std::endl;
    std::cout << "==============================================" << std::endl << std::endl;
}
