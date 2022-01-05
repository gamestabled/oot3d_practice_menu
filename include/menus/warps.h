#pragma once

#include "menu.h"
#include "z3D/entrances.h"

extern Menu WarpsMenu;
extern Menu WarpsPlacesMenu;
extern WarpsSceneMenu WarpsPlacesDungeonsMenu;
extern WarpsSceneMenu WarpsPlacesBossesMenu;
extern WarpsSceneMenu WarpsPlacesTownsMenu;
extern WarpsSceneMenu WarpsPlacesHousesMenu;
extern WarpsSceneMenu WarpsPlacesShopsMenu;
extern WarpsSceneMenu WarpsPlacesMiscMenu;
extern WarpsSceneMenu WarpsPlacesOverworldMenu;

void WarpsPlacesMenuShow(void);
void ClearCutscenePointer(void);
void WarpsOverridesMenuShow(void);
void Warps_OverrideGameMode(s32 selected);
void Warps_OverrideSceneSetupIndex(s32 selected);
void Warps_SetRespawnFlag(s32 selected);

typedef enum {
    WARPS_GAME_MODE,
    WARPS_SCENE_SETUP_INDEX,
    WARPS_RESPAWN_FLAG,
} WarpsOverrides;
