#include <iostream>
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
        " |  []  []  []      Таверна-база       | ",
        " |      ( )        ( )         ( )      | ",
        " |   ___|_|___   ___|_|___   ___|_|___   | ",
        " |  |  _   _  | |  _   _  | |  _   _  |  | ",
        " |__|_| |_| |_|_|_| |_| |_|_|_| |_| |_|__| "
    };

    ASCII_Scenes["travel_map"] = {
        " [БАЗА]* ---- [КАБАК] ---- [РЫНОК] ",
        "    |                         |     ",
        " [БАНК] ---------------- [ВОЛЧЬЯ БАЗА]"
    };

    ASCII_Scenes["upgrade_party_overview"] = {
        "  [1] Лидер  [2] Боец  [3] Боец  [4] Боец  ",
        "  W: оружие и параметры | A: броня (future) "
    };

    ASCII_Scenes["battle_left_right"] = {
        " БАНДА ИГРОКА                    БАНДА ВОЛКОВ ",
        " [Свин][Свин][Свин]            [Волк][Волк][Волк]"
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
