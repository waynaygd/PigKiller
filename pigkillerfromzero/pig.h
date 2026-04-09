#pragma once
#include "character.h"

class CP_PigDefault : public CP_CharacterBase {
public:
	CP_PigDefault() : CP_CharacterBase("Default Pig", "Just a default pig", 15, 45, 2, 15, 1, 2, 0, true) {};
};

class CP_PigPro : public CP_CharacterBase {
public:
	CP_PigPro() : CP_CharacterBase("Pro Pig", "Just a pro pig", 20, 45, 5, 20, 2, 3, 10, true) {};
};

class CP_PigMPro : public CP_CharacterBase {
public:
	CP_PigMPro() : CP_CharacterBase("Mega Pro Pig", "Just a mega pro pig", 35, 45, 10, 35, 3, 5, 20, true) {};
};