#pragma once

#include "menu.h"

extern ToggleMenu FileMenu;

void File_ShowFileMenu(void);
void File_ShowTimersMenu(s32 selected);

extern void File_ToggleSkulltulaFlags(s32 selected);
extern void File_ToggleItemDropsFlags(s32 selected);
extern void File_CallNavi(s32 selected);
extern void File_ToggleEponaFreed(s32 selected);
extern void File_ToggleCarpentersFreed(s32 selected);
extern void File_ToggleIntroCutscenes(s32 selected);
extern void File_ToggleBlueWarps(s32 selected);
extern void File_ToggleMasterQuest(s32 selected);
extern void File_SetTimerStateAndValue(s32 selected);

typedef enum {
    FILE_GOLD_SKULLTULAS,
    FILE_ITEM_DROPS,
    FILE_CALL_NAVI,
    FILE_EPONA_FREED,
    FILE_CARPENTERS_FREED,
    FILE_INTRO_CUTSCENES,
    FILE_BLUE_WARPS_CLEARED,
    FILE_TIMERS,
    FILE_MASTER_QUEST,
} FileOptions;

typedef enum {
    FILE_TIMER1STATE,
    FILE_TIMER1VALUE,
    FILE_TIMER2STATE,
    FILE_TIMER2VALUE,
} TimersOptions;
