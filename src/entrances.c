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

EntrancesByScene Entrances_Market = {
    "Market",
    .nbItems = 11,
    {
        {0x00B1, "From Market Entrance"},
        {0x01CD, "From Market Shooting Gallery"},
        {0x01D1, "From Happy Mask Shop"},
        {0x01D5, "From Treasure Box Shop"},
        {0x025A, "From Hyrule Castle"},
        {0x025E, "From Temple of Time"},
        {0x0262, "From Back Alley: Right Side"},
        {0x029E, "From Back Alley: Left Side"},
        {0x02A2, "From Market Potion Shop"},
        {0x03B8, "From Market Bazaar"},
        {0x03BC, "From Bombchu Bowling Alley"},
    }
};

EntrancesByScene Entrances_MarketBazaar = {
    "Market Bazaar",
    .nbitems = 1,
    {
        {0x052C, "From Market"},
    }
};

EntrancesByScene Entrances_MarketEntrance = {
    "Market Entrance",
    .nbItems = 3,
    {
        {0x0033, "From Market"},
        {0x026E, "From Guard House"},
        {0x0276, "From Hyrule Field"},
    }
};

EntrancesByScene Entrances_MarketPotionShop = {
    "Market Potion Shop",
    .nbitems = 1,
    {
        {0x0388, "From Market"},
    }
};

EntrancesByScene Entrances_MarketShootingGallery = {
    "Market Shooting Gallery",
    .nbitems = 1,
    {
        {0x016D, "From Market"},
    }
};

EntrancesByScene Entrances_MidosHouse = {
    "Mido's House",
    .nbItems = 1,
    {
        {0x0433, "From Kokiri Forest"},
    }
};

EntrancesByScene Entrances_MorphasLair = {
    "Morpha's Lair",
    .nbItems = 1,
    {
        {0x0417, "From Water Temple"},
    }
};

EntrancesByScene Entrances_NaboorusMiniBossRoom = {
    "Nabooru's Mini-Boss Room",
    .nbItems = 1,
    {
        {0x008D, "From Spirit Temple"},
    }
};

EntrancesByScene Entrances_PhantomGanonsLair = {
    "Phantom Ganon's Lair",
    .nbItems = 1,
    {
        {0x000C, "From Forest Temple"},
    }
};

EntrancesByScene Entrances_RanchHouse = {
    "Ranch House",
    .nbItems = 2,
    {
        {0x004F, "From Lon Lon Ranch"},
        {0x05E4, "[?]"},
    }
};

EntrancesByScene Entrances_RoyalFamilysTomb = {
    "Royal Family's Tomb",
    .nbItems = 2,
    {
        {0x002D, "From Graveyard"},
        {0x0574, "Cutscene: Sun's Song"},
    }
};

EntrancesByScene Entrances_SacredForestMeadow = {
    "Sacred Forest Meadow",
    .nbItems = 5,
    {
        {0x00FC, "From Lost Woods"},
        {0x0215, "From Forest Temple"},
        {0x02EE, "[?]"},
        {0x0608, "From Phantom Ganon's Lair: Blue Warp"},
        {0x0600, "Warp Song: Minuet of Forest"},
    }
};

EntrancesByScene Entrances_SariasHouse = {
    "Saria's House",
    .nbItems = 1,
    {
        {0x0437, "From Kokiri Forest"},
    }
};

EntrancesByScene Entrances_ShadowTemple = {
    "Shadow Temple",
    .nbItems = 4,
    {
        {0x0037, "From Graveyard"},
        {0x02B2, "From Bongo Bongo's Lair"},
        {0x02B6, "From Graveyard (Wrong Room)"},
        {0x04EA, "[?]"},
    }
};

EntrancesByScene Entrances_Silo = {
    "Silo",
    .nbItems = 1,
    {
        {0x05D0, "From Lon Lon Ranch"},
    }
};

EntrancesByScene Entrances_SpiritTemple = {
    "Spirit Temple",
    .nbItems = 5,
    {
        {0x02F5, "From Nabooru's Mini-Boss Room"},
        {0x03F8, "[?]"},
        {0x03F4, "From Desert Colossus: Statue's Left Hand"},
        {0x03F0, "From Desert Colossus: Statue's Right Hand"},
        {0x0082, "From Desert Colossus: Entrance"},
    }
};

EntranceByScene Entrances_Stable = {
    "Stable",
    .nbItems = 1,
    {
        {0x02F9, "From Lon Lon Ranch"},
    }
};

EntrancesByScene Entrances_TempleOfTime = {
    "Temple of Time",
    .nbItems = 7,
    {
        {0x0053, "From Temple of Time Exterior"},
        {0x02CA, "From Event: Pull & Place Master Sword"},
        {0x0320, "[?]"},
        {0x0324, "Cutscene: Meeting Sheik"},
        {0x058C, "Cutscene: Light Arrows"},
        {0x0590, "[?]"},
        {0x05F4, "Warp Song: Prelude of Light"},
    }
};

EntrancesByScene Entrances_TempleOfTimeExterior = {
    "Temple of Time Exterior",
    .nbItems = 2,
    {
        {0x0171, "From Market"},
        {0x0472, "From Temple of Time"},
    }
};

EntrancesByScene Entrances_ThievesHideout = {
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

EntranceByScene Entrances_TreasureBoxShop = {
    "Treasure Box Shop",
    .nbItems = 1,
    {
        {0x0063, "From Market"},
    }
};

EntranceByScene Entrances_TwinrovasLair = {
    "Twinrova's Lair",
    .nbItems = 1,
    {
        {0x05EC, "[Unused]"},
    }
};

EntranceByScene Entrances_VolvagiasLair = {
    "Volvagia's Lair",
    .nbItems = 1,
    {
        {0x0305, "From Fire Temple"},
    }
};

EntrancesByScene Entrances_WaterTemple = {
    "Water Temple",
    .nbItems = 2,
    {
        {0x0010, "From Lake Hylia"},
        {0x0423, "From Morpha's Lair"},
    }
};

EntrancesByScene Entrances_Windmill = {
    "Windmill/ Dampe's Grave",
    .nbItems = 3,
    {
        {0x044F, "From Graveyard"},
        {0x0453, "From Kakariko Village"},
        {0x0503, "From Well Draining Cutscene"},
    }
};

EntrancesByScene Entrances_ZoraShop = {
    "Zora Shop",
    .nbItems = 1,
    {
        {0x0380, "From Zora's Domain"}
    }

};

EntrancesByScene Entrances_ZorasDomain = {
    "Zora's Domain",
    .nbItems = 5,
    {
        {0x0108, "From Zora's River"},
        {0x01A1, "From Zora's Fountain"},
        {0x0328, "From Lake Hylia"},
        {0x03C4, "From Zora Shop"},
        {0x0153, "[?] (Throne Room)"},
    }
};

EntrancesByScene Entrances_ZorasFountain = {
    "Zora's Fountain",
    .nbItems = 6,
    {
        {0x010E, "Cutscene: Zora's Saphhire"},
        {0x0221, "From Inside Jabu Jabu's Belly"},
        {0x0225, "From Zora's Domain"},
        {0x0394, "From Great Fairy's Fountain (Spells): Farore's Wind"},
        {0x03D4, "From Ice Cavern"},
        {0x03D8, "From Bottom Left Corner [Unused]"},
    }
};

EntrancesByScene Entrances_ZorasRiver = {
    "Zora's River",
    .nbItems = 5,
    {
        {0x0199, "From Zora's Fountain"},
        {0x019D, "From Zora's Domain"},
        {0x01DD, "From Lost Woods: Zora's River Square"},
        {0x00EA, "From Hyrule Field (Land Transition)"},
        {0X01D9, "From Hyrule Field (Water Transition)"},
    }
};
