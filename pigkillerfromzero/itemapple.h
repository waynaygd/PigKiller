#pragma once
#include "item.h"

class CP_ItemApple : public CP_ItemBase {
public:
	CP_ItemApple() : CP_ItemBase("Apple", "Just an apple", "Heal", 0, 5, 0, 15) {};
};