#include "menu.h"
#include "menus/cheats.h"
#include "z3D/z3D.h"

Menu CheatsMenu = {
    "Cheats",
    .nbItems = 10,
    {
        {"Refill Health", METHOD, .method = Cheats_Health},
        {"Refill Magic", METHOD, .method = Cheats_Magic},
        {"Refill Items", MENU, .menu = &CheatsItemsMenu},
        {"Refill Keys", MENU, .menu = &CheatsKeysMenu},
        {"Refill Rupees", METHOD, .method = Cheats_Rupees},
        {"Infinite Nayru's Love", METHOD, .method = Cheats_Nayrus},
        {"Freeze time of day", METHOD, .method = Cheats_FreezeTime},
        {"No music", METHOD, .method = Cheats_Music},
        {"Usable Items", METHOD, .method = Cheats_Usability},
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
    .nbItems = 20,
    {
        {"Deku Tree", METHOD, .method = Give_Deku_Key},
        {"Dodongo's Cavern", METHOD, .method = Give_Dodongo_Key},
        {"Jabu-Jabu's Belly", METHOD, .method = Give_Jabu_Key},
        {"Forest Temple", METHOD, .method = Give_Forest_Key},
        {"Fire Temple", METHOD, .method = Give_Fire_Key},
        {"Water Temple", METHOD, .method = Give_Water_Key},
        {"Spirit Temple", METHOD, .method = Give_Spirit_Key},
        {"Shadow Temple", METHOD, .method = Give_Shadow_Key},
        {"Bottom of the Well}", METHOD, .method = Give_Well_Key},
        {"Ice Cavern", METHOD, .method = Give_Ice_Key},
        {"Ganon's Castle (Second Part)", METHOD, .method = Give_GanonSecond_Key},
        {"Gerudo Training Grounds", METHOD, .method = Give_Grounds_Key},
        {"Gerudo Fortress", METHOD, .method = Give_Gerudo_Key},
        {"Ganon's Castle (First Part)", METHOD, .method = Give_GanonFirst_Key},
        {"Ganon's Castle (Floor Beneath Boss Chamber", METHOD, .method = Give_GanonBoss_Key},
        {"Ganon's Castle (Crumbling)", METHOD, .method = Give_GanonCrumbling_Key},
        {"Treasure Chest Shop", METHOD, .method = Give_Treasure_Key},
        {"Deku Tree Boss Room", METHOD, .method = Give_DekuBoss_Key},
        {"Dodongo's Cavern Boss Room", METHOD, .method = Give_DodongoBoss_Key},
        {"Jabu-Jabu's Belly Boss Room", METHOD, .method = Give_JabuBoss_Key},
    }
};

void Cheats_Health(void){
    gSaveContext.health = gSaveContext.healthCapacity;
}

void Cheats_Magic(void){
    gSaveContext.magic = 0x30 * gSaveContext.magicLevel;
}

void Cheats_Sticks(void){
    gSaveContext.ammo[ITEM_DEKU_STICK] = 10 * ((gSaveContext.upgrades >> 17) & 0x7);
}

void Cheats_Nuts(void){
    gSaveContext.ammo[ITEM_DEKU_NUT] = 10 + 10 * ((gSaveContext.upgrades >> 20) & 0x7);
}

void Cheats_Bombs(void){
    gSaveContext.ammo[ITEM_BOMB] = 10 + 10 * ((gSaveContext.upgrades >> 3) & 0x7);
}

void Cheats_Arrows(void){
    gSaveContext.ammo[ITEM_FAIRY_BOW] = 20 + 10 * (gSaveContext.upgrades & 0x7);
}

void Cheats_Slingshot(void){
    gSaveContext.ammo[ITEM_FAIRY_SLINGSHOT] = 20 + 10 * ((gSaveContext.upgrades >> 14) & 0x7);
}

void Cheats_Bombchus(void){
    gSaveContext.ammo[ITEM_BOMBCHU] = 50;
}

void Cheats_Beans(void){
    gSaveContext.ammo[ITEM_MAGIC_BEANS] = 10;
}

void Cheats_Rupees(void){
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

void Cheats_Nayrus(void){ //TODO

}

void Cheats_FreezeTime(void){ //TODO

}

void Cheats_Music(void){ //TODO

}

void Cheats_Usability(void){ //TODO

}

void Cheats_ISG(void){
    PLAYER->isg = 1;
}

void Give_Deku_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_DEKU_TREE]++;
}

void Give_Dodongo_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_DODONGOS_CAVERN]++;
}

void Give_Jabu_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_JABUJABUS_BELLY]++;
}

void Give_Forest_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_FOREST_TEMPLE]++;
}

void Give_Fire_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_FIRE_TEMPLE]++;
}

void Give_Water_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_WATER_TEMPLE]++;
}

void Give_Spirit_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_SPIRIT_TEMPLE]++;
}

void Give_Shadow_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_SHADOW_TEMPLE]++;
}

void Give_Well_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_BOTTOM_OF_THE_WELL]++;
}

void Give_Ice_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_ICE_CAVERN]++;
}

void Give_GanonSecond_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_SECOND_PART]++;
}

void Give_Grounds_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_GERUDO_TRAINING_GROUNDS]++;
}

void Give_Gerudo_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_GERUDO_FORTRESS]++;
}

void Give_GanonFirst_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_FIRST_PART]++;
}

void Give_GanonBoss_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_FLOOR_BENEATH_BOSS_CHAMBER]++;
}

void Give_GanonCrumbling_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_CRUMBLING]++;
}

void Give_Treasure_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_TREASURE_CHEST_SHOP]++;
}

void Give_DekuBoss_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_DEKU_TREE_BOSS_ROOM]++;
}

void Give_DodongoBoss_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_DODONGOS_CAVERN_BOSS_ROOM]++;
}

void Give_JabuBoss_Key(void){
    gSaveContext.dungeonKeys[DUNGEON_JABUJABUS_BELLY_BOSS_ROOM]++;
}
