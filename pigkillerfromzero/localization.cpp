#include "localization.h"

#include <unordered_map>

namespace {
const std::unordered_map<std::string, std::string> kEnglishStrings = {
    {"menu.start_game", "- 1. Start Game -"},
    {"menu.funny_button", "- 2. Funny Button -"},
    {"menu.credits", "- 3. Credits -"},
    {"menu.exit", "- 4. Exit -"},
    {"menu.choose_option", "- Choose an option: "},

    {"base.go_battle", "- 1. Go to battle -"},
    {"base.change_team", "- 2. Change team member -"},
    {"base.upgrade_team", "- 3. Upgrade team members -"},
    {"base.change_weapon", "- 4. Change weapons for yourself or your team -"},

    {"ending.win.1", "The Wolf King has fallen!"},
    {"ending.win.2", "The Chief Pig and his brave gang became heroes not only of the village, but also of nearby towns!"},
    {"ending.win.3", "The Pig King personally came to the village to thank the leader for his courage and honor."},
    {"ending.win.4", "And from then on, they lived happily ever after..."},

    {"ending.lose.1", "The gang could not withstand the assault at the tavern..."},
    {"ending.lose.2", "How could anyone even talk about defending the village now?"},
    {"ending.lose.3", "The Wolf King ordered an attack on your base; the pigs tried to hold out, but failed..."},
    {"ending.lose.4", "You betrayed us all."},

    {"credits.author", "Code, narrative, and game design by: Timofey Zhuravlev"}
};

const std::string kMissingPrefix = "[missing-loc-key] ";
std::string kMissingValue;
} // namespace

const std::string& CP_Localization::L(const std::string& key)
{
    auto it = kEnglishStrings.find(key);
    if (it != kEnglishStrings.end()) {
        return it->second;
    }

    kMissingValue = kMissingPrefix + key;
    return kMissingValue;
}
