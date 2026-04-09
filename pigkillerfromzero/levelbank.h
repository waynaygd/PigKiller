#pragma once
#include "level.h"

class CP_LevelBank : public CP_LevelBase {
public:
	CP_LevelBank() : CP_LevelBase(3, 250, 3, 3, "Bank", "Just a bank", false, false) {};

	void Level_Gameplay() override;
	void Level_AfterGameplay() override;
};