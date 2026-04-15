#pragma once
#include "alllevels.h"
#include "allclasses.h"

class TravelSystem {
public:
	void TS_ShowAllLevels();
	void TS_TravelToLevel(CP_Player& player, CP_LevelBase* level);

	CP_LevelBase* TS_GetLevel(int Level_ID);
	void TS_UITravel(CP_Player& player);
	bool TS_CanPBTravel(CP_Player& player, CP_LevelBase* level);
	bool TS_ProcessTravelRisks(CP_Player& player);
protected:
	bool TS_ConfirmTravel;
};
