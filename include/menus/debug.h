#pragma once

#include "menu.h"

extern Menu DebugMenu;

extern void NewActorValuesMenuInit();
extern void Debug_NewActorValuesMenuShow();

typedef enum {
    PLAYERSTATES_PART1,
    PLAYERSTATES_PART2,
    PLAYERSTATES_PART3,
    PLAYERSTATES_PART4,
    PLAYERSTATES_HELD_ITEM,
} PlayerStatesOptions;
