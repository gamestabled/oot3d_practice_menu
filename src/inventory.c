#include "menu.h"
#include "menus/inventory.h"
#include "draw.h"
#include "z3D/z3D.h"
#include <stdio.h>

static u32 SelectedBottle;

Menu InventoryMenu = {
    "Cheats",
    .nbItems = 5,
    {
        {"Items", METHOD, .method = Inventory_ItemsMenuFunc},
        {"Right Side Gear", METHOD, .method = Inventory_RightGearMenuFunc},
        {"Left Side Gear", METHOD, .method = Inventory_LeftGearMenuFunc},
        {"Ocarina Songs", METHOD, .method = Inventory_SongsMenuFunc},
        {"Amounts", METHOD, .method = Inventory_AmountsMenuFunc},
    }
};

ToggleMenu InventoryItemsMenu = {
    "Items",
    .nbItems = 28,
    {
        {0, "Deku Sticks", .method = Inventory_ItemsToggle},
        {0, "Deku Nut", .method = Inventory_ItemsToggle},
        {0, "Bomb", .method = Inventory_ItemsToggle},
        {0, "Fairy Bow", .method = Inventory_ItemsToggle},
        {0, "Fire Arrow", .method = Inventory_ItemsToggle},
        {0, "Din's Fire", .method = Inventory_ItemsToggle},
        {0, "Fairy Slingshot", .method = Inventory_ItemsToggle},
        {0, "Fairy Ocarina", .method = Inventory_ItemsToggle},
        {0, "Ocarina of Time", .method = Inventory_ItemsToggle},
        {0, "Bombchu", .method = Inventory_ItemsToggle},
        {0, "Hookshot", .method = Inventory_ItemsToggle},
        {0, "Longshot", .method = Inventory_ItemsToggle},
        {0, "Ice Arrow", .method = Inventory_ItemsToggle},
        {0, "Farore's Wind", .method = Inventory_ItemsToggle},
        {0, "Boomerang", .method = Inventory_ItemsToggle},
        {0, "Lens of Truth", .method = Inventory_ItemsToggle},
        {0, "Magic Beans", .method = Inventory_ItemsToggle},
        {0, "Megaton Hammer", .method = Inventory_ItemsToggle},
        {0, "Light Arrow", .method = Inventory_ItemsToggle},
        {0, "Nayru's Love", .method = Inventory_ItemsToggle},
        {0, "Bottle #1", .method = Inventory_BottlesMenuFunc},
        {0, "Bottle #2", .method = Inventory_BottlesMenuFunc},
        {0, "Bottle #3", .method = Inventory_BottlesMenuFunc},
        {0, "Bottle #4", .method = Inventory_BottlesMenuFunc},
        {0, "Child Trade", .method = Inventory_ChildTradeMenuFunc},
        {0, "Adult Trade", .method = Inventory_AdultTradeMenuFunc},
        {0, "Iron Boots", .method = Inventory_BootsToggle},
        {0, "Hover Boots", .method = Inventory_BootsToggle},
    }
};

ToggleMenu InventoryBottlesMenu = {
    "Choose Bottle Contents",
    .nbItems = 14,
    {
        {0, "Empty Bottle", .method = Inventory_BottleSelect},
        {0, "Red Potion", .method = Inventory_BottleSelect},
        {0, "Green Potion", .method = Inventory_BottleSelect},
        {0, "Blue Potion", .method = Inventory_BottleSelect},
        {0, "Bottled Fairy", .method = Inventory_BottleSelect},
        {0, "Fish", .method = Inventory_BottleSelect},
        {0, "Lon Lon Milk", .method = Inventory_BottleSelect},
        {0, "Letter", .method = Inventory_BottleSelect},
        {0, "Blue Fire", .method = Inventory_BottleSelect},
        {0, "Bug", .method = Inventory_BottleSelect},
        {0, "Big Poe", .method = Inventory_BottleSelect},
        {0, "Lon Lon Milk (Half)", .method = Inventory_BottleSelect},
        {0, "Poe", .method = Inventory_BottleSelect},
        {0, "None", .method = Inventory_BottleSelect},
    }
};

ToggleMenu InventoryChildTradeMenu = {
    "Choose Child Trade Item",
    .nbItems = 13,
    {
        {0, "Weird Egg", .method = Inventory_ChildTradeSelect},
        {0, "Cucco", .method = Inventory_ChildTradeSelect},
        {0, "Zelda's Letter", .method = Inventory_ChildTradeSelect},
        {0, "Keaton Mask", .method = Inventory_ChildTradeSelect},
        {0, "Skull Mask", .method = Inventory_ChildTradeSelect},
        {0, "Spooky Mask", .method = Inventory_ChildTradeSelect},
        {0, "Bunny Hood", .method = Inventory_ChildTradeSelect},
        {0, "Goron Mask", .method = Inventory_ChildTradeSelect},
        {0, "Zora Mask", .method = Inventory_ChildTradeSelect},
        {0, "Gerudo Mask", .method = Inventory_ChildTradeSelect},
        {0, "Mask of Truth", .method = Inventory_ChildTradeSelect},
        {0, "No Mask", .method = Inventory_ChildTradeSelect},
        {0, "None", .method = Inventory_ChildTradeSelect},
    }
};

ToggleMenu InventoryAdultTradeMenu = {
    "Choose Adult Trade Item",
    .nbItems = 12,
    {
        {0, "Pocket Egg", .method = Inventory_AdultTradeSelect},
        {0, "Pocket Cucco", .method = Inventory_AdultTradeSelect},
        {0, "Cojiro", .method = Inventory_AdultTradeSelect},
        {0, "Odd Mushroom", .method = Inventory_AdultTradeSelect},
        {0, "Odd Poultice", .method = Inventory_AdultTradeSelect},
        {0, "Poacher's Saw", .method = Inventory_AdultTradeSelect},
        {0, "Goron's Sword (Broken)", .method = Inventory_AdultTradeSelect},
        {0, "Prescription", .method = Inventory_AdultTradeSelect},
        {0, "Eye Ball Frog", .method = Inventory_AdultTradeSelect},
        {0, "Eye Drops", .method = Inventory_AdultTradeSelect},
        {0, "Claim Check", .method = Inventory_AdultTradeSelect},
        {0, "None", .method = Inventory_AdultTradeSelect},
    }
};

ToggleMenu InventoryRightGearMenu = {
    "Right Side Gear",
    .nbItems = 28,
    {
        {0, "Kokiri Sword", .method = Inventory_RightGearToggle},
        {0, "Master Sword", .method = Inventory_RightGearToggle},
        {0, "Giant's Knife", .method = Inventory_RightGearToggle},
        {0, "Broken Giant's Knife", .method = Inventory_RightGearToggle},
        {0, "Biggoron's Sword", .method = Inventory_RightGearToggle},
        {0, "Deku Shield", .method = Inventory_RightGearToggle},
        {0, "Hylian Shield", .method = Inventory_RightGearToggle},
        {0, "Mirror Shield", .method = Inventory_RightGearToggle},
        {0, "Kokiri Tunic", .method = Inventory_RightGearToggle},
        {0, "Goron Tunic", .method = Inventory_RightGearToggle},
        {0, "Zora Tunic", .method = Inventory_RightGearToggle},
        {0, "Bullet Bag 30", .method = Inventory_RightGearToggle},
        {0, "Bullet Bag 40", .method = Inventory_RightGearToggle},
        {0, "Bullet Bag 50", .method = Inventory_RightGearToggle},
        {0, "Quiver 30", .method = Inventory_RightGearToggle},
        {0, "Quiver 40", .method = Inventory_RightGearToggle},
        {0, "Quiver 50", .method = Inventory_RightGearToggle},
        {0, "Bomb Bag 20", .method = Inventory_RightGearToggle},
        {0, "Bomb Bag 30", .method = Inventory_RightGearToggle},
        {0, "Bomb Bag 40", .method = Inventory_RightGearToggle},
        {0, "Goron's Bracelet", .method = Inventory_RightGearToggle},
        {0, "Silver Gauntlets", .method = Inventory_RightGearToggle},
        {0, "Golden Gauntlets", .method = Inventory_RightGearToggle},
        {0, "Silver Scale", .method = Inventory_RightGearToggle},
        {0, "Golden Scale", .method = Inventory_RightGearToggle},
        {0, "Adult's Wallet", .method = Inventory_RightGearToggle},
        {0, "Giant's Wallet", .method = Inventory_RightGearToggle},
        {0, "No Wallet (No Rupees Shown)", .method = Inventory_RightGearToggle},
    }
};

ToggleMenu InventoryLeftGearMenu = {
    "Left Side Gear",
    .nbItems = 13,
    {
        {0, "Forest Medallion", .method = Inventory_LeftGearToggle},
        {0, "Fire Medallion", .method = Inventory_LeftGearToggle},
        {0, "Water Medallion", .method = Inventory_LeftGearToggle},
        {0, "Spirit Medallion", .method = Inventory_LeftGearToggle},
        {0, "Shadow Medallion", .method = Inventory_LeftGearToggle},
        {0, "Light Medallion", .method = Inventory_LeftGearToggle},
        {0, "Kokiri Emerald", .method = Inventory_LeftGearToggle},
        {0, "Goron's Ruby", .method = Inventory_LeftGearToggle},
        {0, "Zora's Sapphire", .method = Inventory_LeftGearToggle},
        {0, "Pieces of Heart (Select to Choose Amount)", .method = Inventory_HeartPiecesAmount},
        {0, "Shard of Agony", .method = Inventory_LeftGearToggle},
        {0, "Gerudo Token", .method = Inventory_LeftGearToggle},
        {0, "Gold Skulltulas (Select to Choose Amount)", .method = Inventory_GoldSkulltulaAmount},
    }
};

ToggleMenu InventorySongsMenu = {
    "Ocarina Songs",
    .nbItems = 12,
    {
        {0, "Zelda's Lullaby", .method = Inventory_SongsToggle},
        {0, "Epona's Song", .method = Inventory_SongsToggle},
        {0, "Saria's Song", .method = Inventory_SongsToggle},
        {0, "Sun's Song", .method = Inventory_SongsToggle},
        {0, "Song of Time", .method = Inventory_SongsToggle},
        {0, "Song of Storms", .method = Inventory_SongsToggle},
        {0, "Minuet of Forest", .method = Inventory_SongsToggle},
        {0, "Bolero of Fire", .method = Inventory_SongsToggle},
        {0, "Serenade of Water", .method = Inventory_SongsToggle},
        {0, "Requiem of Spirit", .method = Inventory_SongsToggle},
        {0, "Nocturne of Shadow", .method = Inventory_SongsToggle},
        {0, "Prelude of Light", .method = Inventory_SongsToggle},
    }
};

AmountMenu InventoryAmountsMenu = {
    "Edit Amounts",
    .nbItems = 14,
    {
        {0, 0, "Deku Sticks", .method = Inventory_AmountsSelect},
        {0, 0, "Deku Nuts", .method = Inventory_AmountsSelect},
        {0, 0, "Bombs", .method = Inventory_AmountsSelect},
        {0, 0, "Arrows", .method = Inventory_AmountsSelect},
        {0, 0, "Deku Seeds", .method = Inventory_AmountsSelect},
        {0, 0, "Bombchus", .method = Inventory_AmountsSelect},
        {0, 0, "Magic Beans", .method = Inventory_AmountsSelect},
        {0, 0, "Rupees", .method = Inventory_AmountsSelect},
        {0, 0, "Giant's Knife hits remaining", .method = Inventory_AmountsSelect},
        {0, 0, "Double Defense (1 for on, 0 for off)", .method = Inventory_AmountsSelect},
        {0, 0, "Magic meter size (1 for normal, 2 for double)", .method = Inventory_AmountsSelect},
        {0, 1, "Heart Containers (0x10 per container)", .method = Inventory_AmountsSelect},
        {0, 1, "Current Health (0x10 per container)", .method = Inventory_AmountsSelect},
        {0, 1, "Current Magic (0x30 for normal, 0x60 for double)", .method = Inventory_AmountsSelect},
    }
};

static void ResetSlotsIfMatchesID(u8 id) {
    // Need to remove the slot from child/adult grids
    for (u32 i = 0; i < 0x18; ++i) {
        if (gSaveContext.itemMenuChild[i] == id) {
            gSaveContext.itemMenuChild[i] = 0xFF;
        }
        if (gSaveContext.itemMenuAdult[i] == id) {
            gSaveContext.itemMenuAdult[i] = 0xFF;
        }
    }
}

static void SetMenuToggle(ToggleMenu* menu, u32 selected) {
    for (u32 i = 0; i < menu->nbItems; ++i) {
        menu->items[i].on = (i == selected ? 1 : 0);
    }
}

static void DisableMenuToggles(ToggleMenu* menu) {
    for (u32 i = 0; i < menu->nbItems - 1; ++i) {
        menu->items[i].on = 0;
    }
}

static void Inventory_ItemsMenuInit(void){
    InventoryItemsMenu.items[ITEM_DEKU_STICK].on = (gSaveContext.items[ItemSlots[ITEM_DEKU_STICK]] == ITEM_DEKU_STICK);
    InventoryItemsMenu.items[ITEM_DEKU_NUT].on = (gSaveContext.items[ItemSlots[ITEM_DEKU_NUT]] == ITEM_DEKU_NUT);
    InventoryItemsMenu.items[ITEM_BOMB].on = (gSaveContext.items[ItemSlots[ITEM_BOMB]] == ITEM_BOMB);
    InventoryItemsMenu.items[ITEM_FAIRY_BOW].on = (gSaveContext.items[ItemSlots[ITEM_FAIRY_BOW]] == ITEM_FAIRY_BOW);
    InventoryItemsMenu.items[ITEM_FIRE_ARROW].on = (gSaveContext.items[ItemSlots[ITEM_FIRE_ARROW]] == ITEM_FIRE_ARROW);
    InventoryItemsMenu.items[ITEM_DINS_FIRE].on = (gSaveContext.items[ItemSlots[ITEM_DINS_FIRE]] == ITEM_DINS_FIRE);
    InventoryItemsMenu.items[ITEM_FAIRY_SLINGSHOT].on = (gSaveContext.items[ItemSlots[ITEM_FAIRY_SLINGSHOT]] == ITEM_FAIRY_SLINGSHOT);
    InventoryItemsMenu.items[ITEM_FAIRY_OCARINA].on = (gSaveContext.items[ItemSlots[ITEM_FAIRY_OCARINA]] == ITEM_FAIRY_OCARINA);
    InventoryItemsMenu.items[ITEM_OCARINA_OF_TIME].on = (gSaveContext.items[ItemSlots[ITEM_OCARINA_OF_TIME]] == ITEM_OCARINA_OF_TIME);
    InventoryItemsMenu.items[ITEM_BOMBCHU].on = (gSaveContext.items[ItemSlots[ITEM_BOMBCHU]] == ITEM_BOMBCHU);
    InventoryItemsMenu.items[ITEM_HOOKSHOT].on = (gSaveContext.items[ItemSlots[ITEM_HOOKSHOT]] == ITEM_HOOKSHOT);
    InventoryItemsMenu.items[ITEM_LONGSHOT].on = (gSaveContext.items[ItemSlots[ITEM_LONGSHOT]] == ITEM_LONGSHOT);
    InventoryItemsMenu.items[ITEM_ICE_ARROW].on = (gSaveContext.items[ItemSlots[ITEM_ICE_ARROW]] == ITEM_ICE_ARROW);
    InventoryItemsMenu.items[ITEM_FARORES_WIND].on = (gSaveContext.items[ItemSlots[ITEM_FARORES_WIND]] == ITEM_FARORES_WIND);
    InventoryItemsMenu.items[ITEM_BOOMERANG].on = (gSaveContext.items[ItemSlots[ITEM_BOOMERANG]] == ITEM_BOOMERANG);
    InventoryItemsMenu.items[ITEM_LENS_OF_TRUTH].on = (gSaveContext.items[ItemSlots[ITEM_LENS_OF_TRUTH]] == ITEM_LENS_OF_TRUTH);
    InventoryItemsMenu.items[ITEM_MAGIC_BEANS].on = (gSaveContext.items[ItemSlots[ITEM_MAGIC_BEANS]] == ITEM_MAGIC_BEANS);
    InventoryItemsMenu.items[ITEM_MEGATON_HAMMER].on = (gSaveContext.items[ItemSlots[ITEM_MEGATON_HAMMER]] == ITEM_MEGATON_HAMMER);
    InventoryItemsMenu.items[ITEM_LIGHT_ARROW].on = (gSaveContext.items[ItemSlots[ITEM_LIGHT_ARROW]] == ITEM_LIGHT_ARROW);
    InventoryItemsMenu.items[ITEM_NAYRUS_LOVE].on = (gSaveContext.items[ItemSlots[ITEM_NAYRUS_LOVE]] == ITEM_NAYRUS_LOVE);
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE].on = (gSaveContext.items[ItemSlots[ITEM_EMPTY_BOTTLE]] != ITEM_EMPTY);
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 1].on = (gSaveContext.items[ItemSlots[ITEM_EMPTY_BOTTLE] + 1] != ITEM_EMPTY);
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 2].on = (gSaveContext.items[ItemSlots[ITEM_EMPTY_BOTTLE] + 2] != ITEM_EMPTY);
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 3].on = (gSaveContext.items[ItemSlots[ITEM_EMPTY_BOTTLE] + 3] != ITEM_EMPTY);
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 4].on = (gSaveContext.items[ItemSlots[ITEM_WEIRD_EGG]] != ITEM_EMPTY); //TODO: index on left
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 5].on = (gSaveContext.items[ItemSlots[ITEM_POCKET_EGG]] != ITEM_EMPTY); //TODO: index on left
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 6].on = (gSaveContext.items[ItemSlots[ITEM_POCKET_EGG] + 1] == ITEM_IRON_BOOTS); //TODO
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 7].on = (gSaveContext.items[ItemSlots[ITEM_POCKET_EGG] + 2] == ITEM_HOVER_BOOTS); //TODO
}

void Inventory_ItemsMenuFunc(void){
    Inventory_ItemsMenuInit();
    ToggleMenuShow(&InventoryItemsMenu);
}

void Inventory_ItemsToggle(s32 selected){
    switch(selected) {
        case(ITEM_FAIRY_OCARINA):
            if (gSaveContext.items[ItemSlots[ITEM_FAIRY_OCARINA]] != ITEM_FAIRY_OCARINA){
                gSaveContext.items[ItemSlots[ITEM_FAIRY_OCARINA]] = ITEM_FAIRY_OCARINA;
                InventoryItemsMenu.items[ITEM_FAIRY_OCARINA].on = 1;
                InventoryItemsMenu.items[ITEM_OCARINA_OF_TIME].on = 0; //turn off Ocarina of Time in menu
            }
            else {
                gSaveContext.items[ItemSlots[ITEM_FAIRY_OCARINA]] = ITEM_EMPTY;
                InventoryItemsMenu.items[ITEM_FAIRY_OCARINA].on = 0;
                InventoryItemsMenu.items[ITEM_OCARINA_OF_TIME].on = 0;
            }
            break;
        case(ITEM_OCARINA_OF_TIME):
            if (gSaveContext.items[ItemSlots[ITEM_OCARINA_OF_TIME]] != ITEM_OCARINA_OF_TIME){
                gSaveContext.items[ItemSlots[ITEM_OCARINA_OF_TIME]] = ITEM_OCARINA_OF_TIME;
                InventoryItemsMenu.items[ITEM_FAIRY_OCARINA].on = 0; //turn off Fairy Ocarina in menu
                InventoryItemsMenu.items[ITEM_OCARINA_OF_TIME].on = 1; 
            }
            else {
                gSaveContext.items[ItemSlots[ITEM_OCARINA_OF_TIME]] = ITEM_EMPTY;
                InventoryItemsMenu.items[ITEM_FAIRY_OCARINA].on = 0;
                InventoryItemsMenu.items[ITEM_OCARINA_OF_TIME].on = 0;
            }
            break;
        case(ITEM_HOOKSHOT):
            if (gSaveContext.items[ItemSlots[ITEM_HOOKSHOT]] != ITEM_HOOKSHOT){
                gSaveContext.items[ItemSlots[ITEM_HOOKSHOT]] = ITEM_HOOKSHOT;
                InventoryItemsMenu.items[ITEM_HOOKSHOT].on = 1;
                InventoryItemsMenu.items[ITEM_LONGSHOT].on = 0; //turn off Longshot in menu 
            }
            else {
                gSaveContext.items[ItemSlots[ITEM_HOOKSHOT]] = ITEM_EMPTY;
                ResetSlotsIfMatchesID(ItemSlots[ITEM_HOOKSHOT]);
                InventoryItemsMenu.items[ITEM_HOOKSHOT].on = 0;
                InventoryItemsMenu.items[ITEM_LONGSHOT].on = 0;
            }
            break;
        case(ITEM_LONGSHOT):
            if (gSaveContext.items[ItemSlots[ITEM_LONGSHOT]] != ITEM_LONGSHOT){
                gSaveContext.items[ItemSlots[ITEM_LONGSHOT]] = ITEM_LONGSHOT;
                InventoryItemsMenu.items[ITEM_HOOKSHOT].on = 0; //turn off Hookshot in menu
                InventoryItemsMenu.items[ITEM_LONGSHOT].on = 1;  
            }
            else {
                gSaveContext.items[ItemSlots[ITEM_LONGSHOT]] = ITEM_EMPTY;
                ResetSlotsIfMatchesID(ItemSlots[ITEM_LONGSHOT]);
                InventoryItemsMenu.items[ITEM_HOOKSHOT].on = 0;
                InventoryItemsMenu.items[ITEM_LONGSHOT].on = 0;
            }
            break;
        default:
            if (gSaveContext.items[ItemSlots[selected]] != selected){
                gSaveContext.items[ItemSlots[selected]] = selected;
                InventoryItemsMenu.items[selected].on = 1;
            }
            else {
                gSaveContext.items[ItemSlots[selected]] = ITEM_EMPTY;
                ResetSlotsIfMatchesID(ItemSlots[selected]);
                InventoryItemsMenu.items[selected].on = 0;
            }
            break;
    }
}

static void Inventory_BottlesMenuInit(void){
    for (u32 i = 0; i < ITEM_WEIRD_EGG - ITEM_EMPTY_BOTTLE; ++i){
        InventoryBottlesMenu.items[i].on = (gSaveContext.items[ItemSlots[ITEM_EMPTY_BOTTLE] + SelectedBottle] == ITEM_EMPTY_BOTTLE + i);
    }
    InventoryBottlesMenu.items[ITEM_WEIRD_EGG - ITEM_EMPTY_BOTTLE].on = (gSaveContext.items[ItemSlots[ITEM_EMPTY_BOTTLE] + SelectedBottle] == ITEM_EMPTY);
}

void Inventory_BottlesMenuFunc(s32 selected){
    SelectedBottle = selected - ITEM_EMPTY_BOTTLE;
    Inventory_BottlesMenuInit();
    ToggleMenuShow(&InventoryBottlesMenu);
}

void Inventory_BottleSelect(s32 selected){
    if (selected < ITEM_WEIRD_EGG - ITEM_EMPTY_BOTTLE){ //selected a bottled content
        gSaveContext.items[ItemSlots[ITEM_EMPTY_BOTTLE] + SelectedBottle] = ITEM_EMPTY_BOTTLE + selected;
        SetMenuToggle(&InventoryBottlesMenu, selected);
        InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + SelectedBottle].on = 1;
    }
    else { //erase the bottle
        gSaveContext.items[ItemSlots[ITEM_EMPTY_BOTTLE] + SelectedBottle] = ITEM_EMPTY;
        ResetSlotsIfMatchesID(ItemSlots[ITEM_EMPTY_BOTTLE] + SelectedBottle);
        DisableMenuToggles(&InventoryBottlesMenu);
        InventoryBottlesMenu.items[InventoryBottlesMenu.nbItems - 1].on = 1;
        InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + SelectedBottle].on = 0;
    }
}

static void Inventory_ChildTradeMenuInit(void){
    for (u32 i = 0; i < ITEM_POCKET_EGG - ITEM_WEIRD_EGG; ++i){
        InventoryChildTradeMenu.items[i].on = (gSaveContext.items[ItemSlots[ITEM_WEIRD_EGG]] == ITEM_WEIRD_EGG + i);
    }
    InventoryChildTradeMenu.items[ITEM_POCKET_EGG - ITEM_WEIRD_EGG].on = (gSaveContext.items[ItemSlots[ITEM_WEIRD_EGG]] == ITEM_EMPTY);
}

void Inventory_ChildTradeMenuFunc(s32 selected){
    Inventory_ChildTradeMenuInit();
    ToggleMenuShow(&InventoryChildTradeMenu);
}

void Inventory_ChildTradeSelect(s32 selected){ //TODO: remove hardcoded indexes
    if (selected < ITEM_POCKET_EGG - ITEM_WEIRD_EGG){ //selected a child trade item
        gSaveContext.items[ItemSlots[ITEM_WEIRD_EGG]] = ITEM_WEIRD_EGG + selected;
        SetMenuToggle(&InventoryChildTradeMenu, selected);
        InventoryItemsMenu.items[24].on = 1;
    }
    else { //erase the child trade item
        gSaveContext.items[ItemSlots[ITEM_WEIRD_EGG]] = ITEM_EMPTY;
        ResetSlotsIfMatchesID(ItemSlots[ITEM_WEIRD_EGG]);
        DisableMenuToggles(&InventoryChildTradeMenu);
        InventoryChildTradeMenu.items[InventoryChildTradeMenu.nbItems - 1].on = 1;
        InventoryItemsMenu.items[24].on = 0;
    }
}

static void Inventory_AdultTradeMenuInit(void){
    for (u32 i = 0; i < ITEM_FAIRY_BOW_PLUS_FIRE_ARROW - ITEM_POCKET_EGG; ++i){
        InventoryAdultTradeMenu.items[i].on = (gSaveContext.items[ItemSlots[ITEM_POCKET_EGG]] == ITEM_POCKET_EGG + i);
    }
    InventoryAdultTradeMenu.items[ITEM_FAIRY_BOW_PLUS_FIRE_ARROW - ITEM_POCKET_EGG].on = (gSaveContext.items[ItemSlots[ITEM_POCKET_EGG]] == ITEM_EMPTY);    
}

void Inventory_AdultTradeMenuFunc(s32 selected){
    Inventory_AdultTradeMenuInit();
    ToggleMenuShow(&InventoryAdultTradeMenu);
}

void Inventory_AdultTradeSelect(s32 selected){ //TODO: remove hardcoded indexes
    if (selected < ITEM_FAIRY_BOW_PLUS_FIRE_ARROW - ITEM_POCKET_EGG){ //selected an adult trade item
        gSaveContext.items[ItemSlots[ITEM_POCKET_EGG]] = ITEM_POCKET_EGG + selected;
        SetMenuToggle(&InventoryAdultTradeMenu, selected);
        InventoryItemsMenu.items[25].on = 1;
    }
    else { //erase the adult trade item
        gSaveContext.items[ItemSlots[ITEM_POCKET_EGG]] = ITEM_EMPTY;
        ResetSlotsIfMatchesID(ItemSlots[ITEM_POCKET_EGG]);
        DisableMenuToggles(&InventoryAdultTradeMenu);
        InventoryAdultTradeMenu.items[InventoryAdultTradeMenu.nbItems - 1].on = 1;
        InventoryItemsMenu.items[25].on = 0;
    }
}

void Inventory_BootsToggle(s32 selected){ //TODO: remove hardcoded values
    //put boots in their slots
    //set boots bits in gear
    if (selected == 26){ //Iron boots
        if (gSaveContext.items[24] != ITEM_IRON_BOOTS){
            gSaveContext.items[24] = ITEM_IRON_BOOTS;
            gSaveContext.equipment |= (1 << 13);
            InventoryItemsMenu.items[selected].on = 1;
        }
        else {
            gSaveContext.items[24] = ITEM_EMPTY;
            gSaveContext.equipment &= ~(1 << 13);
            ResetSlotsIfMatchesID(24);
            InventoryItemsMenu.items[selected].on = 0;
        }
    }
    else { //Hover boots
        if (gSaveContext.items[25] != ITEM_HOVER_BOOTS){
            gSaveContext.items[25] = ITEM_HOVER_BOOTS;
            gSaveContext.equipment |= (1 << 14);
            InventoryItemsMenu.items[selected].on = 1;
        }
        else {
            gSaveContext.items[25] = ITEM_EMPTY;
            gSaveContext.equipment &= ~(1 << 14);
            ResetSlotsIfMatchesID(25);
            InventoryItemsMenu.items[selected].on = 0;
        }
    }
}

static void Inventory_RightGearMenu_Init(void){
    InventoryRightGearMenu.items[Gear_Menu_Kokiri_Sword].on = ((gSaveContext.equipment & 1) != 0);
    InventoryRightGearMenu.items[Gear_Menu_Master_Sword].on = ((gSaveContext.equipment & (1 << 1)) != 0);
    InventoryRightGearMenu.items[Gear_Menu_Giants_Knife].on = (((gSaveContext.equipment & (1 << 2)) != 0) && ((gSaveContext.equipment & (1 << 3)) == 0) && !gSaveContext.bgsFlag);
    InventoryRightGearMenu.items[Gear_Menu_Broken_Giants_Knife].on = (((gSaveContext.equipment & (1 << 2)) != 0) && ((gSaveContext.equipment & (1 << 3)) != 0));
    InventoryRightGearMenu.items[Gear_Menu_Biggoron_Sword].on = (((gSaveContext.equipment & (1 << 2)) != 0) && gSaveContext.bgsFlag);
    InventoryRightGearMenu.items[Gear_Menu_Deku_Shield].on = ((gSaveContext.equipment & (1 << 4)) != 0);
    InventoryRightGearMenu.items[Gear_Menu_Hylian_Shield].on = ((gSaveContext.equipment & (1 << 5)) != 0);
    InventoryRightGearMenu.items[Gear_Menu_Mirror_Shield].on = ((gSaveContext.equipment & (1 << 6)) != 0);
    InventoryRightGearMenu.items[Gear_Menu_Kokiri_Tunic].on = ((gSaveContext.equipment & (1 << 8)) != 0);
    InventoryRightGearMenu.items[Gear_Menu_Goron_Tunic].on = ((gSaveContext.equipment & (1 << 9)) != 0);
    InventoryRightGearMenu.items[Gear_Menu_Zora_Tunic].on = ((gSaveContext.equipment & (1 << 10)) != 0);
    InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = (((gSaveContext.upgrades >> 14) & 7) == BULLET_BAG_30);
    InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = (((gSaveContext.upgrades >> 14) & 7) == BULLET_BAG_40);
    InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = (((gSaveContext.upgrades >> 14) & 7) == BULLET_BAG_50);
    InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = ((gSaveContext.upgrades & 7) == QUIVER_30);
    InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = ((gSaveContext.upgrades & 7) == QUIVER_40);
    InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = ((gSaveContext.upgrades & 7) == QUIVER_50);
    InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = (((gSaveContext.upgrades >> 3) & 7) == BOMB_BAG_20);
    InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = (((gSaveContext.upgrades >> 3) & 7) == BOMB_BAG_30);
    InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = (((gSaveContext.upgrades >> 3) & 7) == BOMB_BAG_40);
    InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = (((gSaveContext.upgrades >> 6) & 7) == GORON_BRACELET);
    InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = (((gSaveContext.upgrades >> 6) & 7) == SILVER_GAUNTLETS);
    InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = (((gSaveContext.upgrades >> 6) & 7) == GOLDEN_GAUNTLETS);
    InventoryRightGearMenu.items[Gear_Menu_Silver_Scale].on = (((gSaveContext.upgrades >> 9) & 7) == SILVER_SCALE);
    InventoryRightGearMenu.items[Gear_Menu_Golden_Scale].on = (((gSaveContext.upgrades >> 9) & 7) == GOLDEN_SCALE);
    InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = (((gSaveContext.upgrades >> 12) & 3) == ADULTS_WALLET);
    InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = (((gSaveContext.upgrades >> 12) & 3) == GIANTS_WALLET);
    InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = (((gSaveContext.upgrades >> 12) & 3) == NO_RUPEES_SHOWN);
}

void Inventory_RightGearMenuFunc(void){
    Inventory_RightGearMenu_Init();
    ToggleMenuShow(&InventoryRightGearMenu);
}

void Inventory_RightGearToggle(s32 selected){
    switch(selected){
        case(Gear_Menu_Kokiri_Sword):
            gSaveContext.equipment ^= 1;
            InventoryRightGearMenu.items[Gear_Menu_Kokiri_Sword].on = ((gSaveContext.equipment & 1) != 0);
            break;
        case(Gear_Menu_Master_Sword):
            gSaveContext.equipment ^= (1 << 1);
            InventoryRightGearMenu.items[Gear_Menu_Master_Sword].on = ((gSaveContext.equipment & (1 << 1)) != 0);
            break;
        case(Gear_Menu_Giants_Knife): 
            if ((gSaveContext.equipment & (1 << 2)) && !(gSaveContext.equipment & (1 << 3)) && !gSaveContext.bgsFlag){
                gSaveContext.equipment &= ~(0x3 << 2);
                gSaveContext.bgsFlag = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Knife].on = 0;
            }
            else {
                gSaveContext.equipment &= ~(0x3 << 2);
                gSaveContext.equipment |= (1 << 2);
                gSaveContext.bgsFlag = 0;
                gSaveContext.bgsHitsLeft = 8;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Knife].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Broken_Giants_Knife].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Biggoron_Sword].on = 0;
            }
            break;
        case(Gear_Menu_Broken_Giants_Knife):
            if ((gSaveContext.equipment & (1 << 2)) && (gSaveContext.equipment & (1 << 3))){
                gSaveContext.equipment &= ~(0x3 << 2);
                gSaveContext.bgsFlag = 0;
                InventoryRightGearMenu.items[Gear_Menu_Broken_Giants_Knife].on = 0;
            }
            else {
                gSaveContext.equipment |= (0x3 << 2);
                gSaveContext.bgsFlag = 0;
                gSaveContext.bgsHitsLeft = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Knife].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Broken_Giants_Knife].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Biggoron_Sword].on = 0;
            }
            break;
        case(Gear_Menu_Biggoron_Sword):
            if ((gSaveContext.equipment & (1 << 2)) && gSaveContext.bgsFlag){
                gSaveContext.equipment &= ~(0x3 << 2);
                gSaveContext.bgsFlag = 0;
                InventoryRightGearMenu.items[Gear_Menu_Biggoron_Sword].on = 0;
            }
            else {
                gSaveContext.equipment &= ~(0x3 << 2);
                gSaveContext.equipment |= (1 << 2);
                gSaveContext.bgsFlag = 1;
                gSaveContext.bgsHitsLeft = 1;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Knife].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Broken_Giants_Knife].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Biggoron_Sword].on = 1;
            }
            break;
        case(Gear_Menu_Deku_Shield):
            gSaveContext.equipment ^= (1 << 4);
            InventoryRightGearMenu.items[Gear_Menu_Deku_Shield].on = ((gSaveContext.equipment & (1 << 4)) != 0);
            break;
        case(Gear_Menu_Hylian_Shield):
            gSaveContext.equipment ^= (1 << 5);
            InventoryRightGearMenu.items[Gear_Menu_Hylian_Shield].on = ((gSaveContext.equipment & (1 << 5)) != 0);
            break;
        case(Gear_Menu_Mirror_Shield):
            gSaveContext.equipment ^= (1 << 6);
            InventoryRightGearMenu.items[Gear_Menu_Mirror_Shield].on = ((gSaveContext.equipment & (1 << 6)) != 0);
            break;
        case(Gear_Menu_Kokiri_Tunic):
            gSaveContext.equipment ^= (1 << 8);
            InventoryRightGearMenu.items[Gear_Menu_Kokiri_Tunic].on = ((gSaveContext.equipment & (1 << 8)) != 0);
            break;
        case(Gear_Menu_Goron_Tunic):
            gSaveContext.equipment ^= (1 << 9);
            InventoryRightGearMenu.items[Gear_Menu_Goron_Tunic].on = ((gSaveContext.equipment & (1 << 9)) != 0);
            break;
        case(Gear_Menu_Zora_Tunic):
            gSaveContext.equipment ^= (1 << 10);
            InventoryRightGearMenu.items[Gear_Menu_Zora_Tunic].on = ((gSaveContext.equipment & (1 << 10)) != 0);
            break;
        case(Gear_Menu_Bullet_Bag_30):
            if (((gSaveContext.upgrades >> 14) & 0x7) != BULLET_BAG_30){
                gSaveContext.upgrades &= ~(0x7 << 14);
                gSaveContext.upgrades |= (BULLET_BAG_30 << 14);
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 0;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 14);
                gSaveContext.upgrades |= (NO_BULLET_BAG << 14);
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 0;
            }
            break;
        case(Gear_Menu_Bullet_Bag_40):
            if (((gSaveContext.upgrades >> 14) & 0x7) != BULLET_BAG_40){
                gSaveContext.upgrades &= ~(0x7 << 14);
                gSaveContext.upgrades |= (BULLET_BAG_40 << 14);
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 0;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 14);
                gSaveContext.upgrades |= (NO_BULLET_BAG << 14);
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 0;
            }
            break;
        case(Gear_Menu_Bullet_Bag_50):
            if (((gSaveContext.upgrades >> 14) & 0x7) != BULLET_BAG_50){
                gSaveContext.upgrades &= ~(0x7 << 14);
                gSaveContext.upgrades |= (BULLET_BAG_50 << 14);
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 1;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 14);
                gSaveContext.upgrades |= (NO_BULLET_BAG << 14);
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 0;
            }
            break;
        case(Gear_Menu_Quiver_30):
            if ((gSaveContext.upgrades & 0x7) != QUIVER_30){
                gSaveContext.upgrades &= ~0x7;
                gSaveContext.upgrades |= QUIVER_30;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 0;
            }
            else {
                gSaveContext.upgrades &= ~0x7;
                gSaveContext.upgrades |= NO_QUIVER;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 0;
            }
            break;
        case(Gear_Menu_Quiver_40):
            if ((gSaveContext.upgrades & 0x7) != QUIVER_40){
                gSaveContext.upgrades &= ~0x7;
                gSaveContext.upgrades |= QUIVER_40;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 0;
            }
            else {
                gSaveContext.upgrades &= ~0x7;
                gSaveContext.upgrades |= NO_QUIVER;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 0;
            }
            break;
        case(Gear_Menu_Quiver_50):
            if ((gSaveContext.upgrades & 0x7) != QUIVER_50){
                gSaveContext.upgrades &= ~0x7;
                gSaveContext.upgrades |= QUIVER_50;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 1;
            }
            else {
                gSaveContext.upgrades &= ~0x7;
                gSaveContext.upgrades |= NO_QUIVER;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 0;
            }
            break;
        case(Gear_Menu_Bomb_Bag_20):
            if (((gSaveContext.upgrades >> 3) & 0x7) != BOMB_BAG_20){
                gSaveContext.upgrades &= ~(0x7 << 3);
                gSaveContext.upgrades |= (BOMB_BAG_20 << 3);
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 0;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 3);
                gSaveContext.upgrades |= (NO_BOMB_BAG << 3);
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 0;
            }
            break;
        case(Gear_Menu_Bomb_Bag_30):    
            if (((gSaveContext.upgrades >> 3) & 0x7) != BOMB_BAG_30){
                gSaveContext.upgrades &= ~(0x7 << 3);
                gSaveContext.upgrades |= (BOMB_BAG_30 << 3);
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 0;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 3);
                gSaveContext.upgrades |= (NO_BOMB_BAG << 3);
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 0;
            }
            break;
        case(Gear_Menu_Bomb_Bag_40):
            if (((gSaveContext.upgrades >> 3) & 0x7) != BOMB_BAG_40){
                gSaveContext.upgrades &= ~(0x7 << 3);
                gSaveContext.upgrades |= (BOMB_BAG_40 << 3);
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 1;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 3);
                gSaveContext.upgrades |= (NO_BOMB_BAG << 3);
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 0;
            }
            break;
        case(Gear_Menu_Gorons_Bracelet):
            if (((gSaveContext.upgrades >> 6) & 0x7) != GORON_BRACELET){
                gSaveContext.upgrades &= ~(0x7 << 6);
                gSaveContext.upgrades |= (GORON_BRACELET << 6);
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 0;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 6);
                gSaveContext.upgrades |= (NO_STRENGTH << 6);
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 0;
            }
            break;
        case(Gear_Menu_Silver_Gauntlets):
            if (((gSaveContext.upgrades >> 6) & 0x7) != SILVER_GAUNTLETS){
                gSaveContext.upgrades &= ~(0x7 << 6);
                gSaveContext.upgrades |= (SILVER_GAUNTLETS << 6);
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 0;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 6);
                gSaveContext.upgrades |= (NO_STRENGTH << 6);
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 0;
            }
            break;
        case(Gear_Menu_Golden_Gauntlets):
            if (((gSaveContext.upgrades >> 6) & 0x7) != GOLDEN_GAUNTLETS){
                gSaveContext.upgrades &= ~(0x7 << 6);
                gSaveContext.upgrades |= (GOLDEN_GAUNTLETS << 6);
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 1;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 6);
                gSaveContext.upgrades |= (NO_STRENGTH << 6);
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 0;
            }
            break;
        case(Gear_Menu_Silver_Scale):
            if (((gSaveContext.upgrades >> 9) & 0x7) != SILVER_SCALE){
                gSaveContext.upgrades &= ~(0x7 << 9);
                gSaveContext.upgrades |= (SILVER_SCALE << 9);
                InventoryRightGearMenu.items[Gear_Menu_Silver_Scale].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Scale].on = 0;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 9);
                gSaveContext.upgrades |= (NO_DIVE_UPGRADE << 9);
                InventoryRightGearMenu.items[Gear_Menu_Silver_Scale].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Scale].on = 0;
            }
            break;
        case(Gear_Menu_Golden_Scale):
            if (((gSaveContext.upgrades >> 9) & 0x7) != GOLDEN_SCALE){
                gSaveContext.upgrades &= ~(0x7 << 9);
                gSaveContext.upgrades |= (GOLDEN_SCALE << 9);
                InventoryRightGearMenu.items[Gear_Menu_Silver_Scale].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Scale].on = 1;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 9);
                gSaveContext.upgrades |= (NO_DIVE_UPGRADE << 9);
                InventoryRightGearMenu.items[Gear_Menu_Silver_Scale].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Scale].on = 0;
            }
            break;
        case(Gear_Menu_Adults_Wallet):
            if (((gSaveContext.upgrades >> 12) & 0x3) != ADULTS_WALLET){
                gSaveContext.upgrades &= ~(0x7 << 12);
                gSaveContext.upgrades |= (ADULTS_WALLET << 12);
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 0;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 12);
                gSaveContext.upgrades |= (DEFAULT_WALLET << 12);
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 0;
            }
            break;
        case(Gear_Menu_Giants_Wallet):
            if (((gSaveContext.upgrades >> 12) & 0x3) != GIANTS_WALLET){
                gSaveContext.upgrades &= ~(0x7 << 12);
                gSaveContext.upgrades |= (GIANTS_WALLET << 12);
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 0;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 12);
                gSaveContext.upgrades |= (DEFAULT_WALLET << 12);
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 0;
            }
            break;
        case(Gear_Menu_No_Wallet):
            if (((gSaveContext.upgrades >> 12) & 0x3) != NO_RUPEES_SHOWN){
                gSaveContext.upgrades &= ~(0x7 << 12);
                gSaveContext.upgrades |= (NO_RUPEES_SHOWN << 12);
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 1;
            }
            else {
                gSaveContext.upgrades &= ~(0x7 << 12);
                gSaveContext.upgrades |= (DEFAULT_WALLET << 12);
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 0;
            }
            break;
    }
}

static void Inventory_LeftGearMenuInit(void){
    InventoryLeftGearMenu.items[Gear_Menu_Forest_Medallion].on = gSaveContext.questItems & 1;
    InventoryLeftGearMenu.items[Gear_Menu_Fire_Medallion].on = gSaveContext.questItems & (1 << 1);
    InventoryLeftGearMenu.items[Gear_Menu_Water_Medallion].on = gSaveContext.questItems & (1 << 2);
    InventoryLeftGearMenu.items[Gear_Menu_Spirit_Medallion].on = gSaveContext.questItems & (1 << 3);
    InventoryLeftGearMenu.items[Gear_Menu_Shadow_Medallion].on = gSaveContext.questItems & (1 << 4);
    InventoryLeftGearMenu.items[Gear_Menu_Light_Medallion].on = gSaveContext.questItems & (1 << 5);
    InventoryLeftGearMenu.items[Gear_Menu_Kokiri_Emerald].on = gSaveContext.questItems & (1 << 18);
    InventoryLeftGearMenu.items[Gear_Menu_Gorons_Ruby].on = gSaveContext.questItems & (1 << 19);
    InventoryLeftGearMenu.items[Gear_Menu_Zoras_Sapphire].on = gSaveContext.questItems & (1 << 20);
    InventoryLeftGearMenu.items[Gear_Menu_Pieces_of_Heart].on = ((gSaveContext.questItems >> 24) >> 4 != 0);
    InventoryLeftGearMenu.items[Gear_Menu_Shard_of_Agony].on = ((gSaveContext.questItems & (1 << 21)) != 0);
    InventoryLeftGearMenu.items[Gear_Menu_Gerudo_Token].on = ((gSaveContext.questItems & (1 << 22)) != 0);
    InventoryLeftGearMenu.items[Gear_Menu_Gold_Skulltulas].on = ((gSaveContext.questItems & (1 << 23)) != 0);
}

void Inventory_LeftGearMenuFunc(void){
    Inventory_LeftGearMenuInit();
    ToggleMenuShow(&InventoryLeftGearMenu);
}

void Inventory_LeftGearToggle(s32 selected){
    switch(selected){
        case(Gear_Menu_Forest_Medallion):
            gSaveContext.questItems ^= 1;
            InventoryLeftGearMenu.items[Gear_Menu_Forest_Medallion].on = ((gSaveContext.questItems & 1) != 0);
            break;
        case(Gear_Menu_Fire_Medallion):
            gSaveContext.questItems ^= (1 << 1);
            InventoryLeftGearMenu.items[Gear_Menu_Fire_Medallion].on = ((gSaveContext.questItems & (1 << 1)) != 0);
            break;
        case(Gear_Menu_Water_Medallion):
            gSaveContext.questItems ^= (1 << 2);
            InventoryLeftGearMenu.items[Gear_Menu_Water_Medallion].on = ((gSaveContext.questItems & (1 << 2)) != 0);
            break;
        case(Gear_Menu_Spirit_Medallion):
            gSaveContext.questItems ^= (1 << 3);
            InventoryLeftGearMenu.items[Gear_Menu_Spirit_Medallion].on = ((gSaveContext.questItems & (1 << 3)) != 0);
            break;
        case(Gear_Menu_Shadow_Medallion):
            gSaveContext.questItems ^= (1 << 4);
            InventoryLeftGearMenu.items[Gear_Menu_Shadow_Medallion].on = ((gSaveContext.questItems & (1 << 4)) != 0);
            break;
        case(Gear_Menu_Light_Medallion):
            gSaveContext.questItems ^= (1 << 5);
            InventoryLeftGearMenu.items[Gear_Menu_Light_Medallion].on = ((gSaveContext.questItems & (1 << 5)) != 0);
            break;
        case(Gear_Menu_Kokiri_Emerald):
            gSaveContext.questItems ^= (1 << 18);
            InventoryLeftGearMenu.items[Gear_Menu_Kokiri_Emerald].on = ((gSaveContext.questItems & (1 << 18)) != 0);
            break;
        case(Gear_Menu_Gorons_Ruby):
            gSaveContext.questItems ^= (1 << 19);
            InventoryLeftGearMenu.items[Gear_Menu_Gorons_Ruby].on = ((gSaveContext.questItems & (1 << 19)) != 0);
            break;
        case(Gear_Menu_Zoras_Sapphire):
            gSaveContext.questItems ^= (1 << 20);
            InventoryLeftGearMenu.items[Gear_Menu_Zoras_Sapphire].on = ((gSaveContext.questItems & (1 << 20)) != 0);
            break;
        case(Gear_Menu_Pieces_of_Heart):
            break; //handled in another function
        case(Gear_Menu_Shard_of_Agony):
            gSaveContext.questItems ^= (1 << 21);
            InventoryLeftGearMenu.items[Gear_Menu_Shard_of_Agony].on = ((gSaveContext.questItems & (1 << 21)) != 0);
            break;
        case(Gear_Menu_Gerudo_Token):
            gSaveContext.questItems ^= (1 << 22);
            InventoryLeftGearMenu.items[Gear_Menu_Gerudo_Token].on = ((gSaveContext.questItems & (1 << 22)) != 0);
            break;
        case(Gear_Menu_Gold_Skulltulas):
            break; //handled in another function
    }
}

void Inventory_HeartPiecesAmount(s32 selected){

    u16 curHearts = gSaveContext.questItems >> 28;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        char buf[65] = { 0 };
        sprintf(buf, "%04d", curHearts);
        Draw_DrawString(10, 10, COLOR_TITLE, "Use the D-pad to edit, B to return.");
        Draw_DrawString(30, 30, COLOR_WHITE, buf);
        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = waitInputWithTimeout(1000);

        if (pressed & BUTTON_B){
            break;
        }
        if (pressed & BUTTON_A){
            break;
        }
        else if (pressed & BUTTON_LEFT){
            curHearts--;
        }
        else if (pressed & BUTTON_RIGHT){
            curHearts++;
        }
        else if (pressed & BUTTON_UP){
            curHearts++;
        }
        else if (pressed & BUTTON_DOWN){
            curHearts--;
        }

        curHearts %= 4;

    } while(true);

    gSaveContext.questItems &= 0xFFFFFF;
    gSaveContext.questItems |= (curHearts << 28);
}

void Inventory_GoldSkulltulaAmount(s32 selected){

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        char buf[65] = { 0 };
        sprintf(buf, "%04d", gSaveContext.gsTokens);
        Draw_DrawString(10, 10, COLOR_TITLE, "Use the D-pad to edit, B to return.");
        Draw_DrawString(30, 30, COLOR_WHITE, buf);
        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = waitInputWithTimeout(1000);

        if (pressed & BUTTON_B){
            break;
        }
        if (pressed & BUTTON_A){
            break;
        }
        else if (pressed & BUTTON_LEFT){
            gSaveContext.gsTokens -= 10;
        }
        else if (pressed & BUTTON_RIGHT){
            gSaveContext.gsTokens += 10;
        }
        else if (pressed & BUTTON_UP){
            gSaveContext.gsTokens++;
        }
        else if (pressed & BUTTON_DOWN){
            gSaveContext.gsTokens--;
        }

    } while(true);

    gSaveContext.questItems &= ~(1 << 22);
    gSaveContext.questItems |= ((gSaveContext.gsTokens != 0) << 22);
}

static void Inventory_SongsMenuInit(void){ //TODO
    InventorySongsMenu.items[Songs_Menu_Zeldas_Lullaby].on = (gSaveContext.questItems >> 12) & 1;
    InventorySongsMenu.items[Songs_Menu_Eponas_Song].on = (gSaveContext.questItems >> 13) & 1;
    InventorySongsMenu.items[Songs_Menu_Sarias_Song].on = (gSaveContext.questItems >> 14) & 1;
    InventorySongsMenu.items[Songs_Menu_Suns_Song].on = (gSaveContext.questItems >> 15) & 1;
    InventorySongsMenu.items[Songs_Menu_Song_of_Time].on = (gSaveContext.questItems >> 16) & 1;
    InventorySongsMenu.items[Songs_Menu_Song_of_Storms].on = (gSaveContext.questItems >> 17) & 1;
    InventorySongsMenu.items[Songs_Menu_Minuet].on = (gSaveContext.questItems >> 6) & 1;
    InventorySongsMenu.items[Songs_Menu_Bolero].on = (gSaveContext.questItems >> 7) & 1;
    InventorySongsMenu.items[Songs_Menu_Serenade].on = (gSaveContext.questItems >> 8) & 1;
    InventorySongsMenu.items[Songs_Menu_Requiem].on = (gSaveContext.questItems >> 9) & 1;
    InventorySongsMenu.items[Songs_Menu_Nocturne].on = (gSaveContext.questItems >> 10) & 1;
    InventorySongsMenu.items[Songs_Menu_Prelude].on = (gSaveContext.questItems >> 11) & 1;
}

void Inventory_SongsMenuFunc(void){
    Inventory_SongsMenuInit();
    ToggleMenuShow(&InventorySongsMenu);
}

void Inventory_SongsToggle(s32 selected){
    switch(selected){
        case(Songs_Menu_Zeldas_Lullaby):
            gSaveContext.questItems ^= (1 << 12);
            InventorySongsMenu.items[Songs_Menu_Zeldas_Lullaby].on = ((gSaveContext.questItems & (1 << 12)) != 0);
            break;
        case(Songs_Menu_Eponas_Song):
            gSaveContext.questItems ^= (1 << 13);
            InventorySongsMenu.items[Songs_Menu_Eponas_Song].on = ((gSaveContext.questItems & (1 << 13)) != 0);
            break;        
        case(Songs_Menu_Sarias_Song):
            gSaveContext.questItems ^= (1 << 14);
            InventorySongsMenu.items[Songs_Menu_Sarias_Song].on = ((gSaveContext.questItems & (1 << 14)) != 0);
            break;        
        case(Songs_Menu_Suns_Song):
            gSaveContext.questItems ^= (1 << 15);
            InventorySongsMenu.items[Songs_Menu_Suns_Song].on = ((gSaveContext.questItems & (1 << 15)) != 0);
            break;        
        case(Songs_Menu_Song_of_Time):
            gSaveContext.questItems ^= (1 << 16);
            InventorySongsMenu.items[Songs_Menu_Song_of_Time].on = ((gSaveContext.questItems & (1 << 16)) != 0);
            break;        
        case(Songs_Menu_Song_of_Storms):
            gSaveContext.questItems ^= (1 << 17);
            InventorySongsMenu.items[Songs_Menu_Song_of_Storms].on = ((gSaveContext.questItems & (1 << 17)) != 0);
            break;   
        case(Songs_Menu_Minuet):
            gSaveContext.questItems ^= (1 << 6);
            InventorySongsMenu.items[Songs_Menu_Minuet].on = ((gSaveContext.questItems & (1 << 6)) != 0);
            break;    
        case(Songs_Menu_Bolero):
            gSaveContext.questItems ^= (1 << 7);
            InventorySongsMenu.items[Songs_Menu_Bolero].on = ((gSaveContext.questItems & (1 << 7)) != 0);
            break;    
        case(Songs_Menu_Serenade):
            gSaveContext.questItems ^= (1 << 8);
            InventorySongsMenu.items[Songs_Menu_Serenade].on = ((gSaveContext.questItems & (1 << 8)) != 0);
            break;    
        case(Songs_Menu_Requiem):
            gSaveContext.questItems ^= (1 << 9);
            InventorySongsMenu.items[Songs_Menu_Requiem].on = ((gSaveContext.questItems & (1 << 9)) != 0);
            break;    
        case(Songs_Menu_Nocturne):
            gSaveContext.questItems ^= (1 << 10);
            InventorySongsMenu.items[Songs_Menu_Nocturne].on = ((gSaveContext.questItems & (1 << 10)) != 0);
            break;    
        case(Songs_Menu_Prelude):
            gSaveContext.questItems ^= (1 << 11);
            InventorySongsMenu.items[Songs_Menu_Prelude].on = ((gSaveContext.questItems & (1 << 11)) != 0);
            break;     
    }
}

static void Inventory_AmountsMenuInit(void){
    InventoryAmountsMenu.items[Amounts_Menu_Deku_Sticks].amount = gSaveContext.ammo[ItemSlots[ITEM_DEKU_STICK]];
    InventoryAmountsMenu.items[Amounts_Menu_Deku_Nuts].amount = gSaveContext.ammo[ItemSlots[ITEM_DEKU_NUT]];
    InventoryAmountsMenu.items[Amounts_Menu_Bombs].amount = gSaveContext.ammo[ItemSlots[ITEM_BOMB]];
    InventoryAmountsMenu.items[Amounts_Menu_Arrows].amount = gSaveContext.ammo[ItemSlots[ITEM_FAIRY_BOW]];
    InventoryAmountsMenu.items[Amounts_Menu_Deku_Seeds].amount = gSaveContext.ammo[ItemSlots[ITEM_FAIRY_SLINGSHOT]];
    InventoryAmountsMenu.items[Amounts_Menu_Bombchus].amount = gSaveContext.ammo[ItemSlots[ITEM_BOMBCHU]];
    InventoryAmountsMenu.items[Amounts_Menu_Magic_Beans].amount = gSaveContext.ammo[ItemSlots[ITEM_MAGIC_BEANS]];
    InventoryAmountsMenu.items[Amounts_Menu_Rupees].amount = gSaveContext.rupees;
    InventoryAmountsMenu.items[Amounts_Menu_Giants_Knife_hits].amount = gSaveContext.bgsHitsLeft;
    InventoryAmountsMenu.items[Amounts_Menu_Double_Defense].amount = gSaveContext.doubleDefense;
    InventoryAmountsMenu.items[Amounts_Menu_Magic_meter_size].amount = gSaveContext.magicAcquired + gSaveContext.doubleMagic;
    InventoryAmountsMenu.items[Amounts_Menu_Heart_Containers].amount = gSaveContext.healthCapacity;
    InventoryAmountsMenu.items[Amounts_Menu_Current_Health].amount = gSaveContext.health;
    InventoryAmountsMenu.items[Amounts_Menu_Current_Magic].amount = gSaveContext.magic;
}

void Inventory_AmountsMenuFunc(void){
    Inventory_AmountsMenuInit();
    AmountMenuShow(&InventoryAmountsMenu);
}

void Inventory_AmountsSelect(s32 selected){
    switch(selected){
        case(Amounts_Menu_Deku_Sticks):
            gSaveContext.ammo[ItemSlots[ITEM_DEKU_STICK]] = InventoryAmountsMenu.items[Amounts_Menu_Deku_Sticks].amount;
            break;
        case(Amounts_Menu_Deku_Nuts):
            gSaveContext.ammo[ItemSlots[ITEM_DEKU_NUT]] = InventoryAmountsMenu.items[Amounts_Menu_Deku_Nuts].amount;
            break;
        case(Amounts_Menu_Bombs):
            gSaveContext.ammo[ItemSlots[ITEM_BOMB]] = InventoryAmountsMenu.items[Amounts_Menu_Bombs].amount;
            break;
        case(Amounts_Menu_Arrows):
            gSaveContext.ammo[ItemSlots[ITEM_FAIRY_BOW]] = InventoryAmountsMenu.items[Amounts_Menu_Arrows].amount;
            break;
        case(Amounts_Menu_Deku_Seeds):
            gSaveContext.ammo[ItemSlots[ITEM_FAIRY_SLINGSHOT]] = InventoryAmountsMenu.items[Amounts_Menu_Deku_Seeds].amount;
            break;
        case(Amounts_Menu_Bombchus):
            gSaveContext.ammo[ItemSlots[ITEM_BOMBCHU]] = InventoryAmountsMenu.items[Amounts_Menu_Bombchus].amount;
            break;
        case(Amounts_Menu_Magic_Beans):
            gSaveContext.ammo[ItemSlots[ITEM_MAGIC_BEANS]] = InventoryAmountsMenu.items[Amounts_Menu_Magic_Beans].amount;
            break;
        case(Amounts_Menu_Rupees):
            gSaveContext.rupees = InventoryAmountsMenu.items[Amounts_Menu_Rupees].amount;
            break;
        case(Amounts_Menu_Giants_Knife_hits):
            gSaveContext.bgsHitsLeft = InventoryAmountsMenu.items[Amounts_Menu_Giants_Knife_hits].amount;
            break;
        case(Amounts_Menu_Double_Defense):
            gSaveContext.doubleDefense = InventoryAmountsMenu.items[Amounts_Menu_Double_Defense].amount;
            break;
        case(Amounts_Menu_Magic_meter_size):
            gSaveContext.magicAcquired = (InventoryAmountsMenu.items[Amounts_Menu_Magic_meter_size].amount != 0);
            gSaveContext.doubleMagic = (InventoryAmountsMenu.items[Amounts_Menu_Magic_meter_size].amount == 2);
            break;
        case(Amounts_Menu_Heart_Containers):
            gSaveContext.healthCapacity = InventoryAmountsMenu.items[Amounts_Menu_Heart_Containers].amount;
            break;
        case(Amounts_Menu_Current_Health):
            gSaveContext.health = InventoryAmountsMenu.items[Amounts_Menu_Current_Health].amount;
            break;
        case(Amounts_Menu_Current_Magic):
            gSaveContext.magic = InventoryAmountsMenu.items[Amounts_Menu_Current_Magic].amount;
            break;
    }
}
