#pragma once
#include "character.h"
#include "characternames.h"

class CP_PigDefault : public CP_CharacterBase {
public:
	CP_PigDefault() : CP_CharacterBase(CP_GetRandomCharacterName("default_pig"), "Default Pig", 15, 45, 2, 15, 1, 2, 0, true) {};
};

class CP_PigPro : public CP_CharacterBase {
public:
	CP_PigPro() : CP_CharacterBase(CP_GetRandomCharacterName("pro_pig"), "Pro Pig", 20, 45, 5, 20, 2, 3, 10, true) {};
};

class CP_PigMPro : public CP_CharacterBase {
public:
	CP_PigMPro() : CP_CharacterBase(CP_GetRandomCharacterName("mega_pro_pig"), "Mega Pro Pig", 35, 45, 10, 35, 3, 5, 20, true) {};
};
