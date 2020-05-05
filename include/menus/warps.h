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

enum {
    Manual_Entrance_Menu_Age,
    Manual_Entrance_Menu_Time,
    Manual_Entrance_Menu_CsIdx,
    Manual_Entrance_Menu_EtcIdx,
    Manual_Entrance_Menu_Go,
};