#include "menu.h"
#include "menus/warps.h"
#include "draw.h"
#include "input.h"
#include "menus/commands.h"
#include "z3D/z3D.h"
#include "z3D/entrances.h"
#include <stdio.h>

static u8 sceneSetupOverrideActive = 0;

Menu WarpsMenu = {
    "Warps",
    .nbItems = 4,
    {
        {"Places", METHOD, .method = WarpsPlacesMenuShow},
        {"Manually Enter Entrance Index", METHOD, .method = ManuallyEnterEntranceIndex},
        {"Clear CS Pointer", METHOD, .method = ClearCutscenePointer},
        {"Override Game Mode & Scene Setup", METHOD, .method = WarpsOverridesMenuShow},
    }
};

AmountMenu WarpsOverridesMenu = {
    "Warps Overrides",
    .nbItems = 2,
    {
        {0, 0,  6, "Game Mode", .method = Warps_OverrideGameMode},
        {0, 0, 14, "Scene Setup Index - Override OFF", .method = Warps_OverrideSceneSetupIndex},
    }
};

WarpsSceneMenu WarpsPlacesDungeonsMenu = {
    "Dungeons",
    .nbItems = 17,
    {
        {"0: Inside the Deku Tree", &Entrances_InsideTheDekuTree},
        {"1: Dodongo's Cavern", &Entrances_DodongosCavern},
        {"2: Inside Jabu-Jabu's Belly", &Entrances_InsideJabuJabusBelly},
        {"3: Forest Temple", &Entrances_ForestTemple},
        {"4: Fire Temple", &Entrances_FireTemple},
        {"5: Water Temple", &Entrances_WaterTemple},
        {"6: Spirit Temple", &Entrances_SpiritTemple},
        {"7: Shadow Temple", &Entrances_ShadowTemple},
        {"8: Bottom of the Well", &Entrances_BottomOfTheWell},
        {"9: Ice Cavern", &Entrances_IceCavern},
        {"10: Ganon's Tower", &Entrances_GanonsTower},
        {"11: Gerudo Training Ground", &Entrances_GerudoTrainingGround},
        {"12: Thieves' Hideout", &Entrances_ThievesHideout},
        {"13: Inside Ganon's Castle", &Entrances_InsideGanonsCastle},
        {"14: Ganon's Tower (Collapsing)", &Entrances_GanonsTowerCollapsing},
        {"15: Inside Ganon's Castle (Collapsing)", &Entrances_InsideGanonsCastleCollapsing},
        {"26: Ganon's Tower Exterior (Collapsing)", &Entrances_GanonsTowerExterior},
    }
};

WarpsSceneMenu WarpsPlacesBossesMenu = {
    "Bosses",
    .nbItems = 10,
    {
        {"17: Gohma", &Entrances_GohmasLair},
        {"18: King Dodongo", &Entrances_KingDodongosLair},
        {"19: Barinade", &Entrances_BarinadesLair},
        {"20: Phantom Ganon", &Entrances_PhantomGanonsLair},
        {"21: Volvagia", &Entrances_VolvagiasLair},
        {"22: Morpha", &Entrances_MorphasLair},
        {"23: Twinrova", &Entrances_TwinrovasLair},
        {"24: Bongo Bongo", &Entrances_BongoBongosLair},
        {"25: Ganondorf", &Entrances_GanondorfsLair},
        {"79: Ganon", &Entrances_GanonsBattleArena},
    }
};

WarpsSceneMenu WarpsPlacesTownsMenu = {
    "Towns",
    .nbItems = 9,
    {
        {"82: Kakariko Village", &Entrances_KakarikoVillage},
        {"85: Kokiri Forest", &Entrances_KokiriForest},
        {"88: Zora's Domain", &Entrances_ZorasDomain},
        {"98: Goron City", &Entrances_GoronCity},
        {"99: Lon Lon Ranch", &Entrances_LonLonRanch},
        {"32: Market", &Entrances_Market},
        // {"34: Market (Ruins)", NULL}, //TODO: figure out how to handle this
        {"27: Market Entrance", &Entrances_MarketEntrance},
        {"30: Back Alley", &Entrances_BackAlley},
        {"35: Temple of Time Exterior", &Entrances_TempleOfTimeExterior},
    }
};

WarpsSceneMenu WarpsPlacesHousesMenu = {
    "Houses",
    .nbItems = 15,
    {
        {"52: Link's House", &Entrances_LinksHouse},
        {"38: Know-It-All Brothers' House", &Entrances_KnowItAllBrothersHouse},
        {"39: House of Twins", &Entrances_HouseOfTwins},
        {"40: Mido's House", &Entrances_MidosHouse},
        {"41: Saria's House", &Entrances_SariasHouse},
        {"42: Carpenter Boss's House", &Entrances_CarpenterBosssHouse},
        {"43: Back Alley House (Man in Green)", &Entrances_BackAlleyHouseManInGreen},
        {"53: Richard's House", &Entrances_BackAlleyHouseDogLady},
        {"54: Stable", &Entrances_Stable},
        {"55: Impa's House", &Entrances_ImpasHouse},
        {"57: Carpenters' Tent", &Entrances_CarpentersTent},
        {"58: Gravekeeper's Hut", &Entrances_GravekeepersHut},
        {"76: Ranch Buildings", &Entrances_RanchHouse},
        {"77: Guard House / Ghost Shop", &Entrances_GuardHouse},
        {"80: House of Skulltula", &Entrances_HouseOfSkulltula},
    }
};

WarpsSceneMenu WarpsPlacesShopsMenu = {
    "Shops",
    .nbItems = 12,
    {
        {"44: Bazaar", &Entrances_Bazaar},
        {"45: Kokiri Shop", &Entrances_KokiriShop},
        {"46: Goron Shop", &Entrances_GoronShop},
        {"47: Zora Shop", &Entrances_ZoraShop},
        {"48: Kakariko Potion Shop", &Entrances_KakarikoPotionShop},
        {"49: Market Potion Shop", &Entrances_MarketPotionShop},
        {"50: Bombchu Shop", &Entrances_BombchuShop},
        {"51: Happy Mask Shop", &Entrances_HappyMaskShop},
        {"66: Shooting Gallery", &Entrances_ShootingGallery},
        {"75: Bombchu Bowling Alley", &Entrances_BombchuBowlingAlley},
        {"78: Granny's Potion Shop", &Entrances_GrannysPotionShop},
        {"16: Treasure Chest Shop", &Entrances_TreasureBoxShop},
    }
};

WarpsSceneMenu WarpsPlacesMiscMenu = {
    "Misc",
    .nbItems = 14,
    {
        {"67: Temple of Time", &Entrances_TempleOfTime},
        {"74: Zelda's Courtyard", &Entrances_CastleCourtyard},
        {"72: Dampe's Grave / Windmill", &Entrances_Windmill},
        {"69: Castle Hedge Maze", &Entrances_CastleHeadgeMaze},
        {"56: Lakeside Laboratory", &Entrances_LakesideLaboratory},
        {"59: Great Fairy's Fountain (Upgrades)", &Entrances_GreatFairysFountainUpgrades},
        {"61: Great Fairy's Fountain (Spells)", &Entrances_GreatFairysFountainSpells},
        {"65: Royal Family's Tomb", &Entrances_RoyalFamilysTomb},
        {"62: Grottos", &Entrances_Grottos},
        {"63: Grave (Redead)", &Entrances_GraveRedead},
        {"64: Grave (Fairy's Fountain)", &Entrances_GraveFairysFountain},
        {"68: Chamber of the Sages", &Entrances_ChamberOfTheSages},
        {"71: Cutscene Map", &Entrances_CutsceneMap},
        {"60: Fairy's Fountain", &Entrances_FairysFountain},
    }
};

WarpsSceneMenu WarpsPlacesOverworldMenu = {
    "Overworld",
    .nbItems = 15,
    {
        {"81: Hyrule Field", &Entrances_HyruleField},
        {"91: Lost Woods", &Entrances_LostWoods},
        {"86: Sacred Forest Meadow", &Entrances_SacredForestMeadow},
        {"96: Death Mountain Trail", &Entrances_DeathMountainTrail},
        {"97: Death Mountain Crater", &Entrances_DeathMountainCrater},
        {"84: Zora's River", &Entrances_ZorasRiver},
        {"89: Zora's Fountain", &Entrances_ZorasFountain},
        {"87: Lake Hylia", &Entrances_LakeHylia},
        {"95: Hyrule Castle / Ganon's Castle Exterior", &Entrances_HyruleCastleGanonsCastleExterior},
        // {"100: Ganon's Castle Exterior", NULL}, //TODO: how to do this
        {"90: Gerudo Valley", &Entrances_GerudoValley},
        {"93: Gerudo's Fortress", &Entrances_GerudosFortress},
        {"94: Haunted Wasteland", &Entrances_HauntedWasteland},
        {"92: Desert Colossus", &Entrances_DesertColossus},
        {"83: Graveyard", &Entrances_Graveyard},
        {"73: Fishing Pond", &Entrances_FishingPond},
    }
};

const WarpsPlacesMenuEntry placesMenuEntries[] = {
    {"Dungeons", &WarpsPlacesDungeonsMenu},
    {"Bosses", &WarpsPlacesBossesMenu},
    {"Towns", &WarpsPlacesTownsMenu},
    {"Houses", &WarpsPlacesHousesMenu},
    {"Shops", &WarpsPlacesShopsMenu},
    {"Misc", &WarpsPlacesMiscMenu},
    {"Overworld", &WarpsPlacesOverworldMenu},
};

const s32 WarpsPlacesMenuSize = 7;

void WarpsPlacesMenuShow(void){
    s32 selected = 0;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Places");

        for (s32 i = 0; i < WarpsPlacesMenuSize; ++i)
        {

            Draw_DrawString(30, 30 + i * SPACING_Y, COLOR_WHITE, placesMenuEntries[i].title);
            Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, i == selected ? '>' : ' ');
        }

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);
        if(pressed & BUTTON_B)
            break;
        if(pressed & BUTTON_A)
        {
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();

            WarpsSceneMenuShow(placesMenuEntries[selected].menu);

            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
        }
        else if(pressed & BUTTON_DOWN)
        {
            selected++;
        }
        else if(pressed & BUTTON_UP)
        {
            selected--;
        }

        if(selected < 0)
            selected = WarpsPlacesMenuSize - 1;
        else if(selected >= WarpsPlacesMenuSize) selected = 0;

    } while(menuOpen);
}

void ManuallyEnterEntranceIndex(void){
    EntranceSelectMenuShow(&Entrances_Empty, 1);
}

void ClearCutscenePointer(void){
    static u32 nullCS[] = { 0, 0 };
    gGlobalContext->csCtx.segment = &nullCS;
}

void Warps_OverridesMenuInit(void){
    WarpsOverridesMenu.items[WARPS_GAME_MODE].amount = gSaveContext.gameMode;
    if(!sceneSetupOverrideActive) {
        WarpsOverridesMenu.items[WARPS_SCENE_SETUP_INDEX].amount = gSaveContext.sceneSetupIndex;
    }
}

void WarpsOverridesMenuShow(void){
    Warps_OverridesMenuInit();
    AmountMenuShow(&WarpsOverridesMenu);
}

void Warps_OverrideGameMode(s32 selected){
    gSaveContext.gameMode = WarpsOverridesMenu.items[WARPS_GAME_MODE].amount;
}

void Warps_OverrideSceneSetupIndex(s32 selected) {
    gSaveContext.sceneSetupIndex = WarpsOverridesMenu.items[WARPS_SCENE_SETUP_INDEX].amount;
    if (ADDITIONAL_FLAG_BUTTON) {
        sceneSetupOverrideActive = 1;
        WarpsOverridesMenu.items[WARPS_SCENE_SETUP_INDEX].title = "Scene Setup Index - Override ON ";
    } else {
        sceneSetupOverrideActive = 0;
        WarpsOverridesMenu.items[WARPS_SCENE_SETUP_INDEX].title = "Scene Setup Index - Override OFF";
    }
}

void Warps_OverrideSceneSetup(void){
    if(sceneSetupOverrideActive) {
        gSaveContext.sceneSetupIndex = WarpsOverridesMenu.items[WARPS_SCENE_SETUP_INDEX].amount;
    }
}
