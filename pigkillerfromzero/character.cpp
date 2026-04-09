#include "character.h"

std::string CP_CharacterBase::Character_GetName()
{
    return Character_Name;
}

std::string CP_CharacterBase::Character_GetDescription()
{
    return Character_Description;
}

int CP_CharacterBase::Character_GetHP()
{
    return Character_HP;
}

int CP_CharacterBase::Character_GetArmor()
{
    return Character_Armor;
}

int CP_CharacterBase::Character_GetCHP()
{
    return Character_CHP;
}

int CP_CharacterBase::Character_GetLevel()
{
    return Character_Level;
}

int CP_CharacterBase::Character_GetEXP()
{
    return Character_EXP;
}

int CP_CharacterBase::Character_GetCHit()
{
    return Character_ChanceToHit;
}

bool CP_CharacterBase::Character_GetIsAlive()
{
    return Character_IsAlive;
}

void CP_CharacterBase::Character_SetCHP(int Character_NHP)
{
    Character_CHP = Character_NHP;
}

void CP_CharacterBase::Character_GainEXP(int Character_NEXP) {
    Character_EXP += Character_NEXP;
}

void CP_CharacterBase::Character_LevelUP()
{
    Character_Level++;
    Character_UPGHP();
    Character_UPGArmor();
}

void CP_CharacterBase::Character_SetIsAlive(bool Character_CState)
{
    Character_IsAlive = Character_CState;
}

void CP_CharacterBase::Character_UPGHP()
{
    Character_HP += (2,5 * Character_Level);
    Character_SetCHP(Character_HP);
}

void CP_CharacterBase::Character_UPGArmor()
{
    Character_Armor += (1, 5 * Character_Level);
}

CP_ItemBase* CP_CharacterBase::Character_GetItemFINV(int Item_ID)
{
    return Character_Inventory[Item_ID];
}

void CP_CharacterBase::Character_AddToInventory(CP_ItemBase* Item)
{
    Character_Inventory.push_back(Item);
}

void CP_CharacterBase::Character_RemoveFromInventory(int Item_ID)
{
    Character_Inventory.erase(Character_Inventory.cbegin() + Item_ID);
}

void CP_CharacterBase::Character_AddWeapon(CP_ItemBase* Item)
{
    Character_Inventory.insert(Character_Inventory.begin(), Item);
}

void CP_CharacterBase::Character_TakeDamage(int Weapon_Damage)
{
    if (Weapon_Damage > Character_CHP) {
        Character_CHP = 0;
        Character_SetIsAlive(false);
        return;
    }

    Character_CHP -= Weapon_Damage;
}
