#pragma once
#include "character.h"
#include "characternames.h"

class CP_WolfDefault : public CP_CharacterBase {
public:
	CP_WolfDefault() : CP_CharacterBase(CP_GetRandomCharacterName("default_wolf"), "Default Wolf", 10, 45, 5, 10, 1, 3, 0, true) {};
};

class CP_WolfPro : public CP_CharacterBase {
public:
	CP_WolfPro() : CP_CharacterBase(CP_GetRandomCharacterName("pro_wolf"), "Pro Wolf", 15, 35, 10, 15, 2, 4, 0, true) {};
};

class CP_WolfMPro : public CP_CharacterBase {
public:
	CP_WolfMPro() : CP_CharacterBase(CP_GetRandomCharacterName("mega_pro_wolf"), "Mega Pro Wolf", 20, 25, 20, 20, 2, 5, 0, true) {};
};

class CP_WolfBoss : public CP_CharacterBase {
public:
	CP_WolfBoss() : CP_CharacterBase(CP_GetRandomCharacterName("boss_wolf"), "Boss Wolf", 60, 25, 60, 20, 5, 5, 0, true) {};
};
