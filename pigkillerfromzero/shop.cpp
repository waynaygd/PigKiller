#include <iostream>
#include "shop.h"
#include "menubasefunctions.h"
#include "consoleutils.h"

void CP_Shop::Shop_RemoveItemAfterSell(int Item_ID)
{
	auto iter = Shop_Available_Items.cbegin();
	Shop_Available_Items.erase(iter + (Item_ID));
}

void CP_Shop::Shop_ShowAssortiment()
{
	for (int i = 0; i < Shop_Available_Items.size(); i++) {
		std::cout << i + 1 << ". " << Shop_Available_Items[i]->Item_GetName() << " | " << Shop_Available_Items[i]->Item_GetCost() << std::endl;
	}
    std::cout << "0. Return to base" << std::endl;
	std::cout << "\n";
}

void CP_Shop::Shop_BuyProcess(CP_Player& player, int Item_ID)
{
    player.Player_RemoveFromBalance(Shop_Available_Items[Item_ID]->Item_GetCost());
    player.Player_AddToInventory(Shop_Available_Items[Item_ID]);
	Shop_RemoveItemAfterSell(Item_ID);
}

void CP_Shop::Shop_ShowItemStats(CP_Player& player, int Item_ID)
{
    std::cout << "<- Pig Killer ->" << std::endl << std::endl;

    std::cout << "Item: " << Shop_Available_Items[Item_ID - 1]->Item_GetName() << std::endl;
    std::cout << "Type: " << Shop_Available_Items[Item_ID - 1]->Item_GetClass() << std::endl;
    std::cout << "Description: " << Shop_Available_Items[Item_ID - 1]->Item_GetDescription() << std::endl;
    std::cout << "Price: " << Shop_Available_Items[Item_ID - 1]->Item_GetCost() << std::endl;

    std::cout << "\n";
    std::cout << "Buy this item? (0/1) ";
    std::cin >> Player_Choice;

    if (Player_Choice == 0) {
        Shop_Gameplay(player);
    }

    if (Player_Choice == 1) {
        if (player.Player_GetBalance() >= Shop_Available_Items[Item_ID - 1]->Item_GetCost()) {
            Shop_BuyProcess(player, Item_ID - 1);
        }
        else {
            std::cout << "You do not have enough money!" << std::endl;
            Shop_Gameplay(player);
        }
    }

    system("cls");
    P_BackToPigBase();
}

void CP_Shop::Shop_Gameplay(CP_Player& player)
{
    system("cls");
    std::cout << "<- Pig Killer ->" << std::endl << std::endl;
    std::cout << "Your balance: " << player.Player_GetBalance() << std::endl;
    Shop_ShowAssortiment();
    std::cout << "Choose an item: ";
    std::cin >> Player_Choice;

    if (Player_Choice == 0) {
        system("cls");
        P_BackToPigBase();
    }
    else {
        system("cls");
        Shop_ShowItemStats(player, Player_Choice);
    }
}
