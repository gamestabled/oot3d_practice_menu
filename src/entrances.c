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

EntrancesByScene Entrances_DeathMountainCrater = {
    "Death Mountain Crater",
    .nbItems = 6,
    {
        {0x0147, "From Death Mountain Trail"},
        {0x0246, "From Goron City"},
        {0x024A, "From Fire Temple"},
        {0x0482, "From Great Fairy's Fountain"},
        {0x0564, "From Volvagia's Lair: Blue Warp"},
        {0x0476, "From Warp Song: Bolero of Fire"},
    }
};

EntrancesByScene Entrances_DeathMountainTrail = {
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

EntrancesByScene Entrances_DesertColossus = {
    "Desert Colossus",
    .nbItems = 9,
    {
        {0x0123, "From Haunted Wasteland"},
        {0x01ED, "From Requiem of Spirit Cutscene"},
        {0x057C, "From Great Fairy's Fountain"},
        {0x0610, "From Twinrova's Lair: Blue Warp"},
        {0x01E1, "From Spirit Temple (Main Entrance)"},
        {0x01E5, "From Spirit Temple (Statue's Left Hand)"},
        {0x01E9, "From Spirit Temple (Statue's Right Hand)"},
        {0x01F5, "From Silver Gauntlets Cutscene"},
        {0x01F1, "From Warp Song: Requiem of Spirit"},
    }
};

EntrancesByScene Entrances_DodongosCavern = {
    "Dodongo's Cavern",
    .nbItems = 2,
    {
        {0x0004, "From Death Mountain Trail"},
        {0x00C5, "From King Dodongo's Lair"}
    }
};

EntrancesByScene Entrances_FairysFountain = {
    "Fairy's Fountain",
    .nbItems = 1,
    {
        {0x036D, "From Various"},
    }
};

EntrancesByScene Entrances_FireTemple = {
    "Fire Temple",
    .nbItems = 2,
    {
        {0x0165, "From Death Mountain Crater"},
        {0x0175, "From Volvagia's Lair"},
    }
};

EntrancesByScene Entrances_FishingPond = {
    "Fishing Pond",
    .nbItems = 1,
    {
        {0x045F, "From Lake Hylia"},
    }
};

EntrancesByScene Entrances_ForestTemple = {
    "Forest Temple",
    .nbItems = 3,
    {
        {0x0169, "From Sacred Forest Meadow"},
        {0x024E, "From Phantom Ganon's Lair"},
        {0x0584, "[?]"},
    }
};

EntrancesByScene Entrances_GanonsTower = {
    "Ganon's Tower",
    .nbItems = 3,
    {
        {0x041B, "From Inside Ganon's Castle"},
        {0x0427, "From Ganondorf's Lair"},
        {0x042B, "Below Ganondorf's Lair"},
    }
};

EntrancesByScene Entrances_GanonsTowerCollapsing = {
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

EntrancesByScene Entrances_GanonsBattleArena = {
    "Ganon's Tower Collapse & Battle Arena",
    .nbItems = 1,
    {
        {0x0517, "From Inside Ganon's Castle (Collapsing)"},
    }
};

EntrancesByScene Entrances_GanonsTowerExterior = {
    "Ganon's Tower Exterior (Collapsing)",
    .nbItems = 8,
    {
        {0x043F, "[?]"},
        {0x0524, "Stairs A (Bottom)"},
        {0x051C, "Stairs A (Top)"},
        {0x01C9, "Stairs B (Bottom)"},
        {0x0334, "Stairs B (Top)"},
        {0x0330, "Stairs C (Bottom)"},
        {0x032C, "Stairs C (Top)"},
        {0x04BA, "Stairs D (Bottom)"},
    }
};

EntrancesByScene Entrances_GanondorfsLair = {
    "Ganondorf's Lair",
    .nbItems = 1,
    {
        {0x041F, "From Ganon's Tower"},
    }
};

EntrancesByScene Entrances_GerudoTrainingGround = {
    "Gerudo Training Ground",
    .nbItems = 1,
    {
        {0x0008, "From Gerudo's Fortress"},
    }
};

EntrancesByScene Entrances_GerudoValley = {
    "Gerudo Valley",
    .nbItems = 5,
    {
        {0x0117, "From Hyrule Field"},
        {0x01A5, "From Captured Without Hookshot"},
        {0x0229, "From Gerudo's Fortress [Early]"},
        {0x022D, "From Gerudo's Fortress"},
        {0x03D0, "From Carpenters' Tent"},
    }
};

EntrancesByScene Entrances_GerudosFortress = {
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

EntrancesByScene Entrances_GohmasLair = {
    "Gohma's Lair",
    .nbItems = 1,
    {
        {0x040F, "From Inside the Deku Tree"},
    }
};

EntrancesByScene Entrances_GoronCity = {
    "Goron City",
    .nbItems = 4,
    {
        {0x014D, "From Death Mountain Trail"},
        {0x01C1, "From Death Mountain Crater"},
        {0x03FC, "From Goron Shop"},
        {0x04E2, "From Lost Woods"},
    }
};

EntrancesByScene Entrances_GoronShop = {
    "Goron Shop",
    .nbItems = 1,
    {
        {0x037C, "From Goron City"},
    }
};

EntrancesByScene Entrances_GrannysPotionShop = {
    "Granny's Potion Shop",
    .nbItems = 1,
    {
        {0x0072, "From Kakariko Village"},
    }
};

EntrancesByScene Entrances_GraveFairysFountain = {
    "Grave (Fairy's Fountain)",
    .nbItems = 1,
    {
        {0x004B, "From Graveyard"},
    }
};

EntrancesByScene Entrances_GraveRedead = {
    "Grave (Redead)",
    .nbItems = 1,
    {
        {0x031C, "From Graveyard"},
    }
};

EntrancesByScene Entrances_GravekeepersHut = {
    "Gravekeeper's Hut",
    .nbItems = 1,
    {
        {0x030D, "From Graveyard"},
    }
};

EntrancesByScene Entrances_Graveyard = {
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
        {0x0580, "From Bongo Bongo's Lair: Blue Warp"},
        {0x0568, "From Warp Song: Nocturne of Show"},
    }
};

EntrancesByScene Entrances_GreatFairysFountainSpells = {
    "Great Fairy's Fountain (Spells)",
    .nbItems = 3,
    {
        {0x0578, "From Hyrule Castle"},
        {0x0371, "From Zora's Fountain"},
        {0x0588, "From Desert Colossus"},
    }
};

EntrancesByScene Entrances_GreatFairysFountainUpgrades = {
    "Great Fairy's Fountain (Upgrades)",
    .nbItems = 4,
    {
        {0x04C2, "From Ganon's Castle Exterior"},
        {0x04BE, "From Death Mountain Crater"},
        {0x04F2, "From Death Mountain Crater(Kakariko Village)"},
        {0x0315, "From Death Mountain Trail"},
    }
};

EntrancesByScene Entrances_Grottos = {
    "Grottos",
    .nbItems = 14,
    {
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
        {0x003F, "Small Rupee Chest"},
        {0x05C0, "Tektite"},
        {0x05A8, "Webs"},
        {0x05B4, "Wolfos"},
    }
};

EntrancesByScene Entrances_GuardHouse = {
    "Guard House (Lots o' Pots)",
    .nbItems = 1,
    {
        {0x007E, "From Market Entrance"},
    }
};

EntrancesByScene Entrances_HappyMaskShop = {
    "Happy Mask Shop",
    .nbItems = 1,
    {
        {0x0530, "From Market"},
    }
};

EntrancesByScene Entrances_HauntedWasteland = {
    "Haunted Wasteland",
    .nbItems = 3,
    {
        {0x0130, "Gerudo's Fortress & Void Respawn"},
        {0x0365, "From Desert Colossus"},
        {0x0369, "[?]"},
    }
};

EntrancesByScene Entrances_HouseOfSkulltula = {
    "House of Skulltula",
    .nbItems = 1,
    {
        {0x0550, "From Kakariko Village"},
    }
};

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
