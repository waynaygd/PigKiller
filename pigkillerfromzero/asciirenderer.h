#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class CP_CharacterBase;

class CP_AsciiRenderer {
private:
    std::unordered_map<std::string, std::vector<std::string>> ASCII_Scenes;

    bool LoadSceneFromJson(const std::string& SceneKey, const std::string& FileName);
    static std::vector<std::string> ParseLinesArrayFromJson(const std::string& JsonText);

public:
    CP_AsciiRenderer();
    void RenderScene(const std::string& SceneKey) const;
    void RenderBattleScene(int SelectedPig = -1, int SelectedWolf = -1, int HighlightMode = 0) const;
    void RenderBattleScene(const std::vector<CP_CharacterBase*>& PigTeam,
                           const std::vector<CP_CharacterBase*>& WolfTeam,
                           int SelectedPig = -1,
                           int SelectedWolf = -1,
                           int HighlightMode = 0) const;
};

extern CP_AsciiRenderer GP_AsciiRenderer;
