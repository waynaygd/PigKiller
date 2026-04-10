#pragma once
#include "alllevels.h"
#include "allclasses.h"
#include "travelsystem.h"

void CP_RanGenBotToAttack();

void CP_RanGenMoney();

class FightSystem {
public:
	void FS_StartFight(CP_Player& player, CP_LevelBase* level);
	void FS_AttackByPig(CP_Player& player, CP_LevelBase* level, int CP_PigC, int CP_WolfC, int type_dmg);
	void FS_FightUI(CP_Player& player, CP_LevelBase* level);
	void FS_AttackByWolf(CP_Player& player, CP_LevelBase* level, int CP_PigC, int CP_WolfC);

	void FS_PlayerAttacks(CP_Player& player, CP_LevelBase* level, int CP_PigC, int CP_WolfC);
	void FS_BotAttacks(CP_Player& player, CP_LevelBase* level);

	void FS_CheckPlayerTeamIsDead(CP_Player& player);
	void FS_CheckBotTeamIsDead(CP_LevelBase* level);
	void FS_BattleEnds(CP_Player& player, CP_LevelBase* level);

	void FS_BackToGame(CP_Player& player, TravelSystem& Travel);

protected:
	bool FS_BotTeamWin = false;
	bool FS_PlayerTeamWin = false;
	int FS_PlayerAbilityPoints = 2;
};
