#pragma once
#include "character.h"

class CP_WolfDefault : public CP_CharacterBase {
public:
	CP_WolfDefault() : CP_CharacterBase("Default Wolf", "Just a default wolf", 10, 45, 5, 10, 1, 3, 0, true) {};
};

class CP_WolfPro : public CP_CharacterBase {
public:
	CP_WolfPro() : CP_CharacterBase("Pro Wolf", "Just a pro wolf", 15, 35, 10, 15, 2, 4, 0, true) {};
};

class CP_WolfMPro : public CP_CharacterBase {
public:
	CP_WolfMPro() : CP_CharacterBase("Mega Pro Wolf", "Just a mega pro wolf", 20, 25, 20, 20, 2, 5, 0, true) {};
};

class CP_WolfBoss : public CP_CharacterBase {
public:
	CP_WolfBoss() : CP_CharacterBase("Boss Wolf", "Just a boss wolf", 60, 25, 60, 20, 5, 5, 0, true) {};
};

