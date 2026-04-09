#pragma once
#include "level.h"

class CP_LevelKabak : public CP_LevelBase {
public:
	CP_LevelKabak() : CP_LevelBase(1, 150, 3, 1, "Kabak", "Just a kabak", false, true) {};

	void Level_Gameplay() override;
	void Level_AfterGameplay() override;
};