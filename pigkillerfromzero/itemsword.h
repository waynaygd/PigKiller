#pragma once
#include "item.h"

class CP_ItemSword : public CP_ItemBase {
public:
	CP_ItemSword() : CP_ItemBase("Sword", "Just a sword", "Weapon", 1, 5, 10, 5) {};
};