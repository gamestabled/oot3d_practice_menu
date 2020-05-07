#include "menu.h"
#include "menus/cheats.h"
#include "z3D/z3D.h"

static void Cheats_Health(void){
    gSaveContext.health = gSaveContext.healthCapacity;
}

static void Cheats_Magic(void){
    gSaveContext.magic = 0x30 * gSaveContext.magicLevel;
}

static void Cheats_Sticks(void){
    gSaveContext.ammo[ITEM_DEKU_STICK] = 10 * ((gSaveContext.upgrades >> 17) & 0x7);
}

static void Cheats_Nuts(void){
    gSaveContext.ammo[ITEM_DEKU_NUT] = 10 + 10 * ((gSaveContext.upgrades >> 20) & 0x7);
}

static void Cheats_Bombs(void){
    gSaveContext.ammo[ITEM_BOMB] = 10 + 10 * ((gSaveContext.upgrades >> 3) & 0x7);
}

static void Cheats_Arrows(void){
    gSaveContext.ammo[ITEM_FAIRY_BOW] = 20 + 10 * (gSaveContext.upgrades & 0x7);
}

static void Cheats_Slingshot(void){
    gSaveContext.ammo[ITEM_FAIRY_SLINGSHOT] = 20 + 10 * ((gSaveContext.upgrades >> 14) & 0x7);
}

static void Cheats_Bombchus(void){
    gSaveContext.ammo[ItemSlots[ITEM_BOMBCHU]] = 50;
}

static void Cheats_Beans(void){
    gSaveContext.ammo[ItemSlots[ITEM_MAGIC_BEANS]] = 10;
}

static void Cheats_Rupees(void){
    u8 walletUpgrade = (gSaveContext.upgrades >> 12) & 0x3;
    switch(walletUpgrade){
        case 0:
            gSaveContext.rupees = 99;
            break;
        case 1:
            gSaveContext.rupees = 200;
            break;
        case 2:
            gSaveContext.rupees = 500;
            break;
        default:
            break;
    }
}

static void Cheats_Nayrus(void){ //TODO

}

static void Cheats_FreezeTime(void){ //TODO

}

static void Cheats_Music(void){ //TODO

}

static void Cheats_Usability(void){ //TODO

}

static void Cheats_ISG(void){
    // PLAYER->isg = 1;
    ((Player*)gGlobalContext->actorCtx.actorList[ACTORTYPE_PLAYER].first)->isg = 1;
}

static void Give_Deku_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_DEKU_TREE]++;
}

static void Give_Dodongo_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_DODONGOS_CAVERN]++;
}

static void Give_Jabu_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_JABUJABUS_BELLY]++;
}

static void Give_Forest_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_FOREST_TEMPLE]++;
}

static void Give_Fire_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_FIRE_TEMPLE]++;
}

static void Give_Water_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_WATER_TEMPLE]++;
}

static void Give_Spirit_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_SPIRIT_TEMPLE]++;
}

static void Give_Shadow_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_SHADOW_TEMPLE]++;
}

static void Give_Well_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_BOTTOM_OF_THE_WELL]++;
}

static void Give_Ice_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_ICE_CAVERN]++;
}

// static void Give_GanonSecond_Key(void){
//    gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_SECOND_PART]++;
// }

static void Give_Grounds_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_GERUDO_TRAINING_GROUNDS]++;
}

static void Give_Gerudo_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_GERUDO_FORTRESS]++;
}

// static void Give_GanonFirst_Key(void){
//    gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_FIRST_PART]++;
// }

// static void Give_GanonBoss_Key(void){
//    gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_FLOOR_BENEATH_BOSS_CHAMBER]++;
// }

// static void Give_GanonCrumbling_Key(void){
//    gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_CRUMBLING]++;
// }

static void Give_Treasure_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_TREASURE_CHEST_SHOP]++;
}

// static void Give_DekuBoss_Key(void){
//    gSaveContext.dungeonKeys[DUNGEON_DEKU_TREE_BOSS_ROOM]++;
// }

// static void Give_DodongoBoss_Key(void){
//    gSaveContext.dungeonKeys[DUNGEON_DODONGOS_CAVERN_BOSS_ROOM]++;
// }

// static void Give_JabuBoss_Key(void){ commenting to remove a warning
//     gSaveContext.dungeonKeys[DUNGEON_JABUJABUS_BELLY_BOSS_ROOM]++;
// }


Menu CheatsMenu = {
    "Cheats",
    .nbItems = 10,
    {
        {"Refill Health", METHOD, .method = Cheats_Health},
        {"Refill Magic", METHOD, .method = Cheats_Magic},
        {"Refill Items", MENU, .menu = &CheatsItemsMenu},
        {"Refill Keys", MENU, .menu = &CheatsKeysMenu},
        {"Refill Rupees", METHOD, .method = Cheats_Rupees},
        {"Infinite Nayru's Love (TODO)", METHOD, .method = Cheats_Nayrus},
        {"Freeze time of day (TODO)", METHOD, .method = Cheats_FreezeTime},
        {"No music (TODO)", METHOD, .method = Cheats_Music},
        {"Usable Items (TODO)", METHOD, .method = Cheats_Usability},
        {"ISG", METHOD, .method = Cheats_ISG},
    }
};

Menu CheatsItemsMenu = {
    "Items",
    .nbItems = 7,
    {
        {"Refill Deku Sticks", METHOD, .method = Cheats_Sticks},
        {"Refill Deku Nuts", METHOD, .method = Cheats_Nuts},
        {"Refill Bombs", METHOD, .method = Cheats_Bombs},
        {"Refill Arrows", METHOD, .method = Cheats_Arrows},
        {"Refill Slingshot", METHOD, .method = Cheats_Slingshot},
        {"Refill Bombchus", METHOD, .method = Cheats_Bombchus},
        {"Refill Beans", METHOD, .method = Cheats_Beans},
    }
};

Menu CheatsKeysMenu = {
    "Keys",
    .nbItems = 13,
    {
        {"Deku Tree", METHOD, .method = Give_Deku_Key},
        {"Dodongo's Cavern", METHOD, .method = Give_Dodongo_Key},
        {"Jabu-Jabu's Belly", METHOD, .method = Give_Jabu_Key},
        {"Forest Temple", METHOD, .method = Give_Forest_Key},
        {"Fire Temple", METHOD, .method = Give_Fire_Key},
        {"Water Temple", METHOD, .method = Give_Water_Key},
        {"Spirit Temple", METHOD, .method = Give_Spirit_Key},
        {"Shadow Temple", METHOD, .method = Give_Shadow_Key},
        {"Bottom of the Well", METHOD, .method = Give_Well_Key},
        {"Ice Cavern", METHOD, .method = Give_Ice_Key},
        // {"Ganon's Castle (Second Part)", METHOD, .method = Give_GanonSecond_Key},
        {"Gerudo Training Grounds", METHOD, .method = Give_Grounds_Key},
        {"Gerudo Fortress", METHOD, .method = Give_Gerudo_Key},
        // {"Ganon's Castle (First Part)", METHOD, .method = Give_GanonFirst_Key},
        // {"Ganon's Castle (Floor Beneath Boss Chamber", METHOD, .method = Give_GanonBoss_Key},
        // {"Ganon's Castle (Crumbling)", METHOD, .method = Give_GanonCrumbling_Key},
        {"Treasure Chest Shop", METHOD, .method = Give_Treasure_Key},
        // {"Deku Tree Boss Room", METHOD, .method = Give_DekuBoss_Key},
        // {"Dodongo's Cavern Boss Room", METHOD, .method = Give_DodongoBoss_Key},
        // {"Jabu-Jabu's Belly Boss Room", METHOD, .method = Give_JabuBoss_Key},
    }
};
