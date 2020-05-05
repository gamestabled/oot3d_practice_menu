#pragma once

#include "z3D/z3D.h"

typedef struct EntrancesBySceneEntry {
    u16 entranceIndex;
    const char* title;
} EntrancesBySceneEntry;

typedef struct EntrancesByScene {
    const char* title;

    u32 nbItems;
    EntrancesBySceneEntry items[0x20];
} EntrancesByScene;

typedef struct SceneMenuEntry {
    const char* title;
    const EntrancesByScene* entrances;
} WarpsSceneMenuEntry;

typedef struct SceneMenu {
    const char* title;

    u32 nbItems;
    WarpsSceneMenuEntry scenes[0x20];
} WarpsSceneMenu;

typedef struct WarpsPlacesMenuEntry {
    const char* title;
    const WarpsSceneMenu* menu;
} WarpsPlacesMenuEntry;

void EntranceSelectMenuShow(const EntrancesByScene* entrances);
void EntranceWarp(u16 EntranceIndex, s32 chosenAge, s32 cutsceneIndex, u32 chosenTimeIndex);
void WarpsSceneMenuShow(const WarpsSceneMenu* menu);

void ManuallyEnterEntranceIndex(void);

extern const EntrancesByScene Entrances_BackAlley;
extern const EntrancesByScene Entrances_BackAlleyHouseDogLady;
extern const EntrancesByScene Entrances_BackAlleyHouseManInGreen;
extern const EntrancesByScene Entrances_BarinadesLair;
extern const EntrancesByScene Entrances_Bazaar;
extern const EntrancesByScene Entrances_BombchuBowlingAlley;
extern const EntrancesByScene Entrances_BombchuShop;
extern const EntrancesByScene Entrances_BongoBongosLair;
extern const EntrancesByScene Entrances_BottomOfTheWell;
extern const EntrancesByScene Entrances_CarpenterBosssHouse;
extern const EntrancesByScene Entrances_CarpentersTent;
extern const EntrancesByScene Entrances_CastleCourtyard;
extern const EntrancesByScene Entrances_CastleHeadgeMaze;
extern const EntrancesByScene Entrances_ChamberOfTheSages;
extern const EntrancesByScene Entrances_CutsceneMap;
extern const EntrancesByScene Entrances_DeathMountainCrater;
extern const EntrancesByScene Entrances_DeathMountainTrail;
extern const EntrancesByScene Entrances_DesertColossus;
extern const EntrancesByScene Entrances_DodongosCavern;
extern const EntrancesByScene Entrances_FairysFountain;
extern const EntrancesByScene Entrances_FireTemple;
extern const EntrancesByScene Entrances_FishingPond;
extern const EntrancesByScene Entrances_ForestTemple;
extern const EntrancesByScene Entrances_GanonsTower;
extern const EntrancesByScene Entrances_GanonsTowerCollapsing;
extern const EntrancesByScene Entrances_GanonsBattleArena;
extern const EntrancesByScene Entrances_GanonsTowerExterior;
extern const EntrancesByScene Entrances_GanondorfsLair;
extern const EntrancesByScene Entrances_GerudoTrainingGround;
extern const EntrancesByScene Entrances_GerudoValley;
extern const EntrancesByScene Entrances_GerudosFortress;
extern const EntrancesByScene Entrances_GohmasLair;
extern const EntrancesByScene Entrances_GoronCity;
extern const EntrancesByScene Entrances_GoronShop;
extern const EntrancesByScene Entrances_GrannysPotionShop;
extern const EntrancesByScene Entrances_GraveFairysFountain;
extern const EntrancesByScene Entrances_GraveRedead;
extern const EntrancesByScene Entrances_GravekeepersHut;
extern const EntrancesByScene Entrances_Graveyard;
extern const EntrancesByScene Entrances_GreatFairysFountainSpells;
extern const EntrancesByScene Entrances_GreatFairysFountainUpgrades;
extern const EntrancesByScene Entrances_Grottos;
extern const EntrancesByScene Entrances_GuardHouse;
extern const EntrancesByScene Entrances_HappyMaskShop;
extern const EntrancesByScene Entrances_HauntedWasteland;
extern const EntrancesByScene Entrances_HouseOfTwins;
extern const EntrancesByScene Entrances_HouseOfSkulltula;
extern const EntrancesByScene Entrances_HyruleCastleGanonsCastleExterior;
extern const EntrancesByScene Entrances_HyruleField;
extern const EntrancesByScene Entrances_IceCavern;
extern const EntrancesByScene Entrances_ImpasHouse;
extern const EntrancesByScene Entrances_InsideGanonsCastle;
extern const EntrancesByScene Entrances_InsideGanonsCastleCollapsing;
extern const EntrancesByScene Entrances_InsideJabuJabusBelly;
extern const EntrancesByScene Entrances_InsideTheDekuTree;
extern const EntrancesByScene Entrances_KakarikoPotionShop;
extern const EntrancesByScene Entrances_KakarikoVillage;
extern const EntrancesByScene Entrances_KingDodongosLair;
extern const EntrancesByScene Entrances_KnowItAllBrothersHouse;
extern const EntrancesByScene Entrances_KokiriForest;
extern const EntrancesByScene Entrances_KokiriShop;
extern const EntrancesByScene Entrances_LakeHylia;
extern const EntrancesByScene Entrances_LakesideLaboratory;
extern const EntrancesByScene Entrances_LinksHouse;
extern const EntrancesByScene Entrances_LonLonRanch;
extern const EntrancesByScene Entrances_LostWoods;
extern const EntrancesByScene Entrances_Market;
extern const EntrancesByScene Entrances_MarketEntrance;
extern const EntrancesByScene Entrances_MarketPotionShop;
extern const EntrancesByScene Entrances_MidosHouse;
extern const EntrancesByScene Entrances_MorphasLair;
extern const EntrancesByScene Entrances_NaboorusMiniBossRoom;
extern const EntrancesByScene Entrances_PhantomGanonsLair;
extern const EntrancesByScene Entrances_RanchHouse;
extern const EntrancesByScene Entrances_RoyalFamilysTomb;
extern const EntrancesByScene Entrances_SacredForestMeadow;
extern const EntrancesByScene Entrances_SariasHouse;
extern const EntrancesByScene Entrances_ShadowTemple;
extern const EntrancesByScene Entrances_ShootingGallery;
extern const EntrancesByScene Entrances_Stable;
extern const EntrancesByScene Entrances_SpiritTemple;
extern const EntrancesByScene Entrances_TempleOfTime;
extern const EntrancesByScene Entrances_TempleOfTimeExterior;
extern const EntrancesByScene Entrances_ThievesHideout;
extern const EntrancesByScene Entrances_TreasureBoxShop;
extern const EntrancesByScene Entrances_TwinrovasLair;
extern const EntrancesByScene Entrances_VolvagiasLair;
extern const EntrancesByScene Entrances_WaterTemple;
extern const EntrancesByScene Entrances_Windmill;
extern const EntrancesByScene Entrances_ZoraShop;
extern const EntrancesByScene Entrances_ZorasDomain;
extern const EntrancesByScene Entrances_ZorasFountain;
extern const EntrancesByScene Entrances_ZorasRiver;

enum {
    Entrance_Select_Menu_Age,
    Entrance_Select_Menu_Time,
    Entrance_Select_Menu_CsIdx,
    Entrance_Select_Menu_Etcs,
};
