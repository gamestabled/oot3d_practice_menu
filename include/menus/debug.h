#pragma once

#include "menu.h"

extern Menu DebugMenu;

extern u32 memoryEditorAddress;

extern void DebugActors_ShowActors();
extern void Debug_PlayerStatesMenuShow();
extern void NewActorValuesMenuInit();
extern void Debug_NewActorValuesMenuShow();
extern void Debug_MemoryEditor();
extern void MemoryEditor_EditAddress();
extern void MemoryEditor_EditValue();

typedef enum {
    PLAYERSTATES_PART1,
    PLAYERSTATES_PART2,
    PLAYERSTATES_PART3,
    PLAYERSTATES_PART4,
    PLAYERSTATES_HELD_ITEM,
} PlayerStatesOptions;
