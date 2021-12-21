#include "menu.h"
#include "menus/warps.h"
#include "draw.h"
#include "input.h"
#include "menus/commands.h"
#include "z3D/z3D.h"
#include "z3D/entrances.h"
#include <stdio.h>

Menu WarpsMenu = {
    "Warps",
    .nbItems = 3,
    {
        {"Places", METHOD, .method = WarpsPlacesMenuShow},
        {"Manually Enter Entrance Index", METHOD, .method = ManuallyEnterEntranceIndex},
        {"Clear CS Pointer", METHOD, .method = ClearCutscenePointer},
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
        {"12: Thieve's Hideout", &Entrances_ThievesHideout},
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
        {"17: Gohma's Lair", &Entrances_GohmasLair},
        {"18: King Dodongo's Lair", &Entrances_KingDodongosLair},
        {"19: Barinade's Lair", &Entrances_BarinadesLair},
        {"20: Phantom Ganon's Lair", &Entrances_PhantomGanonsLair},
        {"21: Volvagia's Lair", &Entrances_VolvagiasLair},
        {"22: Morpha's Lair", &Entrances_MorphasLair},
        {"23: Twinrova's Lair & Nabooru's Mini-Boss Room", &Entrances_TwinrovasLair},
        {"24: Bongo Bongo's Lair", &Entrances_BongoBongosLair},
        {"25: Ganondorf's Lair", &Entrances_GanondorfsLair},
        {"79: Ganon's Tower Collapse & Battle Arena", &Entrances_GanonsBattleArena},
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
        {"53: Back Alley House (Dog Lady)", &Entrances_BackAlleyHouseDogLady},
        {"54: Stable", &Entrances_Stable},
        {"55: Impa's House", &Entrances_ImpasHouse},
        {"57: Carpenters' Tent", &Entrances_CarpentersTent},
        {"58: Gravekeeper's Hut", &Entrances_GravekeepersHut},
        {"76: Ranch House & Silo", &Entrances_RanchHouse},
        {"77: Guard House", &Entrances_GuardHouse},
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
        {"16: Treasure Box Shop", &Entrances_TreasureBoxShop},
    }
};

WarpsSceneMenu WarpsPlacesMiscMenu = {
    "Misc",
    .nbItems = 14,
    {
        {"67: Temple of Time", &Entrances_TempleOfTime},
        {"74: Castle Courtyard", &Entrances_CastleCourtyard},
        {"72: Dampe's Grace & Windmill", &Entrances_Windmill},
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

static const char* TimeNames[] = {
    "Current ",
    "Midnight",
    "6 AM    ",
    "Noon    ",
    "6 PM    ",
};

void ManuallyEnterEntranceIndex(void){
    s32 selected = 0;
    s32 chosenAge = gSaveContext.linkAge;
    u32 chosenTime = 0;
    u16 chosenIndex = 0x0000;
    u32 curColor = COLOR_WHITE;
    s32 cutsceneIndex = -1;
    u32 chosen = 0;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Manually Enter Entrance Index");

        Draw_DrawFormattedString(30, 30, COLOR_WHITE, "Age on Load: %s", chosenAge ? "Child" : "Adult");
        Draw_DrawCharacter(10, 30, COLOR_TITLE, selected == Manual_Entrance_Menu_Age ? '>' : ' ');

        Draw_DrawFormattedString(30, 30 + SPACING_Y * Manual_Entrance_Menu_Time, COLOR_WHITE, "Time of Day: %s", TimeNames[chosenTime]);
        Draw_DrawCharacter(10, 30 + SPACING_Y * Manual_Entrance_Menu_Time, COLOR_TITLE, selected == Manual_Entrance_Menu_Time ? '>' : ' ');

        if (cutsceneIndex < 0){
            cutsceneIndex = -1;
            Draw_DrawString(30, 30 + SPACING_Y * Manual_Entrance_Menu_CsIdx, selected == 1 ? curColor : COLOR_WHITE, "Cutscene Number on Load: None");
        }
        else {
            Draw_DrawFormattedString(30, 30 + SPACING_Y * Manual_Entrance_Menu_CsIdx,
                selected == Manual_Entrance_Menu_CsIdx ? curColor : COLOR_WHITE, "Cutscene Number on Load: %04d", cutsceneIndex);
        }
        Draw_DrawCharacter(10, 30 + SPACING_Y * Manual_Entrance_Menu_CsIdx, COLOR_TITLE, selected == Manual_Entrance_Menu_CsIdx ? '>' : ' ');

        Draw_DrawFormattedString(30, 30 + SPACING_Y * Manual_Entrance_Menu_EtcIdx, selected == Manual_Entrance_Menu_EtcIdx ? curColor : COLOR_WHITE,
            "Entrance Index: 0x%04X", chosenIndex);
        Draw_DrawCharacter(10, 30 + SPACING_Y * Manual_Entrance_Menu_EtcIdx, COLOR_TITLE, selected == Manual_Entrance_Menu_EtcIdx ? '>' : ' ');

        Draw_DrawString(30, 30 + SPACING_Y * Manual_Entrance_Menu_Go, COLOR_WHITE, "Go");
        Draw_DrawCharacter(10, 30 + SPACING_Y * Manual_Entrance_Menu_Go, COLOR_TITLE, selected == Manual_Entrance_Menu_Go ? '>' : ' ');

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);
        if(pressed & BUTTON_B && !chosen)
            break;
        else if(pressed & BUTTON_B && chosen)
        {
            curColor = COLOR_WHITE;
            chosen = 0;
        }
        else if(pressed & BUTTON_A && !chosen)
        {
            if(selected == Manual_Entrance_Menu_CsIdx || selected == Manual_Entrance_Menu_EtcIdx){
                chosen = 1;
                curColor = COLOR_RED;
            }
            else if(selected == Manual_Entrance_Menu_Age){
                chosenAge = 1 - chosenAge;
            }
            else if(selected == Manual_Entrance_Menu_Time){
                chosenTime++;
                chosenTime %= 5;
            }
            else if(selected == Manual_Entrance_Menu_Go){
                EntranceWarp(chosenIndex, chosenAge, cutsceneIndex, chosenTime);
                menuOpen = 0;
            }
        }
        else if(pressed & BUTTON_A && chosen)
        {
            curColor = COLOR_WHITE;
            chosen = 0;
        }
        else if(pressed & BUTTON_DOWN && !chosen)
        {
            selected++;
        }
        else if(pressed & BUTTON_DOWN && chosen && selected == Manual_Entrance_Menu_CsIdx)
        {
            cutsceneIndex--;
        }
        else if(pressed & BUTTON_DOWN && chosen && selected == Manual_Entrance_Menu_EtcIdx){
            chosenIndex--;
        }
        else if(pressed & BUTTON_UP && !chosen)
        {
            selected--;
        }
        else if(pressed & BUTTON_UP && chosen && selected == Manual_Entrance_Menu_CsIdx)
        {
            cutsceneIndex++;
        }
        else if(pressed & BUTTON_UP && chosen && selected == Manual_Entrance_Menu_EtcIdx){
            chosenIndex++;
        }
        else if(pressed & BUTTON_LEFT && chosen && selected == Manual_Entrance_Menu_CsIdx){
            cutsceneIndex -= 10;
        }
        else if(pressed & BUTTON_LEFT && chosen && selected == Manual_Entrance_Menu_EtcIdx){
            chosenIndex -= 16;
        }
        else if(pressed & BUTTON_RIGHT && chosen && selected == Manual_Entrance_Menu_CsIdx){
            cutsceneIndex += 10;
        }
        else if(pressed & BUTTON_RIGHT && chosen && selected == Manual_Entrance_Menu_EtcIdx){
            chosenIndex += 16;
        }
        if(selected < 0)
            selected = Manual_Entrance_Menu_Go;
        else if(selected > Manual_Entrance_Menu_Go) selected = Manual_Entrance_Menu_Age;

    } while(menuOpen);
}

void ClearCutscenePointer(void){
    static u32 nullCS[] = { 0, 0 };
    gGlobalContext->csCtx.segment = &nullCS;
}