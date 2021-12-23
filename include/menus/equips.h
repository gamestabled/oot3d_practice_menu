#pragma once

#include "menu.h"

extern AmountMenu EquipsMenu;
void Equips_ShowEquipsMenu();

typedef enum {
    EQUIP_BUTTON_B = 0,
    EQUIP_BUTTON_Y,
    EQUIP_BUTTON_X,
    EQUIP_BUTTON_I,
    EQUIP_BUTTON_II,
    EQUIP_SLOT_Y,
    EQUIP_SLOT_X,
    EQUIP_SLOT_I,
    EQUIP_SLOT_II,
    EQUIP_SWORD,
    EQUIP_SHIELD,
    EQUIP_TUNIC,
    EQUIP_BOOTS,
    EQUIP_TEMP_B,
} EquipButtons;
