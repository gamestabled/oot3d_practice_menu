#include "z3D/entrances.h"
#include "draw.h"
#include "menu.h"
#include "z3D/z3D.h"
#include "utils.h"
#include <stdio.h>

#define ENTRANCE_MENU_MAX_SHOW 16

void EntranceWarp(u16 EntranceIndex, s32 chosenAge, s32 cutsceneIndex){
    gGlobalContext->nextEntranceIndex = EntranceIndex;
    gGlobalContext->linkAgeOnLoad = chosenAge;
    if (cutsceneIndex < 0){
        gSaveContext.cutsceneIndex = 0;
    }
    else {
        gSaveContext.cutsceneIndex = (cutsceneIndex += 0xFFF0);
    }
    gGlobalContext->sceneLoadFlag = 0x14;
}

void EntranceSelectMenuShow(EntrancesByScene* entrances){
    s32 selected = 0, page = 0, pagePrev = 0;
    s32 chosenAge = gSaveContext.linkAge;
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

        char ageBuf[65] = { 0 };
        sprintf(ageBuf, "Age on Load: %s", chosenAge ? "Child" : "Adult");
        Draw_DrawString(30, 30, COLOR_WHITE, ageBuf);
        Draw_DrawCharacter(10, 30, COLOR_WHITE, selected == 0 ? '>' : ' ');

        char csBuf[65] = { 0 };
        if (cutsceneIndex < 0){
            cutsceneIndex = -1;
            Draw_DrawString(30, 30 + SPACING_Y, curColor, "Cutscene Number on Load: None");
        }
        else {
            sprintf(csBuf, "Cutscene Number on Load: %d", cutsceneIndex);
            Draw_DrawString(30, 30 + SPACING_Y, curColor, csBuf);

        }
        Draw_DrawCharacter(10, 30 + SPACING_Y, COLOR_WHITE, selected == 1 ? '>' : ' ');

        for (s32 i = 0; i < ENTRANCE_MENU_MAX_SHOW && page * ENTRANCE_MENU_MAX_SHOW + i < entrances->nbItems; ++i)
        {
            char buf[65] = { 0 };
            s32 j = page * ENTRANCE_MENU_MAX_SHOW + i;
            Draw_DrawString(70, 30 + (2 + i) * SPACING_Y, COLOR_WHITE, entrances->items[j].title);
            Draw_DrawCharacter(10, 30 + (2 + i) * SPACING_Y, COLOR_WHITE, selected == (2 + i) ? '>' : ' ');
        }

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = waitInputWithTimeout(1000);
        if(pressed & BUTTON_B && !chosen)
            break;
        else if(pressed & BUTTON_B && chosen)
        {
            curColor = COLOR_WHITE;
            chosen = 0;
        }
        else if(pressed & BUTTON_A && !chosen)
        {
            if(selected == 1){
                chosen = 1;
                curColor = COLOR_RED;
            }
            else if(selected == 0){
                chosenAge = 1 - chosenAge;
            }
            else {
                EntranceWarp(entrances->items[selected - 2].entranceIndex, chosenAge, cutsceneIndex);
                break;
            }
        }
        else if(pressed & BUTTON_A && chosen) //should be guaranteed selected == 1
        {
            curColor = COLOR_WHITE;
            chosen = 0;
        }
        else if(pressed & BUTTON_DOWN && !chosen)
        {
            selected++;
        }
        else if(pressed & BUTTON_DOWN && chosen)
        {
            cutsceneIndex--;
        }
        else if(pressed & BUTTON_UP && !chosen)
        {
            selected--;
        }
        else if(pressed & BUTTON_UP && chosen)
        {
            cutsceneIndex++;
        }
        if(selected < 0)
            selected = entrances->nbItems - 1;
        else if(selected >= entrances->nbItems) selected = 0;

        pagePrev = page;
        page = selected / ENTRANCE_MENU_MAX_SHOW;
    } while(true);
}

EntrancesByScene Entrances_BackAlley = {
    "Back Alley",
    .nbItems = 5,
    {
        {0x0067, "From Man in Green"},
        {0x038C, "From Dog Lady"},
        {0x0398, "From Bombchu Shop"},
        {0x029A, "From Market (Left Side)"},
        {0x00AD, "From Market (Right Side)"},
    }
};

EntrancesByScene Entrances_BackAlleyHouseDogLady = {
    "Back Alley House (Dog Lady)",
    .nbItems = 1,
    {
        {0x0398, "From Back Alley"},
    }
};

EntrancesByScene Entrances_BackAlleyHouseManInGreen = {
    "Back Alley House (Man in Green)",
    .nbItems = 1,
    {
        {0x043B, "From Back Alley"},
    }
};

EntrancesByScene Entrances_BarinadesLair = {
    "Barinade's Lair",
    .nbItems = 1,
    {
        {0x0301, "From Inside Jabu Jabu's Belly"},
    }
};

EntrancesByScene Entrances_BombchuBowlingAlley = {
    "Bombchu Bowling Alley",
    .nbItems = 1,
    {
        {0x0507, "From Market"},
    }
};

EntrancesByScene Entrances_BombchuShop = {
    "Bombchu Shop",
    .nbItems = 2,
    {
        {0x0390, "[Unused]"},
        {0x0528, "From Back Alley"},
    }
};

EntrancesByScene Entrances_BottomOfTheWell = {
    "Bottom of the Well",
    .nbItems = 2,
    {
        {0x0098, "From Kakariko Village"},
        {0x05CC, "[Unused]"},
    }
};

EntrancesByScene Entrances_CarpenterBosssHouse = {
    "Carpenter Boss's House",
    .nbItems = 1,
    {
        {0x02FD, "From Kakariko Village"},
    }
};

EntrancesByScene Entrances_CarpentersTent = {
    "Carpenter's Tent",
    .nbItems = 1,
    {
        {0x03A0, "From Gerudo Valley"},
    }
};

EntrancesByScene Entrances_CastleCourtyard = {
    "Castle Courtyard",
    .nbItems = 2,
    {
        {0x0400, "From Castle Hedge Maze"},
        {0x05F0, "From Triforce Cutscene"},
    }
};

EntrancesByScene Entrances_CastleHeadgeMaze = {
    "Castle Hedge Maze",
    .nbItems = 3,
    {
        {0x007A, "From Hyrule Castle"},
        {0x0296, "From Castle Courtyard"},
        {0x0076, "[Unused]"},
    }
};

EntrancesByScene Entrances_ChamberOfTheSages = {
    "Chamber of the Sages",
    .nbItems = 2,
    {
        {0x006B, "From Temple of Time"},
        {0x02CE, "[?]"},
    }
};

EntrancesByScene Entrances_CutsceneMap = {
    "Cutscene Map",
    .nbItems = 2,
    {
        {0x00A0, "[?]"},
        {0x02EF, "[?]"},
    }
};

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

EntrancesByScene Entrances_Windmill = {
    "Windmill/ Dampe's Grave",
    .nbItems = 3,
    {
        {0x044F, "From Graveyard"},
        {0x0453, "Kakariko Village"},
        {0x0503, "From Well Draining Cutscene"},
    }
};

EntrancesByScene Entrances_ZorasDomain;
EntrancesByScene Entrances_ZorasFountain;
EntrancesByScene Entrances_ZorasRiver;
