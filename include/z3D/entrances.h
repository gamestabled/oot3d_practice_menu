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
    EntrancesByScene* entrances;
} WarpsSceneMenuEntry;

typedef struct SceneMenu {
    const char* title;

    u32 nbItems;
    WarpsSceneMenuEntry scenes[0x20];
} WarpsSceneMenu;

typedef struct WarpsPlacesMenuEntry {
    const char* title;
    WarpsSceneMenu* menu;
} WarpsPlacesMenuEntry;

void EntranceSelectMenuShow(EntrancesByScene* entrances);
void EntranceWarp(u16 EntranceIndex, s32 chosenAge, s32 cutsceneIndex);
void WarpsSceneMenuShow(WarpsSceneMenu* menu);

void ManuallyEnterEntranceIndex(void);

extern EntrancesByScene Entrances_BackAlley;
extern EntrancesByScene Entrances_BackAlleyHouseDogLady;
extern EntrancesByScene Entrances_BackAlleyHouseManInGreen;
extern EntrancesByScene Entrances_BarinadesLair;
extern EntrancesByScene Entrances_Bazaar;
extern EntrancesByScene Entrances_BombchuBowlingAlley;
extern EntrancesByScene Entrances_BombchuShop;
extern EntrancesByScene Entrances_BongoBongosLair;
extern EntrancesByScene Entrances_BottomOfTheWell;
extern EntrancesByScene Entrances_CarpenterBosssHouse;
extern EntrancesByScene Entrances_CarpentersTent;
extern EntrancesByScene Entrances_CastleCourtyard;
extern EntrancesByScene Entrances_CastleHeadgeMaze;
extern EntrancesByScene Entrances_ChamberOfTheSages;
extern EntrancesByScene Entrances_CutsceneMap;
extern EntrancesByScene Entrances_DeathMountainCrater;
extern EntrancesByScene Entrances_DeathMountainTrail;
extern EntrancesByScene Entrances_DesertColossus;
extern EntrancesByScene Entrances_DodongosCavern;
extern EntrancesByScene Entrances_FairysFountain;
extern EntrancesByScene Entrances_FireTemple;
extern EntrancesByScene Entrances_FishingPond;
extern EntrancesByScene Entrances_ForestTemple;
extern EntrancesByScene Entrances_GanonsTower;
extern EntrancesByScene Entrances_GanonsTowerCollapsing;
extern EntrancesByScene Entrances_GanonsBattleArena;
extern EntrancesByScene Entrances_GanonsTowerExterior;
extern EntrancesByScene Entrances_GanondorfsLair;
extern EntrancesByScene Entrances_GerudoTrainingGround;
extern EntrancesByScene Entrances_GerudoValley;
extern EntrancesByScene Entrances_GerudosFortress;
extern EntrancesByScene Entrances_GohmasLair;
extern EntrancesByScene Entrances_GoronCity;
extern EntrancesByScene Entrances_GoronShop;
extern EntrancesByScene Entrances_GrannysPotionShop;
extern EntrancesByScene Entrances_GraveFairysFountain;
extern EntrancesByScene Entrances_GraveRedead;
extern EntrancesByScene Entrances_GravekeepersHut;
extern EntrancesByScene Entrances_Graveyard;
extern EntrancesByScene Entrances_GreatFairysFountainSpells;
extern EntrancesByScene Entrances_GreatFairysFountainUpgrades;
extern EntrancesByScene Entrances_Grottos;
extern EntrancesByScene Entrances_GuardHouse;
extern EntrancesByScene Entrances_HappyMaskShop;
extern EntrancesByScene Entrances_HauntedWasteland;
extern EntrancesByScene Entrances_HouseOfTwins;
extern EntrancesByScene Entrances_HouseOfSkulltula;
extern EntrancesByScene Entrances_HyruleCastleGanonsCastleExterior;
extern EntrancesByScene Entrances_HyruleField;
extern EntrancesByScene Entrances_IceCavern;
extern EntrancesByScene Entrances_ImpasHouse;
extern EntrancesByScene Entrances_InsideGanonsCastle;
extern EntrancesByScene Entrances_InsideGanonsCastleCollapsing;
extern EntrancesByScene Entrances_InsideJabuJabusBelly;
extern EntrancesByScene Entrances_InsideTheDekuTree;
extern EntrancesByScene Entrances_KakarikoPotionShop;
extern EntrancesByScene Entrances_KakarikoVillage;
extern EntrancesByScene Entrances_KingDodongosLair;
extern EntrancesByScene Entrances_KnowItAllBrothersHouse;
extern EntrancesByScene Entrances_KokiriForest;
extern EntrancesByScene Entrances_KokiriShop;
extern EntrancesByScene Entrances_LakeHylia;
extern EntrancesByScene Entrances_LakesideLaboratory;
extern EntrancesByScene Entrances_LinksHouse;
extern EntrancesByScene Entrances_LonLonRanch;
extern EntrancesByScene Entrances_LostWoods;
extern EntrancesByScene Entrances_Market;
extern EntrancesByScene Entrances_MarketEntrance;
extern EntrancesByScene Entrances_MarketPotionShop;
extern EntrancesByScene Entrances_MidosHouse;
extern EntrancesByScene Entrances_MorphasLair;
extern EntrancesByScene Entrances_NaboorusMiniBossRoom;
extern EntrancesByScene Entrances_PhantomGanonsLair;
extern EntrancesByScene Entrances_RanchHouse;
extern EntrancesByScene Entrances_RoyalFamilysTomb;
extern EntrancesByScene Entrances_SacredForestMeadow;
extern EntrancesByScene Entrances_SariasHouse;
extern EntrancesByScene Entrances_ShadowTemple;
extern EntrancesByScene Entrances_ShootingGallery;
extern EntrancesByScene Entrances_Stable;
extern EntrancesByScene Entrances_SpiritTemple;
extern EntrancesByScene Entrances_TempleOfTime;
extern EntrancesByScene Entrances_TempleOfTimeExterior;
extern EntrancesByScene Entrances_ThievesHideout;
extern EntrancesByScene Entrances_TreasureBoxShop;
extern EntrancesByScene Entrances_TwinrovasLair;
extern EntrancesByScene Entrances_VolvagiasLair;
extern EntrancesByScene Entrances_WaterTemple;
extern EntrancesByScene Entrances_Windmill;
extern EntrancesByScene Entrances_ZoraShop;
extern EntrancesByScene Entrances_ZorasDomain;
extern EntrancesByScene Entrances_ZorasFountain;
extern EntrancesByScene Entrances_ZorasRiver;
