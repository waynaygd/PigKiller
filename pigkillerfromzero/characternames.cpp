#include "characternames.h"

#include <fstream>
#include <random>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace {
std::vector<std::string> GetCharacterNamesSearchRoots()
{
    std::vector<std::string> Roots;
    Roots.push_back("data/names");
    Roots.push_back("pigkillerfromzero/data/names");
    Roots.push_back("../data/names");
    Roots.push_back("../pigkillerfromzero/data/names");
    Roots.push_back("../../data/names");
    Roots.push_back("../../pigkillerfromzero/data/names");
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

std::vector<std::string> ParseStringArrayForKey(const std::string& JsonText, const std::string& Key)
{
    std::vector<std::string> Result;
    const std::string QuotedKey = "\"" + Key + "\"";
    const std::size_t KeyPos = JsonText.find(QuotedKey);
    if (KeyPos == std::string::npos) {
        return Result;
    }

    const std::size_t ArrayStart = JsonText.find('[', KeyPos);
    if (ArrayStart == std::string::npos) {
        return Result;
    }

    const std::size_t ArrayEnd = JsonText.find(']', ArrayStart);
    if (ArrayEnd == std::string::npos || ArrayEnd <= ArrayStart) {
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
            Current += Ch;
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

const std::unordered_map<std::string, std::vector<std::string>>& GetFallbackNames()
{
    static const std::unordered_map<std::string, std::vector<std::string>> FallbackNames = {
        {"default_pig", {"Niff", "Rosie", "Bacon", "Poppy", "Trotter"}},
        {"pro_pig", {"Brisket", "Hammond", "Rumble", "Porkins", "Tasha"}},
        {"mega_pro_pig", {"Boaris", "Titanham", "Mighty Oink", "Thunderhoof", "Iron Snout"}},
        {"default_wolf", {"Fang", "Skoll", "Rag", "Shadow", "Nightpaw"}},
        {"pro_wolf", {"Grimm", "Howler", "Varg", "Ashclaw", "Razor"}},
        {"mega_pro_wolf", {"Fenrik", "Dreadfang", "Moonreaper", "Bloodclaw", "Blackmane"}},
        {"boss_wolf", {"Wolf King"}}
    };
    return FallbackNames;
}

const std::unordered_map<std::string, std::vector<std::string>>& GetLoadedNames()
{
    static std::unordered_map<std::string, std::vector<std::string>> NameMap;
    static bool IsLoaded = false;

    if (IsLoaded) {
        return NameMap;
    }

    const std::vector<std::string> Roots = GetCharacterNamesSearchRoots();
    for (std::size_t i = 0; i < Roots.size(); i++) {
        std::ifstream Input(JoinPath(Roots[i], "character_names.json").c_str());
        if (!Input.is_open()) {
            continue;
        }

        std::ostringstream Buffer;
        Buffer << Input.rdbuf();
        const std::string JsonText = Buffer.str();

        NameMap["default_pig"] = ParseStringArrayForKey(JsonText, "default_pig");
        NameMap["pro_pig"] = ParseStringArrayForKey(JsonText, "pro_pig");
        NameMap["mega_pro_pig"] = ParseStringArrayForKey(JsonText, "mega_pro_pig");
        NameMap["default_wolf"] = ParseStringArrayForKey(JsonText, "default_wolf");
        NameMap["pro_wolf"] = ParseStringArrayForKey(JsonText, "pro_wolf");
        NameMap["mega_pro_wolf"] = ParseStringArrayForKey(JsonText, "mega_pro_wolf");
        NameMap["boss_wolf"] = ParseStringArrayForKey(JsonText, "boss_wolf");
        break;
    }

    IsLoaded = true;
    return NameMap;
}
} // namespace

std::string CP_GetRandomCharacterName(const std::string& CharacterClassKey)
{
    const std::unordered_map<std::string, std::vector<std::string>>& Loaded = GetLoadedNames();
    const std::unordered_map<std::string, std::vector<std::string>>& Fallback = GetFallbackNames();
    std::vector<std::string> Names;

    std::unordered_map<std::string, std::vector<std::string>>::const_iterator LoadedIt = Loaded.find(CharacterClassKey);
    if (LoadedIt != Loaded.end() && !LoadedIt->second.empty()) {
        Names = LoadedIt->second;
    }

    if (Names.empty()) {
        std::unordered_map<std::string, std::vector<std::string>>::const_iterator FallbackIt = Fallback.find(CharacterClassKey);
        if (FallbackIt != Fallback.end() && !FallbackIt->second.empty()) {
            Names = FallbackIt->second;
        }
    }

    if (Names.empty()) {
        return "Unknown";
    }

    static std::mt19937 Rng(std::random_device{}());
    std::uniform_int_distribution<int> Dist(0, static_cast<int>(Names.size()) - 1);
    return Names[Dist(Rng)];
}
