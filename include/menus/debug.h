#pragma once

#include "menu.h"

extern Menu DebugMenu;

extern u32 memoryEditorAddress;

extern void DebugActors_ShowActors();
extern void Debug_ShowObjects();
extern void Debug_FlagsEditor();
extern void Debug_PlayerStatesMenuShow();
extern void Debug_MemoryEditor();
extern void MemoryEditor_EditAddress();
extern void MemoryEditor_EditValue();
extern bool MemoryEditor_ConfirmPermissionOverride();

typedef enum {
    FLAGS_SWITCH,
    FLAGS_TEMP_SWITCH,
    FLAGS_ROOMS,
    FLAGS_FLOORS,
    FLAGS_CHEST,
    FLAGS_CLEAR,
    FLAGS_TEMP_CLEAR,
    FLAGS_COLLECT,
    FLAGS_TEMP_COLLECT,
    FLAGS_GOLD_SKULLTULAS,
    FLAGS_EVENT_CHK_INF,
    FLAGS_ITEM_GET_INF,
    FLAGS_INF_TABLE_1,
    FLAGS_INF_TABLE_2,
    FLAGS_EVENT_INF,
} FlagsGroups;

typedef enum {
    PLAYERSTATES_PART1,
    PLAYERSTATES_PART2,
    PLAYERSTATES_PART3,
    PLAYERSTATES_PART4,
    PLAYERSTATES_HELD_ITEM,
} PlayerStatesOptions;
