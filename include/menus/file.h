#pragma once

#include "menu.h"

extern ToggleMenu FileMenu;

void File_ShowFileMenu(void);

extern void File_ToggleSkulltulaFlags(s32 selected);
extern void File_CallNavi(s32 selected);
extern void File_ToggleEponaFreed(s32 selected);
extern void File_ToggleCarpentersFreed(s32 selected);
extern void File_ToggleIntroCutscenes(s32 selected);
extern void File_ToggleBlueWarps(s32 selected);
extern void File_ToggleMasterQuest(s32 selected);

typedef enum {
    FILE_GOLD_SKULLTULAS,
    FILE_CALL_NAVI,
    FILE_EPONA_FREED,
    FILE_CARPENTERS_FREED,
    FILE_INTRO_CUTSCENES,
    FILE_BLUE_WARPS_CLEARED,
    FILE_MASTER_QUEST,
} FileOptions;
