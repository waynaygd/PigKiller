#pragma once
#include <string>
#include <vector>
#include "player.h"
#include "allitems.h"

class CP_Shop {
public:
	void Shop_RemoveItemAfterSell(int Item_ID);
	void Shop_ShowAssortiment();
	void Shop_BuyProcess(CP_Player& player, int Item_ID);
	void Shop_ShowItemStats(CP_Player& player, int Item_ID);

	void Shop_Gameplay(CP_Player& player);

protected:
	int Player_Choice;
	std::vector <CP_ItemBase*> Shop_Available_Items = { new CP_ItemApple, new CP_ItemMorgenshtern, new CP_ItemSekira, new CP_ItemBulava, new CP_ItemKatana, new CP_ItemArbalet };
	int Maximum_Items = 5;
};
