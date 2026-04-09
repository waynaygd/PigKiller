#pragma once
#include "level.h"

class CP_LevelShop : public CP_LevelBase {
public:
	CP_LevelShop() : CP_LevelBase(2, 200, 4, 1, "Bazar", "Just a shop", false, false) {};

	void Level_Gameplay() override;
	void Level_AfterGameplay() override;
};