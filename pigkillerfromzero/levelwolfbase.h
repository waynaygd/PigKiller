#pragma once
#include "level.h"

class CP_LevelWolfBase : public CP_LevelBase {
public:
	CP_LevelWolfBase() : CP_LevelBase(4, 52, 4, 5, "Wolf Base", "Just a wolf base", false, false) {};

	void Level_Gameplay() override;
};