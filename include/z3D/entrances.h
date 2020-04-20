#pragma once

#include "z3D/z3D.h"

typedef struct EntrancesBySceneEntry {
    u16 entranceIndex;
    const char* title;
} EntrancesBySceneEntry;

typedef struct EntrancesByScene {
    const char* title;

    u32 nbItems;
    EntrancesBySceneEntry items[0x10];
} EntrancesByScene;

void EntranceSelectMenuShow(EntrancesByScene* entrances);
void EntranceWarp(u16 EntranceIndex, s32 chosenAge, s32 cutsceneIndex);

EntrancesByScene Entrances_BackAlley;
EntrancesByScene Entrances_BackAlleyHouseDogLady;
EntrancesByScene Entrances_BackAlleyHouseManInGreen;
EntrancesByScene Entrances_BarinadesLair;
EntrancesByScene Entrances_BombchuBowlingAlley;
EntrancesByScene Entrances_BombchuShop;
EntrancesByScene Entrances_BottomOfTheWell;
EntrancesByScene Entrances_CarpenterBosssHouse;
EntrancesByScene Entrances_CarpentersTent;
EntrancesByScene Entrances_CastleCourtyard;
EntrancesByScene Entrances_CastleHeadgeMaze;
EntrancesByScene Entrances_ChamberOfTheSages;
EntrancesByScene Entrances_CutsceneMap;
EntrancesByScene Entrances_DeathMountainCrater;
EntrancesByScene Entrances_DeathMountainTrail;
EntrancesByScene Entrances_DesertColossus;
EntrancesByScene Entrances_DodongosCavern;
EntrancesByScene Entrances_FireTemple;
EntrancesByScene Entrances_ForestTemple;
EntrancesByScene Entrances_GanonsTower;
EntrancesByScene Entrances_GanonsTowerCollapsing;
EntrancesByScene Entrances_GanonsTowerExterior;
EntrancesByScene Entrances_GerudoValley;
EntrancesByScene Entrances_GerudosFortress;
EntrancesByScene Entrances_GoronCity;
EntrancesByScene Entrances_Graveyard;
EntrancesByScene Entrances_GreatFairysFountainSpells;
EntrancesByScene Entrances_GreatFairysFountainUpgrades;
EntrancesByScene Entrances_Grottos;
EntrancesByScene Entrances_HauntedWasteland;
EntrancesByScene Entrances_HyruleCastleGanonsCastleExterior;
EntrancesByScene Entrances_HyruleField;
EntrancesByScene Entrances_IceCavern;
EntrancesByScene Entrances_ImpasHouse;
EntrancesByScene Entrances_InsideGanonsCastle;
EntrancesByScene Entrances_InsideGanonsCastleCollapsing;
EntrancesByScene Entrances_InsideJabuJabusBelly;
EntrancesByScene Entrances_InsideTheDekuTree;
EntrancesByScene Entrances_KakarikoPotionShop;
EntrancesByScene Entrances_KakarikoShootingGallery;
EntrancesByScene Entrances_KakarikoVillage;
EntrancesByScene Entrances_KokiriForest;
EntrancesByScene Entrances_LakeHylia;
EntrancesByScene Entrances_LakesideLaboratory;
EntrancesByScene Entrances_LinksHouse;
EntrancesByScene Entrances_LonLonRanch;
EntrancesByScene Entrances_LostWoods;
EntrancesByScene Entrances_Market;
EntrancesByScene Entrances_MarketEntrance;
EntrancesByScene Entrances_RanchHouse;
EntrancesByScene Entrances_RoyalFamilysTomb;
EntrancesByScene Entrances_SacredForestMeadow;
EntrancesByScene Entrances_ShadowTemple;
EntrancesByScene Entrances_SpiritTemple;
EntrancesByScene Entrances_TempleOfTime;
EntrancesByScene Entrances_TempleOfTimeExterior;
EntrancesByScene Entrances_ThievesHideout;
EntrancesByScene Entrances_WaterTemple;
EntrancesByScene Entrances_Windmill;
EntrancesByScene Entrances_ZorasDomain;
EntrancesByScene Entrances_ZorasFountain;
EntrancesByScene Entrances_ZorasRiver;