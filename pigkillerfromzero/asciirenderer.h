#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class CP_AsciiRenderer {
private:
    std::unordered_map<std::string, std::vector<std::string>> ASCII_Scenes;

public:
    CP_AsciiRenderer();
    void RenderScene(const std::string& SceneKey) const;
};

extern CP_AsciiRenderer GP_AsciiRenderer;
