#include "item.h"

std::string CP_ItemBase::Item_GetName()
{
    return Item_Name;
}

std::string CP_ItemBase::Item_GetDescription()
{
    return Item_Description;
}

std::string CP_ItemBase::Item_GetClass()
{
    return Item_Class;
}

int CP_ItemBase::Item_GetID()
{
    return Item_ID;
}

int CP_ItemBase::Item_GetCost()
{
    return Item_Cost;
}

int CP_ItemBase::Item_GetDMG()
{
    return Item_DMG;
}

int CP_ItemBase::Item_GetHealUP()
{
    return Item_HealUP;
}
