#include "z3D/entrances.h"
#include "draw.h"
#include "menu.h"
#include "input.h"
#include "common.h"
#include "menus/commands.h"
#include "menus/scene.h"
#include "menus/cheats.h"
#include "z3D/z3D.h"
#include "utils.h"
#include <stdio.h>

#define ENTRANCE_MENU_MAX_SHOW 15
#define SCENE_MENU_MAX_SHOW 18

static const u16 EntranceTimes[] = {
    0xFFFF, //unused
    0x0000,
    0x4001,
    0x8000,
    0xC001,
};

static const char* TimeNames[] = {
    "Current ",
    "Midnight",
    "6 AM    ",
    "Noon    ",
    "6 PM    ",
};

static const char* AgeNames[] = {
    "Adult  ",
    "Child  ",
    "Current",
};

void EntranceWarp(u16 EntranceIndex, s32 chosenAge, s32 cutsceneIndex, u32 chosenTimeIndex){
    if (chosenTimeIndex != 0){
        gSaveContext.dayTime = frozenTime = EntranceTimes[chosenTimeIndex];
    }
    gGlobalContext->nextEntranceIndex = EntranceIndex;
    gGlobalContext->fadeOutTransition = 11;
    gGlobalContext->linkAgeOnLoad = chosenAge;
    if (cutsceneIndex == -1){ //this prevents crashes because warping with CS 0xFFEF ("None") would keep the previous CS number
        gSaveContext.cutsceneIndex = 0;
    }

    gSaveContext.nextCutsceneIndex = (cutsceneIndex == -2) ? 0 : (cutsceneIndex + 0xFFF0);

    gGlobalContext->sceneLoadFlag = 0x14;

    if(noClip) {
        Scene_NoClipToggle();
    }
}

void EntranceSelectMenuShow(const EntrancesByScene* entrances, const u8 manualSelection){
    s32 selected = 3, page = 0, pagePrev = 0;
    s32 chosenAge = 2;
    u32 chosenTime = 0;
    u16 chosenEntranceIndex = 0x0000;
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
        if (page != pagePrev)
        {
            Draw_ClearFramebuffer();
        }
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, entrances->title);

        Draw_DrawFormattedString(30, 30, COLOR_WHITE, "Age on Load: %s", AgeNames[chosenAge]);
        Draw_DrawCharacter(10, 30, COLOR_TITLE, selected == Entrance_Select_Menu_Age ? '>' : ' ');

        Draw_DrawFormattedString(30, 30 + SPACING_Y * Entrance_Select_Menu_Time, COLOR_WHITE, "Time of Day: %s", TimeNames[chosenTime]);
        Draw_DrawCharacter(10, 30 + SPACING_Y * Entrance_Select_Menu_Time, COLOR_TITLE, selected == Entrance_Select_Menu_Time ? '>' : ' ');

        if (cutsceneIndex < -1){
            cutsceneIndex = -2;
            Draw_DrawString(30, 30 + SPACING_Y * Entrance_Select_Menu_CsIdx,
                (selected == Entrance_Select_Menu_CsIdx) ? curColor : COLOR_WHITE, "Cutscene Number on Load: Forced Cleared (BiT)");
        }
        else if (cutsceneIndex == -1){
            Draw_DrawString(30, 30 + SPACING_Y * Entrance_Select_Menu_CsIdx,
                (selected == Entrance_Select_Menu_CsIdx) ? curColor : COLOR_WHITE, "Cutscene Number on Load: None                ");
        }
        else {
            Draw_DrawFormattedString(30, 30 + SPACING_Y * Entrance_Select_Menu_CsIdx,
                (selected == Entrance_Select_Menu_CsIdx) ? curColor : COLOR_WHITE, "Cutscene Number on Load: %02d                  ", cutsceneIndex);
        }
        Draw_DrawCharacter(10, 30 + SPACING_Y * Entrance_Select_Menu_CsIdx, COLOR_TITLE, selected == Entrance_Select_Menu_CsIdx ? '>' : ' ');

        for (s32 i = 0; i < ENTRANCE_MENU_MAX_SHOW && page * ENTRANCE_MENU_MAX_SHOW + i < entrances->nbItems; ++i)
        {
            s32 j = page * ENTRANCE_MENU_MAX_SHOW + i;
            Draw_DrawString(45, 30 + (Entrance_Select_Menu_Etcs + i) * SPACING_Y, COLOR_WHITE, entrances->items[j].title);
            Draw_DrawCharacter(10, 30 + (Entrance_Select_Menu_Etcs + i) * SPACING_Y, COLOR_TITLE, selected == (Entrance_Select_Menu_Etcs + j) ? '>' : ' ');
        }

        if (manualSelection) {
            Draw_DrawFormattedString(30, 30 + SPACING_Y * Entrance_Select_Menu_Etcs, selected == Entrance_Select_Menu_Etcs ? curColor : COLOR_WHITE,
                "Entrance Index: 0x%04X", chosenEntranceIndex);
            Draw_DrawCharacter(10, 30 + SPACING_Y * Entrance_Select_Menu_Etcs, COLOR_TITLE, selected == Entrance_Select_Menu_Etcs ? '>' : ' ');

            Draw_DrawString(30, 30 + SPACING_Y * Entrance_Select_Menu_Go, COLOR_WHITE, "Go");
            Draw_DrawCharacter(10, 30 + SPACING_Y * Entrance_Select_Menu_Go, COLOR_TITLE, selected == Entrance_Select_Menu_Go ? '>' : ' ');
        }

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);
        if (chosen) {
            if(pressed & (BUTTON_B | BUTTON_A)) // unselect option
            {
                curColor = COLOR_WHITE;
                chosen = 0;
                if (ADDITIONAL_FLAG_BUTTON && selected == Entrance_Select_Menu_CsIdx) {
                    gSaveContext.nextCutsceneIndex = (cutsceneIndex == -2) ? 0 : (cutsceneIndex + 0xFFF0);
                }
                else if (ADDITIONAL_FLAG_BUTTON && selected == Entrance_Select_Menu_Etcs) {
                    gGlobalContext->nextEntranceIndex = chosenEntranceIndex;
                }
            }
            else if (pressed & (BUTTON_UP | BUTTON_DOWN | BUTTON_LEFT | BUTTON_RIGHT)) // change selected value
            {
                s32 increment = 0;
                if (pressed & BUTTON_UP) increment = (pressed & BUTTON_X) ? 0x100 : 0x1;
                if (pressed & BUTTON_DOWN) increment = (pressed & BUTTON_X) ? -0x100 : -0x1;
                if (pressed & BUTTON_RIGHT) increment = (pressed & BUTTON_X) ? 0x1000 : 0x10;
                if (pressed & BUTTON_LEFT) increment = (pressed & BUTTON_X) ? -0x1000 : -0x10;

                if (selected == Entrance_Select_Menu_Etcs)
                    chosenEntranceIndex += increment;
                else if (selected == Entrance_Select_Menu_CsIdx) {
                    cutsceneIndex += increment;
                    // keep cutsceneIndex within the correct values
                    if(cutsceneIndex > 15){
                        cutsceneIndex = (ADDITIONAL_FLAG_BUTTON ? -2 : -1);
                    }
                    if(cutsceneIndex < (ADDITIONAL_FLAG_BUTTON ? -2 : -1)) {
                        cutsceneIndex = 15;
                    }
                }
            }
        } else { // not chosen
            if(pressed & BUTTON_B) // close entrances menu
            {
                break;
            }
            if(pressed & BUTTON_A) // select option
            {
                if(selected == Entrance_Select_Menu_CsIdx || (manualSelection && selected == Entrance_Select_Menu_Etcs)){
                    chosen = 1;
                    curColor = COLOR_RED;
                }
                else if(selected == Entrance_Select_Menu_Age){
                    chosenAge++;
                    chosenAge %= 3;
                }
                else if(selected == Entrance_Select_Menu_Time){
                    chosenTime++;
                    chosenTime %= 5;
                    if (ADDITIONAL_FLAG_BUTTON && chosenTime != 0){
                        gSaveContext.dayTime = frozenTime = EntranceTimes[chosenTime];
                    }
                }
                else if(selected >= Entrance_Select_Menu_Etcs){
                    s32 age;
                    switch(chosenAge) {
                        case 2: age = gGlobalContext->linkAgeOnLoad; break;
                        default: age = chosenAge; break;
                    }
                    u16 entranceIndex = manualSelection ? chosenEntranceIndex : entrances->items[selected - Entrance_Select_Menu_Etcs].entranceIndex;
                    EntranceWarp(entranceIndex, age, cutsceneIndex, chosenTime);
                    menuOpen = 0;
                }
            }
            else if(pressed & BUTTON_DOWN)
            {
                selected++;
            }
            else if(pressed & BUTTON_UP)
            {
                selected--;
            }
        }

        if(selected < 0) {
            selected = (manualSelection ? Entrance_Select_Menu_Go : (Entrance_Select_Menu_Etcs + entrances->nbItems - 1));
        }
        else if(selected > (manualSelection ? Entrance_Select_Menu_Go : (Entrance_Select_Menu_Etcs + entrances->nbItems - 1))) {
            selected = Entrance_Select_Menu_Age;
        }
        pagePrev = page;
        page = selected >= ENTRANCE_MENU_MAX_SHOW + Entrance_Select_Menu_Etcs ? 1 : 0;

        if(ADDITIONAL_FLAG_BUTTON) {
            Draw_DrawFormattedStringTop(60, 190, COLOR_WHITE, "Current Entrance: %04X", (u16)gSaveContext.entranceIndex);
            Draw_DrawFormattedStringTop(60, 200, COLOR_WHITE, "Current Cutscene: %04X", (u16)gSaveContext.cutsceneIndex);
            Draw_DrawFormattedStringTop(60, 210, COLOR_WHITE, "Next Entrance:    %04X", (u16)gGlobalContext->nextEntranceIndex);
            Draw_DrawFormattedStringTop(60, 220, COLOR_WHITE, "Next Cutscene:    %04X", (u16)gSaveContext.nextCutsceneIndex);

            // this would print the cutscene number formatted like in the options, but I think the hex value is better
            /*if (gSaveContext.nextCutsceneIndex >= 0xFFF0) {
                Draw_DrawFormattedStringTop(60, 220, COLOR_WHITE, "Next Cutscene: %02d                  ", gSaveContext.nextCutsceneIndex - 0xFFF0);
            }
            else if (gSaveContext.nextCutsceneIndex == 0) {
                Draw_DrawStringTop(60, 220, COLOR_WHITE, "Next Cutscene: Forced Cleared (BiT)");
            }
            else { // 0xFFEF, default
                Draw_DrawStringTop(60, 220, COLOR_WHITE, "Next Cutscene: None                ");
            }*/
        }
    } while(menuOpen);
}

void WarpsSceneMenuShow(const WarpsSceneMenu* menu){
    s32 selected = 0, page = 0, pagePrev = 0;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        if (page != pagePrev)
        {
            Draw_ClearFramebuffer();
        }
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, menu->title);

        for (s32 i = 0; i < SCENE_MENU_MAX_SHOW && page * SCENE_MENU_MAX_SHOW + i < menu->nbItems; ++i)
        {
            s32 j = page * SCENE_MENU_MAX_SHOW + i;
            Draw_DrawString(30, 30 + i * SPACING_Y, COLOR_WHITE, menu->scenes[j].title);
            Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, j == selected ? '>' : ' ');
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

            EntranceSelectMenuShow(menu->scenes[selected].entrances, 0);

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
        else if(pressed & BUTTON_LEFT){
            selected -= SCENE_MENU_MAX_SHOW;
        }
        else if(pressed & BUTTON_RIGHT){
            if(selected + SCENE_MENU_MAX_SHOW < menu->nbItems)
                selected += SCENE_MENU_MAX_SHOW;
            else if((menu->nbItems - 1) / SCENE_MENU_MAX_SHOW == page)
                selected %= SCENE_MENU_MAX_SHOW;
            else selected = menu->nbItems - 1;
        }

        if(selected < 0)
            selected = menu->nbItems - 1;
        else if(selected >= menu->nbItems) selected = 0;

        pagePrev = page;
        page = selected / SCENE_MENU_MAX_SHOW;
    } while(menuOpen);
}

const EntrancesByScene Entrances_Empty = {
    "Manually Enter Entrance Index",
    .nbItems = 0,
    {
    }
};

const EntrancesByScene Entrances_BackAlley = {
    "Back Alley",
    .nbItems = 5,
    {
        {0x00AD, "From Market (Right Side)"},
        {0x029A, "From Market (Left Side)"},
        {0x03C1, "From Bombchu Shop"},
        {0x0067, "From Man in Green"},
        {0x038C, "From Richard's House"},
    }
};

const EntrancesByScene Entrances_BackAlleyHouseDogLady = {
    "Richard's House",
    .nbItems = 1,
    {
        {0x0398, "From Back Alley"},
    }
};

const EntrancesByScene Entrances_BackAlleyHouseManInGreen = {
    "Back Alley House (Man in Green)",
    .nbItems = 1,
    {
        {0x043B, "From Back Alley"},
    }
};

const EntrancesByScene Entrances_BarinadesLair = {
    "Barinade's Lair",
    .nbItems = 1,
    {
        {0x0301, "From Inside Jabu Jabu's Belly"},
    }
};

const EntrancesByScene Entrances_Bazaar = {
    "Bazaar",
    .nbItems = 2,
    {
        {0x00B7, "From Kakariko Village"},
        {0x052C, "From Market"},
    }
};

const EntrancesByScene Entrances_BombchuBowlingAlley = {
    "Bombchu Bowling Alley",
    .nbItems = 1,
    {
        {0x0507, "From Market"},
    }
};

const EntrancesByScene Entrances_BombchuShop = {
    "Bombchu Shop",
    .nbItems = 2,
    {
        {0x0528, "From Back Alley"},
        {0x0390, "Unused: normal entrance"},
    }
};

const EntrancesByScene Entrances_BongoBongosLair = {
    "Bongo Bongo's Lair",
    .nbItems = 1,
    {
        {0x0413, "From Shadow Temple"},
    }
};

const EntrancesByScene Entrances_BottomOfTheWell = {
    "Bottom of the Well",
    .nbItems = 2,
    {
        {0x0098, "From Kakariko Village"},
        {0x05CC, "Unused: normal entrance"},
    }
};

const EntrancesByScene Entrances_CarpenterBosssHouse = {
    "Carpenter Boss's House",
    .nbItems = 1,
    {
        {0x02FD, "From Kakariko Village"},
    }
};

const EntrancesByScene Entrances_CarpentersTent = {
    "Carpenter's Tent",
    .nbItems = 1,
    {
        {0x03A0, "From Gerudo Valley"},
    }
};

const EntrancesByScene Entrances_CastleCourtyard = {
    "Zelda's Courtyard",
    .nbItems = 2,
    {
        {0x0400, "From Castle Hedge Maze"},
        {0x05F0, "From Triforce Cutscene"},
    }
};

const EntrancesByScene Entrances_CastleHeadgeMaze = {
    "Castle Hedge Maze",
    .nbItems = 2,
    {
        {0x007A, "From Hyrule Castle"},
        {0x0296, "From Castle Courtyard"},
    }
};

const EntrancesByScene Entrances_ChamberOfTheSages = {
    "Chamber of the Sages",
    .nbItems = 2,
    {
        {0x006B, "Default"},
        {0x02CE, "Unused: crashes"},
    }
};

const EntrancesByScene Entrances_CutsceneMap = {
    "Cutscene Map",
    .nbItems = 2,
    {
        {0x00A0, "Default"},
        {0x02EF, "Unused: single copy, reversed rain?"},
    }
};

const EntrancesByScene Entrances_DeathMountainCrater = {
    "Death Mountain Crater",
    .nbItems = 6,
    {
        {0x0147, "From Death Mountain Trail"},
        {0x0246, "From Goron City"},
        {0x024A, "From Fire Temple"},
        {0x0482, "From Great Fairy's Fountain"},
        {0x04F6, "From Warp Song: Bolero of Fire"},
        {0x0564, "From Blue Warp"},
    }
};

const EntrancesByScene Entrances_DeathMountainTrail = {
    "Death Mountain Trail",
    .nbItems = 6,
    {
        {0x013D, "From Kakariko Village"},
        {0x01B9, "From Goron City"},
        {0x01BD, "From Death Mountain Crater"},
        {0x0242, "From Dodongo's Cavern"},
        {0x045B, "From Great Fairy's Fountan"},
        {0x047A, "From Goron's Ruby Cutscene"},
    }
};

const EntrancesByScene Entrances_DesertColossus = {
    "Desert Colossus",
    .nbItems = 9,
    {
        {0x0123, "From Haunted Wasteland"},
        {0x01E1, "From Spirit Temple (Main Entrance)"},
        {0x01E5, "From Spirit Temple (Statue's Left Hand)"},
        {0x01E9, "From Spirit Temple (Statue's Right Hand)"},
        {0x01ED, "From Requiem of Spirit Cutscene"},
        {0x01F1, "From Warp Song: Requiem of Spirit"},
        {0x01F5, "From Silver Gauntlets Cutscene"},
        {0x057C, "From Great Fairy's Fountain"},
        {0x0610, "From Blue Warp"},
    }
};

const EntrancesByScene Entrances_DodongosCavern = {
    "Dodongo's Cavern",
    .nbItems = 2,
    {
        {0x0004, "From Death Mountain Trail"},
        {0x00C5, "From King Dodongo's Lair"}
    }
};

const EntrancesByScene Entrances_FairysFountain = {
    "Fairy's Fountain",
    .nbItems = 1,
    {
        {0x036D, "From Various"},
    }
};

const EntrancesByScene Entrances_FireTemple = {
    "Fire Temple",
    .nbItems = 2,
    {
        {0x0165, "From Death Mountain Crater"},
        {0x0175, "From Volvagia's Lair"},
    }
};

const EntrancesByScene Entrances_FishingPond = {
    "Fishing Pond",
    .nbItems = 1,
    {
        {0x045F, "From Lake Hylia"},
    }
};

const EntrancesByScene Entrances_ForestTemple = {
    "Forest Temple",
    .nbItems = 3,
    {
        {0x0169, "From Sacred Forest Meadow"},
        {0x024E, "From Phantom Ganon's Lair"},
        {0x0584, "Unused: ceiling crush room"},
    }
};

const EntrancesByScene Entrances_GanonsTower = {
    "Ganon's Tower",
    .nbItems = 3,
    {
        {0x041B, "From Inside Ganon's Castle"},
        {0x0427, "From Ganondorf's Lair"},
        {0x042B, "Unused: Below Ganondorf's Lair"},
    }
};

const EntrancesByScene Entrances_GanonsTowerCollapsing = {
    "Ganon's Tower (Collapsing)",
    .nbItems = 8,
    {
        {0x04B6, "1F - Entrance Chamber"},
        {0x03E4, "2F - Dinolfos Room"},
        {0x03DC, "3F - Boss Key Room (Top)"},
        {0x03E0, "3F - Boss Key Room (Bottom)"},
        {0x01B5, "4F - Iron Knuckle Room (Top)"},
        {0x0256, "4F - Iron Knuckle Room (Bottom)"},
        {0x0134, "5F - Ganondorf's Lair (Bottom)"},
        {0x0179, "5F - Ganondorf's Lair (Top)"}
    }
};

const EntrancesByScene Entrances_GanonsBattleArena = {
    "Ganon's Tower Collapse & Battle Arena",
    .nbItems = 1,
    {
        {0x0517, "From Inside Ganon's Castle (Collapsing)"},
    }
};

const EntrancesByScene Entrances_GanonsTowerExterior = {
    "Ganon's Tower Exterior (Collapsing)",
    .nbItems = 8,
    {
        {0x043F, "From Ganondorf"},
        {0x0524, "Stairs A (Bottom)"},
        {0x051C, "Stairs A (Top)"},
        {0x01C9, "Stairs B (Bottom)"},
        {0x0334, "Stairs B (Top)"},
        {0x0330, "Stairs C (Bottom)"},
        {0x032C, "Stairs C (Top)"},
        {0x04BA, "Stairs D (Bottom)"},
    }
};

const EntrancesByScene Entrances_GanondorfsLair = {
    "Ganondorf's Lair",
    .nbItems = 1,
    {
        {0x041F, "From Ganon's Tower"},
    }
};

const EntrancesByScene Entrances_GerudoTrainingGround = {
    "Gerudo Training Ground",
    .nbItems = 1,
    {
        {0x0008, "From Gerudo's Fortress"},
    }
};

const EntrancesByScene Entrances_GerudoValley = {
    "Gerudo Valley",
    .nbItems = 5,
    {
        {0x0117, "From Hyrule Field"},
        {0x01A5, "From Captured Without Hookshot"},
        {0x0229, "[Unused] From Gerudo's Fortress"},
        {0x022D, "From Gerudo's Fortress"},
        {0x03D0, "From Carpenters' Tent"},
    }
};

const EntrancesByScene Entrances_GerudosFortress = {
    "Gerudo's Fortress",
    .nbItems = 19,
    {
        {0x0129, "From Gerudo Valley"},
        {0x03A8, "From Gerudo Training Ground"},
        {0x03AC, "From Haunted Wasteland"},
        {0x03B0, "From Horseback Archery"},
        {0x03B4, "From Captured With Hookshot (First Time)"},
        {0x05F8, "From Captured With Hookshot (Second Time)"},
        {0x0235, "1F (Center Left)"},
        {0x0239, "1F (Center)"},
        {0x0231, "1F (Far Left)"},
        {0x02BA, "1F (Far Right)"},
        {0x02AA, "2F (Center)"},
        {0x02BE, "2F (Left)"},
        {0x02C2, "2F (Right)"},
        {0x03A4, "3F (Center Left)"},
        {0x02D2, "3F (Center Right)"},
        {0x02DA, "3F (Far Left)"},
        {0x02C6, "3F (Far Right)"},
        {0x02D6, "4F (Center)"},
        {0x02DE, "Elevated Cell Roof"},
    }
};

const EntrancesByScene Entrances_GohmasLair = {
    "Gohma's Lair",
    .nbItems = 1,
    {
        {0x040F, "From Inside the Deku Tree"},
    }
};

const EntrancesByScene Entrances_GoronCity = {
    "Goron City",
    .nbItems = 4,
    {
        {0x014D, "From Death Mountain Trail"},
        {0x01C1, "From Death Mountain Crater"},
        {0x03FC, "From Goron Shop"},
        {0x04E2, "From Lost Woods"},
    }
};

const EntrancesByScene Entrances_GoronShop = {
    "Goron Shop",
    .nbItems = 1,
    {
        {0x037C, "From Goron City"},
    }
};

const EntrancesByScene Entrances_GrannysPotionShop = {
    "Granny's Potion Shop",
    .nbItems = 1,
    {
        {0x0072, "From Kakariko Village"},
    }
};

const EntrancesByScene Entrances_GraveFairysFountain = {
    "Grave (Fairy's Fountain)",
    .nbItems = 1,
    {
        {0x004B, "From Graveyard"},
    }
};

const EntrancesByScene Entrances_GraveRedead = {
    "Grave (Redead)",
    .nbItems = 1,
    {
        {0x031C, "From Graveyard"},
    }
};

const EntrancesByScene Entrances_GravekeepersHut = {
    "Gravekeeper's Hut",
    .nbItems = 1,
    {
        {0x030D, "From Graveyard"},
    }
};

const EntrancesByScene Entrances_Graveyard = {
    "Graveyard",
    .nbItems = 9,
    {
        {0x00E4, "From Kakariko Village"},
        {0x0205, "From Shadow Temple"},
        {0x0355, "From Gravekeeper's Hut"},
        {0x0359, "From Dampe's Grave"},
        {0x035D, "From Grave (Fairy's Fountain)"},
        {0x0361, "From Grave (Redead)"},
        {0x050B, "From Royal Family's Tomb"},
        {0x0580, "From Blue Warp"},
        {0x0568, "From Warp Song: Nocturne of Shadow"},
    }
};

const EntrancesByScene Entrances_GreatFairysFountainSpells = {
    "Great Fairy's Fountain (Spells)",
    .nbItems = 3,
    {
        {0x0578, "From Hyrule Castle"},
        {0x0371, "From Zora's Fountain"},
        {0x0588, "From Desert Colossus"},
    }
};

const EntrancesByScene Entrances_GreatFairysFountainUpgrades = {
    "Great Fairy's Fountain (Upgrades)",
    .nbItems = 4,
    {
        {0x0315, "From Death Mountain Trail"},
        {0x04BE, "From Death Mountain Crater"},
        {0x04C2, "From Ganon's Castle Exterior"},
        {0x04F2, "From Death Mountain Crater (Kakariko Village)"},
    }
};

const EntrancesByScene Entrances_Grottos = {
    "Grottos",
    .nbItems = 14,
    {
        {0x003F, "Default"},
        {0x0598, "Big Skulltula"},
        {0x05B8, "Bombable Walls"},
        {0x059C, "Business Scrub (Piece of Heart)"},
        {0x05A4, "Business Scrub x3 (Nuts, Seeds, Bombs)"},
        {0x05B0, "Business Scrub x2 (Nut Upgrade & Seeds)"},
        {0x05BC, "Business Scrub x2 (Red & Green Potion)"},
        {0x05FC, "Cow & Recovery Hearts"},
        {0x05C4, "Forest Stage"},
        {0x05AC, "Octorok"},
        {0x05A0, "Redead"},
        {0x05C0, "Tektite"},
        {0x05A8, "Webs"},
        {0x05B4, "Wolfos"},
    }
};

const EntrancesByScene Entrances_GuardHouse = {
    "Guard House (Lots o' Pots)",
    .nbItems = 1,
    {
        {0x007E, "From Market Entrance"},
    }
};

const EntrancesByScene Entrances_HappyMaskShop = {
    "Happy Mask Shop",
    .nbItems = 1,
    {
        {0x0530, "From Market"},
    }
};

const EntrancesByScene Entrances_HauntedWasteland = {
    "Haunted Wasteland",
    .nbItems = 3,
    {
        {0x0130, "From Gerudo's Fortress"},
        {0x0365, "From Desert Colossus"},
        {0x0369, "Unused: OoB spawn without Link"},
    }
};

const EntrancesByScene Entrances_HouseOfTwins = {
    "House of Twins",
    .nbItems = 1,
    {
        {0x009C, "From Kokiri Forest"},
    }
};

const EntrancesByScene Entrances_HouseOfSkulltula = {
    "House of Skulltula",
    .nbItems = 1,
    {
        {0x0550, "From Kakariko Village"},
    }
};

const EntrancesByScene Entrances_HyruleCastleGanonsCastleExterior = {
    "Hyrule Castle / Ganon's Castle Exterior", //TODO: force age in wrong one
    .nbItems = 5,
    {
        {0x0138, "From Market"},
        {0x023D, "From Castle Hedge Maze / Ganon's Castle"},
        {0x0340, "From Great Fairy's Fountain"},
        {0x047E, "From Caught By Castle Guard"},
        {0x04FA, "From Caught By Hedge Maze Guard"},
    }
};

const EntrancesByScene Entrances_HyruleField = {
    "Hyrule Field",
    .nbItems = 18,
    {
        {0x00CD, "From Zelda's Escape Cutscene"},
        {0x017D, "From Kakariko Village"},
        {0x0181, "From Zora's River (Land)"},
        {0x0185, "From Lost Woods"},
        {0x0189, "From Lake Hylia"},
        {0x018D, "From Gerudo Valley"},
        {0x01F9, "From Lon Lon Ranch (Main Entrance)"},
        {0x01FD, "From Market Entrance"},
        {0x027A, "[Unused] Near Lake Hylia"},
        {0x027E, "From Lake Hylia Owl Ride"},
        {0x0282, "[Unused] Near River"},
        {0x028A, "From Lon Lon Ranch (South Fence Jump)"},
        {0x028E, "From Lon Lon Ranch (West Fence Jump)"},
        {0x0292, "From Lon Lon Ranch (East Fence Jump)"},
        {0x0311, "From Zora's River (Water)"},
        {0x0476, "From Lon Lon Ranch (Front Gate Jump)"},
        {0x050F, "From Song of Time Cutscene"},
        {0x0594, "From Impa's Cutscene"},
    }
};

const EntrancesByScene Entrances_IceCavern = {
    "Ice Cavern",
    .nbItems = 2,
    {
        {0x0088, "From Zora's Fountain"},
        {0x05D8, "[Unused] Near Block Puzzle Room"},
    }
};

const EntrancesByScene Entrances_ImpasHouse = {
    "Impa's House",
    .nbItems = 2,
    {
        {0x039C, "Main Entrance"},
        {0x05C8, "Cage"},
    }
};

const EntrancesByScene Entrances_InsideGanonsCastle = {
    "Inside Ganon's Castle",
    .nbItems = 8,
    {
        {0x0467, "From Ganon's Castle Exterior"},
        {0x0534, "From Ganon's Tower"},
        {0x0538, "Forest Trial Clear"},
        {0x053C, "Water Trial Clear"},
        {0x0540, "Shadow Trial Clear"},
        {0x0544, "Fire Trial Clear"},
        {0x0548, "Light Trial Clear"},
        {0x054C, "Spirit Trial Clear"},
    }
};

const EntrancesByScene Entrances_InsideGanonsCastleCollapsing = {
    "Inside Ganon's Castle (Collapsing)",
    .nbItems = 1,
    {
        {0x056C, "From Ganon's Tower (Collapsing)"},
    }
};

const EntrancesByScene Entrances_InsideJabuJabusBelly = {
    "Inside Jabu-Jabu's Belly",
    .nbItems = 2,
    {
        {0x0028, "From Zora's Fountain"},
        {0x0407, "From Barinade's Lair"},
    }
};

const EntrancesByScene Entrances_InsideTheDekuTree = {
    "Inside the Deku Tree",
    .nbItems = 2,
    {
        {0x0000, "From Kokiri Forest"},
        {0x0252, "From Gohma's Lair"},
    }
};

const EntrancesByScene Entrances_KakarikoPotionShop = {
    "Kakariko Potion Shop",
    .nbItems = 2,
    {
        {0x03EC, "Back Door"},
        {0x0384, "Front Door"},
        {0x03E8, "Unused: Front Door"},
    }
};

const EntrancesByScene Entrances_KakarikoVillage = {
    "Kakariko Village",
    .nbItems = 16,
    {
        {0x00DB, "From Hyrule Field"},
        {0x0191, "From Death Mountain Trail"},
        {0x0195, "From Graveyard"},
        {0x0201, "From Kakariko Bazaar"},
        {0x02A6, "From Bottom of the Well"},
        {0x0345, "From Impa's House (Main Entrance)"},
        {0x0349, "From Carpenter Boss's House"},
        {0x034D, "From Granny's Potion Shop"},
        {0x0351, "From Windmill"},
        {0x044B, "From Kakariko Potion Shop (Front Door)"},
        {0x0463, "From Kakariko Shooting Gallery"},
        {0x04EE, "From House of Skulltula"},
        {0x04FF, "From Kakariko Potion Shop (Back Door)"},
        {0x0513, "From Nocturne of Shadow Cutscene"},
        {0x0554, "From Death Mountain Trail Owl Ride"},
        {0x05DC, "From Impa's House (Cage)"},
    }
};

const EntrancesByScene Entrances_KingDodongosLair = {
    "King Dodongo's Lair",
    .nbItems = 1,
    {
        {0x040B, "From Dodongo's Cavern"},
    }
};

const EntrancesByScene Entrances_KnowItAllBrothersHouse = {
    "Know-It-All Brothers' House",
    .nbItems = 1,
    {
        {0x00C9, "From Kokiri Forest"},
    }
};

const EntrancesByScene Entrances_KokiriForest = {
    "Kokiri Forest",
    .nbItems = 13,
    {
        {0x00EE, "Main Cutscene Entrance"},
        {0x0209, "From Inside the Deku Tree"},
        {0x020D, "From Lost Woods (Forest Bridge)"},
        {0x0211, "From Link's House"},
        {0x0266, "From Kokiri Shop"},
        {0x026A, "From Know-It-All Brothers' House"},
        {0x0286, "From Lost Woods (high entrance)"},
        {0x033C, "From House of Twins"},
        {0x0443, "From Mido's House"},
        {0x0447, "From Saria's House"},
        {0x0457, "From Deku Tree Death Cutscene"},
        {0x05E8, "From Deku Sprout Cutscene"},
        {0x0338, "Unused: top of Link's House"},
    }
};

const EntrancesByScene Entrances_KokiriShop = {
    "Kokiri Shop",
    .nbItems = 1,
    {
        {0x00C1, "From Kokiri Forest"},
    }
};

const EntrancesByScene Entrances_LakeHylia = {
    "Lake Hylia",
    .nbItems = 10,
    {
        {0x0102, "From Hyrule Field"},
        {0x0219, "From Gerudo Valley"},
        {0x021D, "From Water Temple"},
        {0x0309, "From Fishing Pond"},
        {0x03CC, "From Lakeside Laboratory"},
        {0x0560, "From Zora's Domain"},
        {0x03C8, "Unused: main entrance"},
        {0x04E6, "From Water Rising Cutscene"},
        {0x0604, "From Warp Song: Serenade of Water"},
        {0x060C, "From Blue Warp"},
    }
};

const EntrancesByScene Entrances_LakesideLaboratory = {
    "Lakeside Laboratory",
    .nbItems = 2,
    {
        {0x0043, "From Lake Hylia"},
        {0x01C5, "Unused: eyedrops timeout"},
    }
};

const EntrancesByScene Entrances_LinksHouse = {
    "Link's House",
    .nbItems = 2,
    {
        {0x00BB, "From Child Savewarp"},
        {0x0272, "From Kokiri Forest"},
    }
};

const EntrancesByScene Entrances_LonLonRanch = {
    "Lon Lon Ranch",
    .nbItems = 11,
    {
        {0x0157, "From Hyrule Field"},
        {0x02AE, "From Epona's Song Cutscene"},
        {0x0378, "From Talon's House"},
        {0x042F, "From Stable"},
        {0x05D4, "From Tower"},
        {0x04CA, "Horse Riding"},
        {0x04CE, "From winning race"},
        {0x0558, "From losing race"},
        {0x055C, "Unused: Near Ingo/Malon"},
        {0x02E2, "Unused: From South Fence"},
        {0x02E6, "Unused: From West Fence"},
    }
};

const EntrancesByScene Entrances_LostWoods = {
    "Lost Woods",
    .nbItems = 10,
    {
        {0x011E, "From Kokiri Forest (High Entrance)"},
        {0x01A9, "From Sacred Forest Meadow"},
        {0x01AD, "Mushroom Timeout"},
        {0x04D6, "From Goron City"},
        {0x04DA, "From Zora's River"},
        {0x04DE, "From Hyrule Field"},
        {0x05E0, "From Kokiri Forest (Forest Bridge)"},
        {0x04D2, "Unused: Boulder and Grass Square"},
        {0x01B1, "Unused: Entrance Square from opposite side"},
        {0x04C6, "Unused: Entrance Square from ocarina game"},
    }
};

const EntrancesByScene Entrances_Market = {
    "Market",
    .nbItems = 11,
    {
        {0x00B1, "From Market Entrance"},
        {0x025A, "From Castle"},
        {0x025E, "From Temple of Time"},
        {0x0262, "From Back Alley: Right Side"},
        {0x029E, "From Back Alley: Left Side"},
        {0x01CD, "From Market Shooting Gallery"},
        {0x01D1, "From Happy Mask Shop"},
        {0x01D5, "From Treasure Chest Shop"},
        {0x02A2, "From Market Potion Shop"},
        {0x03B8, "From Market Bazaar"},
        {0x03BC, "From Bombchu Bowling Alley"},
    }
};

const EntrancesByScene Entrances_MarketEntrance = {
    "Market Entrance",
    .nbItems = 3,
    {
        {0x0033, "From Market"},
        {0x026E, "From Guard House"},
        {0x0276, "From Hyrule Field"},
    }
};

const EntrancesByScene Entrances_MarketPotionShop = {
    "Market Potion Shop",
    .nbItems = 1,
    {
        {0x0388, "From Market"},
    }
};

const EntrancesByScene Entrances_MidosHouse = {
    "Mido's House",
    .nbItems = 1,
    {
        {0x0433, "From Kokiri Forest"},
    }
};

const EntrancesByScene Entrances_MorphasLair = {
    "Morpha's Lair",
    .nbItems = 1,
    {
        {0x0417, "From Water Temple"},
    }
};

const EntrancesByScene Entrances_PhantomGanonsLair = {
    "Phantom Ganon's Lair",
    .nbItems = 1,
    {
        {0x000C, "From Forest Temple"},
    }
};

const EntrancesByScene Entrances_RanchHouse = {
    "Ranch Buildings",
    .nbItems = 3,
    {
        {0x004F, "Talon's House from Lon Lon Ranch"},
        {0x05D0, "Tower from Lon Lon Ranch"},
        {0x05E4, "Talon's House from Cucco game"},

    }
};

const EntrancesByScene Entrances_RoyalFamilysTomb = {
    "Royal Family's Tomb",
    .nbItems = 2,
    {
        {0x002D, "From Graveyard"},
        {0x0574, "Cutscene: Sun's Song"},
    }
};

const EntrancesByScene Entrances_SacredForestMeadow = {
    "Sacred Forest Meadow",
    .nbItems = 5,
    {
        {0x00FC, "From Lost Woods"},
        {0x0215, "From Forest Temple"},
        {0x02EE, "Unused: single copy, spawn 0"},
        {0x0600, "From Warp Song: Minuet of Forest"},
        {0x0608, "From Blue Warp"},
    }
};

const EntrancesByScene Entrances_SariasHouse = {
    "Saria's House",
    .nbItems = 1,
    {
        {0x0437, "From Kokiri Forest"},
    }
};

const EntrancesByScene Entrances_ShadowTemple = {
    "Shadow Temple",
    .nbItems = 4,
    {
        {0x0037, "From Graveyard"},
        {0x02B2, "Unused: Outside Boss Door"},
        {0x02B6, "From Bongo Bongo's Lair"},
        {0x04EA, "[Unused] (crashes)"},
    }
};

const EntrancesByScene Entrances_ShootingGallery = {
    "Shooting Gallery",
    .nbItems = 3,
    {
        {0x016D, "From Market"},
        {0x003B, "From Kakariko Village"},
        {0x02F0, "Unused: From Kakariko Village"},
    }
};

const EntrancesByScene Entrances_SpiritTemple = {
    "Spirit Temple",
    .nbItems = 5,
    {
        {0x0082, "From Desert Colossus: Entrance"},
        {0x03F4, "From Desert Colossus: Statue's Left Hand"},
        {0x03F0, "From Desert Colossus: Statue's Right Hand"},
        {0x02F5, "From Twinrova's Lair"},
        {0x03F8, "Unused: from left hand, room #00"},
    }
};

const EntrancesByScene Entrances_Stable = {
    "Stable",
    .nbItems = 1,
    {
        {0x02F9, "From Lon Lon Ranch"},
    }
};

const EntrancesByScene Entrances_TempleOfTime = {
    "Temple of Time",
    .nbItems = 7,
    {
        {0x0053, "From Temple of Time Exterior"},
        {0x02CA, "From Event: Pull & Place Master Sword"},
        {0x0320, "Unused: near stones"},
        {0x0324, "Cutscene: Meeting Sheik"},
        {0x058C, "Cutscene: Light Arrows"},
        {0x0590, "Unused: LACS"},
        {0x05F4, "From Warp Song: Prelude of Light"},
    }
};

const EntrancesByScene Entrances_TempleOfTimeExterior = {
    "Temple of Time Exterior",
    .nbItems = 2,
    {
        {0x0171, "From Market"},
        {0x0472, "From Temple of Time"},
    }
};

const EntrancesByScene Entrances_ThievesHideout = {
    "Thieves' Hideout",
    .nbItems = 13,
    {
        {0x049E, "Blue Cell Block (Bottom)"},
        {0x04A2, "Blue Cell Block (Top)"},
        {0x0570, "Dark Green Cell Block"},
        {0x04AE, "Dining Hall (Bottom)"},
        {0x04B2, "Dining Hall (Top)"},
        {0x048E, "Kitchen Hall (Bottom Left)"},
        {0x0492, "Kitchen Hall (Bottom Right)"},
        {0x04A6, "Kitchen Hall (Middle Left)"},
        {0x04AA, "Kitchen Hall (Top Left)"},
        {0x0496, "Light Green Cell Block (Left)"},
        {0x049A, "Light Green Cell Block (Right)"},
        {0x0486, "Red Cell Block (Left)"},
        {0x048A, "Red Cell Block (Right)"},
    }
};

const EntrancesByScene Entrances_TreasureBoxShop = {
    "Treasure Chest Shop",
    .nbItems = 1,
    {
        {0x0063, "From Market"},
    }
};

const EntrancesByScene Entrances_TwinrovasLair = {
    "Twinrova's Lair",
    .nbItems = 2,
    {
        {0x008D, "From Spirit Temple"},
        {0x05EC, "Unused: boss arena"},
    }
};

const EntrancesByScene Entrances_VolvagiasLair = {
    "Volvagia's Lair",
    .nbItems = 1,
    {
        {0x0305, "From Fire Temple"},
    }
};

const EntrancesByScene Entrances_WaterTemple = {
    "Water Temple",
    .nbItems = 2,
    {
        {0x0010, "From Lake Hylia"},
        {0x0423, "From Morpha's Lair"},
    }
};

const EntrancesByScene Entrances_Windmill = {
    "Dampe's Grave & Windmill",
    .nbItems = 3,
    {
        {0x044F, "From Graveyard"},
        {0x0453, "From Kakariko Village"},
        {0x0503, "From Well Draining Cutscene"},
    }
};

const EntrancesByScene Entrances_ZoraShop = {
    "Zora Shop",
    .nbItems = 1,
    {
        {0x0380, "From Zora's Domain"}
    }

};

const EntrancesByScene Entrances_ZorasDomain = {
    "Zora's Domain",
    .nbItems = 5,
    {
        {0x0108, "From Zora's River"},
        {0x01A1, "From Zora's Fountain"},
        {0x0328, "From Lake Hylia"},
        {0x03C4, "From Zora Shop"},
        {0x0153, "Frog Timeout"},
    }
};

const EntrancesByScene Entrances_ZorasFountain = {
    "Zora's Fountain",
    .nbItems = 6,
    {
        {0x010E, "Cutscene: Zora's Sapphire"},
        {0x0221, "From Inside Jabu Jabu's Belly"},
        {0x0225, "From Zora's Domain"},
        {0x03D4, "From Ice Cavern"},
        {0x0394, "From Great Fairy's Fountain"},
        {0x03D8, "Unused: near bottom left corner"},
    }
};

const EntrancesByScene Entrances_ZorasRiver = {
    "Zora's River",
    .nbItems = 5,
    {
        {0x00EA, "From Hyrule Field (Land Transition)"},
        {0x0199, "Unused: From Zora's Fountain"},
        {0x019D, "From Zora's Domain"},
        {0X01D9, "From Hyrule Field (Water Transition)"},
        {0x01DD, "From Lost Woods"},
    }
};
