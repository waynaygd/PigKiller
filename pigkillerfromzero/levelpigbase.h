#pragma once
#include "level.h"
#include "player.h"
#include "menubasefunctions.h"

class CP_LevelPigBase : public CP_LevelBase {
public:
	CP_LevelPigBase() : CP_LevelBase(0, 0, 0, 0, "Pig Base", "Just a pig base", true, false) {};

	void Level_Gameplay() override;
};