#include "menu.h"
#include "menus/inventory.h"
#include "draw.h"
#include "z3d.h"
#include "z3Dequipment.h"
#include <stdio.h>

Menu InventoryMenu = {
    "Cheats",
    .nbItems = 3,
    {
        {"Items", METHOD, .method = Inventory_ItemsMenuFunc},
        {"Right Side Gear", METHOD, .method = Inventory_RightGearMenuFunc},
        {"Left Side Gear", METHOD, .method = Inventory_LeftGearMenuFunc},
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
    .nbItems = 11,
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

AmountMenu InventoryAmountsMenu = {
    "Amounts. Press A to edit/save amount. Press B to cancel.",
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
        {0, 0, "Double Defense (1 for on, 0 for off)", .method = Inventory_AmountsSelect},
        {0, 1, "Heart Containers (0x10 per container)", .method = Inventory_AmountsSelect},
        {0, 1, "Current Health (0x10 per container)", .method = Inventory_AmountsSelect},
        {0, 1, "Magic meter size (0x30 for normal, 0x60 for double)", .method = Inventory_AmountsSelect},
        {0, 1, "Current Magic (0x30 for normal, 0x60 for double)", .method = Inventory_AmountsSelect},
        {0, 1, "Giant's Knife hits remaining", .method = Inventory_AmountsSelect},
    }
};

void Inventory_ItemsMenuInit(void){
    InventoryItemsMenu.items[ITEM_DEKU_STICK].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_DEKU_STICK]] == ITEM_DEKU_STICK);
    InventoryItemsMenu.items[ITEM_DEKU_NUT].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_DEKU_NUT]] == ITEM_DEKU_NUT);
    InventoryItemsMenu.items[ITEM_BOMB].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_BOMB]] == ITEM_BOMB);
    InventoryItemsMenu.items[ITEM_FAIRY_BOW].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_FAIRY_BOW]] == ITEM_FAIRY_BOW);
    InventoryItemsMenu.items[ITEM_FIRE_ARROW].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_FIRE_ARROW]] == ITEM_FIRE_ARROW); //TODO
    InventoryItemsMenu.items[ITEM_DINS_FIRE].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_DINS_FIRE]] == ITEM_DINS_FIRE);
    InventoryItemsMenu.items[ITEM_FAIRY_SLINGSHOT].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_FAIRY_SLINGSHOT]] == ITEM_FAIRY_SLINGSHOT);
    InventoryItemsMenu.items[ITEM_FAIRY_OCARINA].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_FAIRY_OCARINA]] == ITEM_FAIRY_OCARINA);
    InventoryItemsMenu.items[ITEM_OCARINA_OF_TIME].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_OCARINA_OF_TIME]] == ITEM_OCARINA_OF_TIME);
    InventoryItemsMenu.items[ITEM_BOMBCHU].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_BOMBCHU]] == ITEM_BOMBCHU);
    InventoryItemsMenu.items[ITEM_HOOKSHOT].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_HOOKSHOT]] == ITEM_HOOKSHOT);
    InventoryItemsMenu.items[ITEM_LONGSHOT].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_LONGSHOT]] == ITEM_LONGSHOT);
    InventoryItemsMenu.items[ITEM_ICE_ARROW].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_ICE_ARROW]] == ITEM_ICE_ARROW); //TODO
    InventoryItemsMenu.items[ITEM_FARORES_WIND].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_FARORES_WIND]] == ITEM_FARORES_WIND);
    InventoryItemsMenu.items[ITEM_BOOMERANG].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_BOOMERANG]] == ITEM_BOOMERANG);
    InventoryItemsMenu.items[ITEM_LENS_OF_TRUTH].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_LENS_OF_TRUTH]] == ITEM_LENS_OF_TRUTH);
    InventoryItemsMenu.items[ITEM_MAGIC_BEANS].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_MAGIC_BEANS]] == ITEM_MAGIC_BEANS);
    InventoryItemsMenu.items[ITEM_MEGATON_HAMMER].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_MEGATON_HAMMER]] == ITEM_MEGATON_HAMMER);
    InventoryItemsMenu.items[ITEM_LIGHT_ARROW].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_LIGHT_ARROW]] == ITEM_LIGHT_ARROW); //TODO
    InventoryItemsMenu.items[ITEM_NAYRUS_LOVE].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_NAYRUS_LOVE]] == ITEM_NAYRUS_LOVE);
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE]] != ITEM_EMPTY);
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 1].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE] + 1] != ITEM_EMPTY);
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 2].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE] + 2] != ITEM_EMPTY);
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 3].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE] + 3] != ITEM_EMPTY);
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 4].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE] + 4] != ITEM_EMPTY); //TODO
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 5].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE] + 5] != ITEM_EMPTY); //TODO
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 6].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE] + 6] == ITEM_IRON_BOOTS); //TODO
    InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + 7].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE] + 7] != ITEM_HOVER_BOOTS); //TODO
}

void Inventory_ItemsMenuFunc(void){
    Inventory_ItemsMenuInit();
    ToggleMenuShow(&InventoryItemsMenu);
}

void Inventory_ItemsToggle(s32 selected){
    switch(selected) {
        case(ITEM_FAIRY_BOW): //TODO
        case(ITEM_FIRE_ARROW): //TODO
        case(ITEM_FAIRY_OCARINA):
            if (gSaveContext.item_slot_item[ItemSlots[ITEM_FAIRY_OCARINA]] != ITEM_FAIRY_OCARINA){
                gSaveContext.item_slot_item[ItemSlots[ITEM_FAIRY_OCARINA]] = ITEM_FAIRY_OCARINA;
                InventoryItemsMenu.items[ITEM_FAIRY_OCARINA].on = 1;
                InventoryItemsMenu.items[ITEM_OCARINA_OF_TIME].on = 0; //turn off Ocarina of Time in menu
            }
            else {
                gSaveContext.item_slot_item[ItemSlots[ITEM_FAIRY_OCARINA]] = ITEM_EMPTY;
                InventoryItemsMenu.items[ITEM_FAIRY_OCARINA].on = 0;
                InventoryItemsMenu.items[ITEM_OCARINA_OF_TIME].on = 0;
            }
            break;
        case(ITEM_OCARINA_OF_TIME):
            if (gSaveContext.item_slot_item[ItemSlots[ITEM_OCARINA_OF_TIME]] != ITEM_OCARINA_OF_TIME){
                gSaveContext.item_slot_item[ItemSlots[ITEM_OCARINA_OF_TIME]] = ITEM_OCARINA_OF_TIME;
                InventoryItemsMenu.items[ITEM_FAIRY_OCARINA].on = 0; //turn off Fairy Ocarina in menu
                InventoryItemsMenu.items[ITEM_OCARINA_OF_TIME].on = 1; 
            }
            else {
                gSaveContext.item_slot_item[ItemSlots[ITEM_OCARINA_OF_TIME]] = ITEM_EMPTY;
                InventoryItemsMenu.items[ITEM_FAIRY_OCARINA].on = 0;
                InventoryItemsMenu.items[ITEM_OCARINA_OF_TIME].on = 0;
            }
            break;
        case(ITEM_HOOKSHOT):
            if (gSaveContext.item_slot_item[ItemSlots[ITEM_HOOKSHOT]] != ITEM_HOOKSHOT){
                gSaveContext.item_slot_item[ItemSlots[ITEM_HOOKSHOT]] = ITEM_HOOKSHOT;
                InventoryItemsMenu.items[ITEM_HOOKSHOT].on = 1;
                InventoryItemsMenu.items[ITEM_LONGSHOT].on = 0; //turn off Longshot in menu 
            }
            else {
                gSaveContext.item_slot_item[ItemSlots[ITEM_HOOKSHOT]] = ITEM_EMPTY;
                for (u32 i = 0; i < 0x30; ++i){ //need to remove the slot from child/adult grids
                    if (gSaveContext.inventory_grid_data_child[i] == ItemSlots[ITEM_HOOKSHOT]){
                        gSaveContext.inventory_grid_data_child[i] = 0xFF;
                    }
                }
                InventoryItemsMenu.items[ITEM_HOOKSHOT].on = 0;
                InventoryItemsMenu.items[ITEM_LONGSHOT].on = 0;
            }
            break;
        case(ITEM_LONGSHOT):
            if (gSaveContext.item_slot_item[ItemSlots[ITEM_LONGSHOT]] != ITEM_LONGSHOT){
                gSaveContext.item_slot_item[ItemSlots[ITEM_LONGSHOT]] = ITEM_LONGSHOT;
                InventoryItemsMenu.items[ITEM_HOOKSHOT].on = 0; //turn off Hookshot in menu
                InventoryItemsMenu.items[ITEM_LONGSHOT].on = 1;  
            }
            else {
                gSaveContext.item_slot_item[ItemSlots[ITEM_LONGSHOT]] = ITEM_EMPTY;
                for (u32 i = 0; i < 0x30; ++i){ //need to remove the slot from child/adult grids
                    if (gSaveContext.inventory_grid_data_child[i] == ItemSlots[ITEM_LONGSHOT]){
                        gSaveContext.inventory_grid_data_child[i] = 0xFF;
                    }
                }
                InventoryItemsMenu.items[ITEM_HOOKSHOT].on = 0;
                InventoryItemsMenu.items[ITEM_LONGSHOT].on = 0;
            }
            break;
        case(ITEM_ICE_ARROW): //TODO
        case(ITEM_LIGHT_ARROW): //TODO
        default:
            if (gSaveContext.item_slot_item[ItemSlots[selected]] != selected){
                gSaveContext.item_slot_item[ItemSlots[selected]] = selected;
                InventoryItemsMenu.items[selected].on = 1;
            }
            else {
                gSaveContext.item_slot_item[ItemSlots[selected]] = ITEM_EMPTY;
                for (u32 i = 0; i < 0x30; ++i){ //need to remove the slot from child/adult grids
                    if (gSaveContext.inventory_grid_data_child[i] == ItemSlots[selected]){
                        gSaveContext.inventory_grid_data_child[i] = 0xFF;
                    }
                }
                InventoryItemsMenu.items[selected].on = 0;
            }
            break;
    }
}

void Inventory_BottlesMenuInit(void){
    for (u32 i = 0; i < ITEM_WEIRD_EGG - ITEM_EMPTY_BOTTLE; ++i){
        InventoryBottlesMenu.items[i].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE] + SelectedBottle] == ITEM_EMPTY_BOTTLE + i);
    }
    InventoryBottlesMenu.items[ITEM_WEIRD_EGG - ITEM_EMPTY_BOTTLE].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE] + SelectedBottle] == ITEM_EMPTY);
}

void Inventory_BottlesMenuFunc(s32 selected){
    SelectedBottle = selected - ITEM_EMPTY_BOTTLE;
    Inventory_BottlesMenuInit();
    ToggleMenuShow(&InventoryBottlesMenu);
}

void Inventory_BottleSelect(s32 selected){
    if (selected < ITEM_WEIRD_EGG - ITEM_EMPTY_BOTTLE){ //selected a bottled content
        gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE] + SelectedBottle] = ITEM_EMPTY_BOTTLE + selected;
        for(u32 i = 0; i < InventoryBottlesMenu.nbItems; ++i){ //set menu toggles on/off
            InventoryBottlesMenu.items[i].on = (i == selected ? 1 : 0);
        }
        InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + SelectedBottle].on = 1;
    }
    else { //erase the bottle
        gSaveContext.item_slot_item[ItemSlots[ITEM_EMPTY_BOTTLE] + SelectedBottle] = ITEM_EMPTY;
        for (u32 i = 0; i < 0x30; ++i){ //need to remove the slot from child/adult grids
            if (gSaveContext.inventory_grid_data_child[i] == ItemSlots[ITEM_EMPTY_BOTTLE] + SelectedBottle){
                gSaveContext.inventory_grid_data_child[i] = 0xFF;
            }
        }
        for(u32 i = 0; i < InventoryBottlesMenu.nbItems; ++i){ //set menu toggles off
            InventoryBottlesMenu.items[i].on = 0;
        }
        InventoryItemsMenu.items[ITEM_EMPTY_BOTTLE + SelectedBottle].on = 0;
    }
}

void Inventory_ChildTradeMenuInit(void){
    for (u32 i = 0; i < ITEM_POCKET_EGG - ITEM_WEIRD_EGG; ++i){
        InventoryChildTradeMenu.items[i].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_WEIRD_EGG]] == ITEM_WEIRD_EGG + i);
    }
    InventoryChildTradeMenu.items[ITEM_POCKET_EGG - ITEM_WEIRD_EGG].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_WEIRD_EGG]] == ITEM_EMPTY);
}

void Inventory_ChildTradeMenuFunc(s32 selected){
    Inventory_ChildTradeMenuInit();
    ToggleMenuShow(&InventoryChildTradeMenu);
}

void Inventory_ChildTradeSelect(s32 selected){ //TODO: remove hardcoded indexes
    if (selected < ITEM_POCKET_EGG - ITEM_WEIRD_EGG){ //selected a child trade item
        gSaveContext.item_slot_item[ItemSlots[ITEM_WEIRD_EGG]] = ITEM_WEIRD_EGG + selected;
        for(u32 i = 0; i < InventoryBottlesMenu.nbItems; ++i){ //set menu toggles on/off
            InventoryBottlesMenu.items[i].on = (i == selected ? 1 : 0);
        }
        InventoryItemsMenu.items[24].on = 1;
    }
    else { //erase the child trade item
        gSaveContext.item_slot_item[ItemSlots[ITEM_WEIRD_EGG]] = ITEM_EMPTY;
        for (u32 i = 0; i < 0x30; ++i){ //need to remove the slot from child/adult grids
            if (gSaveContext.inventory_grid_data_child[i] == ItemSlots[ITEM_WEIRD_EGG]){
                gSaveContext.inventory_grid_data_child[i] = 0xFF;
            }
        }
        for(u32 i = 0; i < InventoryBottlesMenu.nbItems; ++i){ //set menu toggles off
            InventoryBottlesMenu.items[i].on = 0;
        }
        InventoryItemsMenu.items[24].on = 0;
    }
}

void Inventory_AdultTradeMenuInit(void){
    for (u32 i = 0; i < ITEM_FAIRY_BOW_PLUS_FIRE_ARROW - ITEM_POCKET_EGG; ++i){
        InventoryAdultTradeMenu.items[i].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_POCKET_EGG]] == ITEM_POCKET_EGG + i);
    }
    InventoryAdultTradeMenu.items[ITEM_FAIRY_BOW_PLUS_FIRE_ARROW - ITEM_POCKET_EGG].on = (gSaveContext.item_slot_item[ItemSlots[ITEM_POCKET_EGG]] == ITEM_EMPTY);    
}

void Inventory_AdultTradeMenuFunc(s32 selected){
    Inventory_AdultTradeMenuInit();
    ToggleMenuShow(&InventoryAdultTradeMenu);
}

void Inventory_AdultTradeSelect(s32 selected){ //TODO: remove hardcoded indexes
    if (selected < ITEM_FAIRY_BOW_PLUS_FIRE_ARROW - ITEM_POCKET_EGG){ //selected an adult trade item
        gSaveContext.item_slot_item[ItemSlots[ITEM_POCKET_EGG]] = ITEM_POCKET_EGG + selected;
        for(u32 i = 0; i < InventoryBottlesMenu.nbItems; ++i){ //set menu toggles on/off
            InventoryBottlesMenu.items[i].on = (i == selected ? 1 : 0);
        }
        InventoryItemsMenu.items[25].on = 1;
    }
    else { //erase the adult trade item
        gSaveContext.item_slot_item[ItemSlots[ITEM_POCKET_EGG]] = ITEM_EMPTY;
        for (u32 i = 0; i < 0x30; ++i){ //need to remove the slot from child/adult grids
            if (gSaveContext.inventory_grid_data_child[i] == ItemSlots[ITEM_POCKET_EGG]){
                gSaveContext.inventory_grid_data_child[i] = 0xFF;
            }
        }
        for(u32 i = 0; i < InventoryBottlesMenu.nbItems; ++i){ //set menu toggles off
            InventoryBottlesMenu.items[i].on = 0;
        }
        InventoryItemsMenu.items[25].on = 0;
    }
}

void Inventory_BootsToggle(s32 selected){ //TODO: remove hardcoded values
    //put boots in their slots
    //set boots bits in gear
    if (selected == 26){ //Iron boots
        if (gSaveContext.item_slot_item[24] != ITEM_IRON_BOOTS){
            gSaveContext.item_slot_item[24] = ITEM_IRON_BOOTS;
            gSaveContext.iron_boots = 1;
            InventoryItemsMenu.items[selected].on = 1;
        }
        else {
            gSaveContext.item_slot_item[24] = ITEM_EMPTY;
            gSaveContext.iron_boots = 0;
            for (u32 i = 0; i < 0x30; ++i){ //need to remove the slot from child/adult grids
                if (gSaveContext.inventory_grid_data_child[i] == 24){
                    gSaveContext.inventory_grid_data_child[i] = 0xFF;
                }
            }
            InventoryItemsMenu.items[selected].on = 0;
        }
    }
    else { //Hover boots
        if (gSaveContext.item_slot_item[25] != ITEM_HOVER_BOOTS){
            gSaveContext.item_slot_item[25] = ITEM_HOVER_BOOTS;
            gSaveContext.hover_boots = 1;
            InventoryItemsMenu.items[selected].on = 1;
        }
        else {
            gSaveContext.item_slot_item[25] = ITEM_EMPTY;
            gSaveContext.hover_boots = 0;
            for (u32 i = 0; i < 0x30; ++i){ //need to remove the slot from child/adult grids
                if (gSaveContext.inventory_grid_data_child[i] == 25){
                    gSaveContext.inventory_grid_data_child[i] = 0xFF;
                }
            }
            InventoryItemsMenu.items[selected].on = 0;
        }
    }
}

void Inventory_RightGearMenu_Init(void){
    InventoryRightGearMenu.items[Gear_Menu_Kokiri_Sword].on = gSaveContext.kokiri_sword;
    InventoryRightGearMenu.items[Gear_Menu_Master_Sword].on = gSaveContext.master_sword;
    InventoryRightGearMenu.items[Gear_Menu_Giants_Knife].on = gSaveContext.giants_knife; //TODO
    InventoryRightGearMenu.items[Gear_Menu_Broken_Giants_Knife].on = gSaveContext.giants_knife; //TODO
    InventoryRightGearMenu.items[Gear_Menu_Biggoron_Sword].on = gSaveContext.giants_knife; //TODO
    InventoryRightGearMenu.items[Gear_Menu_Deku_Shield].on = gSaveContext.deku_shield;
    InventoryRightGearMenu.items[Gear_Menu_Hylian_Shield].on = gSaveContext.hylian_shield;
    InventoryRightGearMenu.items[Gear_Menu_Mirror_Shield].on = gSaveContext.mirror_shield;
    InventoryRightGearMenu.items[Gear_Menu_Kokiri_Tunic].on = gSaveContext.kokiri_tunic;
    InventoryRightGearMenu.items[Gear_Menu_Goron_Tunic].on = gSaveContext.goron_tunic;
    InventoryRightGearMenu.items[Gear_Menu_Zora_Tunic].on = gSaveContext.zora_tunic;
    InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = (gSaveContext.bullet_bag == BULLET_BAG_30);
    InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = (gSaveContext.bullet_bag == BULLET_BAG_40);
    InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = (gSaveContext.bullet_bag == BULLET_BAG_50);
    InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = (gSaveContext.quiver == QUIVER_30);
    InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = (gSaveContext.quiver == QUIVER_40);
    InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = (gSaveContext.quiver == QUIVER_50);
    InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = (gSaveContext.bomb_bag == BOMB_BAG_20);
    InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = (gSaveContext.bomb_bag == BOMB_BAG_30);
    InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = (gSaveContext.bomb_bag == BOMB_BAG_40);
    InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = (gSaveContext.strength_upgrade == GORON_BRACELET);
    InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = (gSaveContext.strength_upgrade == SILVER_GAUNTLETS);
    InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = (gSaveContext.strength_upgrade == GOLDEN_GAUNTLETS);
    InventoryRightGearMenu.items[Gear_Menu_Silver_Scale].on = (gSaveContext.dive_meter == SILVER_SCALE);
    InventoryRightGearMenu.items[Gear_Menu_Golden_Scale].on = (gSaveContext.dive_meter == GOLDEN_SCALE);
    InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = (gSaveContext.wallet_upgrade == ADULTS_WALLET);
    InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = (gSaveContext.wallet_upgrade == GIANTS_WALLET);
    InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = (gSaveContext.wallet_upgrade == NO_RUPEES_SHOWN);
}

void Inventory_RightGearMenuFunc(void){
    Inventory_RightGearMenu_Init();
    ToggleMenuShow(&InventoryRightGearMenu);
}

void Inventory_RightGearToggle(s32 selected){ //TODO
    switch(selected){
        case(Gear_Menu_Kokiri_Sword):
            gSaveContext.kokiri_sword = ~gSaveContext.kokiri_sword;
            InventoryRightGearMenu.items[Gear_Menu_Kokiri_Sword].on = gSaveContext.kokiri_sword;
            break;
        case(Gear_Menu_Master_Sword):
            gSaveContext.master_sword = ~gSaveContext.master_sword;
            InventoryRightGearMenu.items[Gear_Menu_Master_Sword].on = gSaveContext.master_sword;
            break;
        case(Gear_Menu_Giants_Knife): //TODO
        case(Gear_Menu_Broken_Giants_Knife): //TODO
        case(Gear_Menu_Biggoron_Sword): //TODO
        case(Gear_Menu_Deku_Shield):
            gSaveContext.deku_shield = ~gSaveContext.deku_shield;
            InventoryRightGearMenu.items[Gear_Menu_Deku_Shield].on = gSaveContext.deku_shield;
            break;
        case(Gear_Menu_Hylian_Shield):
            gSaveContext.hylian_shield = ~gSaveContext.hylian_shield;
            InventoryRightGearMenu.items[Gear_Menu_Hylian_Shield].on = gSaveContext.hylian_shield;
            break;
        case(Gear_Menu_Mirror_Shield):
            gSaveContext.mirror_shield = ~gSaveContext.mirror_shield;
            InventoryRightGearMenu.items[Gear_Menu_Mirror_Shield].on = gSaveContext.mirror_shield;
            break;
        case(Gear_Menu_Kokiri_Tunic):
            gSaveContext.kokiri_tunic = ~gSaveContext.kokiri_tunic;
            InventoryRightGearMenu.items[Gear_Menu_Kokiri_Tunic].on = gSaveContext.kokiri_tunic;
            break;
        case(Gear_Menu_Goron_Tunic):
            gSaveContext.goron_tunic = ~gSaveContext.goron_tunic;
            InventoryRightGearMenu.items[Gear_Menu_Goron_Tunic].on = gSaveContext.goron_tunic;
            break;
        case(Gear_Menu_Zora_Tunic):
            gSaveContext.zora_tunic = ~gSaveContext.zora_tunic;
            InventoryRightGearMenu.items[Gear_Menu_Zora_Tunic].on = gSaveContext.zora_tunic;
            break;
        case(Gear_Menu_Bullet_Bag_30):
            if (gSaveContext.bullet_bag != BULLET_BAG_30){
                gSaveContext.bullet_bag = BULLET_BAG_30;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 0;
            }
            else {
                gSaveContext.bullet_bag = NO_BULLET_BAG;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 0;
            }
            break;
        case(Gear_Menu_Bullet_Bag_40):
            if (gSaveContext.bullet_bag != BULLET_BAG_40){
                gSaveContext.bullet_bag = BULLET_BAG_40;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 0;
            }
            else {
                gSaveContext.bullet_bag = NO_BULLET_BAG;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 0;
            }
            break;
        case(Gear_Menu_Bullet_Bag_50):
            if (gSaveContext.bullet_bag != BULLET_BAG_50){
                gSaveContext.bullet_bag = BULLET_BAG_50;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 1;
            }
            else {
                gSaveContext.bullet_bag = NO_BULLET_BAG;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bullet_Bag_50].on = 0;
            }
            break;
        case(Gear_Menu_Quiver_30):
            if (gSaveContext.quiver != QUIVER_30){
                gSaveContext.quiver = QUIVER_30;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 0;
            }
            else {
                gSaveContext.quiver = NO_QUIVER;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 0;
            }
            break;
        case(Gear_Menu_Quiver_40):
            if (gSaveContext.quiver != QUIVER_40){
                gSaveContext.quiver = QUIVER_40;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 0;
            }
            else {
                gSaveContext.quiver = NO_QUIVER;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 0;
            }
            break;
        case(Gear_Menu_Quiver_50):
            if (gSaveContext.quiver != QUIVER_50){
                gSaveContext.quiver = QUIVER_50;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 1;
            }
            else {
                gSaveContext.quiver = NO_QUIVER;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_40].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Quiver_50].on = 0;
            }
            break;
        case(Gear_Menu_Bomb_Bag_20):
            if (gSaveContext.bomb_bag != BOMB_BAG_20){
                gSaveContext.bomb_bag = BOMB_BAG_20;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 0;
            }
            else {
                gSaveContext.bomb_bag = NO_BOMB_BAG;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 0;
            }
            break;
        case(Gear_Menu_Bomb_Bag_30):    
            if (gSaveContext.bomb_bag != BOMB_BAG_30){
                gSaveContext.bomb_bag = BOMB_BAG_30;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 0;
            }
            else {
                gSaveContext.bomb_bag = NO_BOMB_BAG;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 0;
            }
            break;
        case(Gear_Menu_Bomb_Bag_40):
            if (gSaveContext.bomb_bag != BOMB_BAG_40){
                gSaveContext.bomb_bag = BOMB_BAG_40;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 1;
            }
            else {
                gSaveContext.bomb_bag = NO_BOMB_BAG;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_20].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_30].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Bomb_Bag_40].on = 0;
            }
            break;
        case(Gear_Menu_Gorons_Bracelet):
            if (gSaveContext.strength_upgrade != GORON_BRACELET){
                gSaveContext.strength_upgrade = GORON_BRACELET;
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 0;
            }
            else {
                gSaveContext.strength_upgrade = NO_STRENGTH;
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 0;
            }
            break;
        case(Gear_Menu_Silver_Gauntlets):
            if (gSaveContext.strength_upgrade != SILVER_GAUNTLETS){
                gSaveContext.strength_upgrade = SILVER_GAUNTLETS;
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 0;
            }
            else {
                gSaveContext.strength_upgrade = NO_STRENGTH;
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 0;
            }
            break;
        case(Gear_Menu_Golden_Gauntlets):
            if (gSaveContext.strength_upgrade != GOLDEN_GAUNTLETS){
                gSaveContext.strength_upgrade = GOLDEN_GAUNTLETS;
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 1;
            }
            else {
                gSaveContext.strength_upgrade = NO_STRENGTH;
                InventoryRightGearMenu.items[Gear_Menu_Gorons_Bracelet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Gauntlets].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Gauntlets].on = 0;
            }
            break;
        case(Gear_Menu_Silver_Scale):
            if (gSaveContext.dive_meter != SILVER_SCALE){
                gSaveContext.dive_meter = SILVER_SCALE;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Scale].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Scale].on = 0;
            }
            else {
                gSaveContext.dive_meter = NO_DIVE_UPGRADE;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Scale].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Scale].on = 0;
            }
            break;
        case(Gear_Menu_Golden_Scale):
            if (gSaveContext.dive_meter != GOLDEN_SCALE){
                gSaveContext.dive_meter = GOLDEN_SCALE;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Scale].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Scale].on = 1;
            }
            else {
                gSaveContext.dive_meter = GOLDEN_SCALE;
                InventoryRightGearMenu.items[Gear_Menu_Silver_Scale].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Golden_Scale].on = 0;
            }
            break;
        case(Gear_Menu_Adults_Wallet):
            if (gSaveContext.wallet_upgrade != ADULTS_WALLET){
                gSaveContext.wallet_upgrade = ADULTS_WALLET;
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 0;
            }
            else {
                gSaveContext.wallet_upgrade = DEFAULT_WALLET;
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 0;
            }
            break;
        case(Gear_Menu_Giants_Wallet):
            if (gSaveContext.wallet_upgrade != GIANTS_WALLET){
                gSaveContext.wallet_upgrade = GIANTS_WALLET;
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 1;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 0;
            }
            else {
                gSaveContext.wallet_upgrade = DEFAULT_WALLET;
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 0;
            }
            break;
        case(Gear_Menu_No_Wallet):
            if (gSaveContext.wallet_upgrade != NO_RUPEES_SHOWN){
                gSaveContext.wallet_upgrade = NO_RUPEES_SHOWN;
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 1;
            }
            else {
                gSaveContext.wallet_upgrade = DEFAULT_WALLET;
                InventoryRightGearMenu.items[Gear_Menu_Adults_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_Giants_Wallet].on = 0;
                InventoryRightGearMenu.items[Gear_Menu_No_Wallet].on = 0;
            }
            break;
    }
}

void Inventory_LeftGearMenuInit(void){
    InventoryLeftGearMenu.items[Gear_Menu_Forest_Medallion].on = gSaveContext.forest_medallion;
    InventoryLeftGearMenu.items[Gear_Menu_Fire_Medallion].on = gSaveContext.fire_medallion;
    InventoryLeftGearMenu.items[Gear_Menu_Water_Medallion].on = gSaveContext.water_medallion;
    InventoryLeftGearMenu.items[Gear_Menu_Spirit_Medallion].on = gSaveContext.spirit_medallion;
    InventoryLeftGearMenu.items[Gear_Menu_Shadow_Medallion].on = gSaveContext.shadow_medallion;
    InventoryLeftGearMenu.items[Gear_Menu_Light_Medallion].on = gSaveContext.light_medallion;
    InventoryLeftGearMenu.items[Gear_Menu_Kokiri_Emerald].on = gSaveContext.kokiris_emerald;
    InventoryLeftGearMenu.items[Gear_Menu_Gorons_Ruby].on = gSaveContext.gorons_ruby;
    InventoryLeftGearMenu.items[Gear_Menu_Zoras_Sapphire].on = gSaveContext.zoras_sapphire;
    InventoryLeftGearMenu.items[Gear_Menu_Pieces_of_Heart].on = (gSaveContext.heart_pieces >> 4 != 0);
    InventoryLeftGearMenu.items[Gear_Menu_Shard_of_Agony].on = gSaveContext.shard_of_agony;
    InventoryLeftGearMenu.items[Gear_Menu_Gerudo_Token].on = gSaveContext.gerudos_card;
    InventoryLeftGearMenu.items[Gear_Menu_Gold_Skulltulas].on = gSaveContext.gold_skulltula;
}

void Inventory_LeftGearMenuFunc(void){
    Inventory_LeftGearMenuInit();
    ToggleMenuShow(&InventoryLeftGearMenu);
}

void Inventory_LeftGearToggle(s32 selected){
    switch(selected){
        case(Gear_Menu_Forest_Medallion):
            gSaveContext.forest_medallion = ~gSaveContext.forest_medallion;
            InventoryLeftGearMenu.items[Gear_Menu_Forest_Medallion].on = gSaveContext.forest_medallion;
            break;
        case(Gear_Menu_Fire_Medallion):
            gSaveContext.fire_medallion = ~gSaveContext.fire_medallion;
            InventoryLeftGearMenu.items[Gear_Menu_Fire_Medallion].on = gSaveContext.fire_medallion;
            break;
        case(Gear_Menu_Water_Medallion):
            gSaveContext.water_medallion = ~gSaveContext.water_medallion;
            InventoryLeftGearMenu.items[Gear_Menu_Water_Medallion].on = gSaveContext.water_medallion;
            break;
        case(Gear_Menu_Spirit_Medallion):
            gSaveContext.spirit_medallion = ~gSaveContext.spirit_medallion;
            InventoryLeftGearMenu.items[Gear_Menu_Spirit_Medallion].on = gSaveContext.spirit_medallion;
            break;
        case(Gear_Menu_Shadow_Medallion):
            gSaveContext.shadow_medallion = ~gSaveContext.shadow_medallion;
            InventoryLeftGearMenu.items[Gear_Menu_Shadow_Medallion].on = gSaveContext.shadow_medallion;
            break;
        case(Gear_Menu_Light_Medallion):
            gSaveContext.light_medallion = ~gSaveContext.light_medallion;
            InventoryLeftGearMenu.items[Gear_Menu_Light_Medallion].on = gSaveContext.light_medallion;
            break;
        case(Gear_Menu_Kokiri_Emerald):
            gSaveContext.kokiris_emerald = ~gSaveContext.kokiris_emerald;
            InventoryLeftGearMenu.items[Gear_Menu_Kokiri_Emerald].on = gSaveContext.kokiris_emerald;
            break;
        case(Gear_Menu_Gorons_Ruby):
            gSaveContext.gorons_ruby = ~gSaveContext.gorons_ruby;
            InventoryLeftGearMenu.items[Gear_Menu_Gorons_Ruby].on = gSaveContext.gorons_ruby;
            break;
        case(Gear_Menu_Zoras_Sapphire):
            gSaveContext.zoras_sapphire = ~gSaveContext.zoras_sapphire;
            InventoryLeftGearMenu.items[Gear_Menu_Zoras_Sapphire].on = gSaveContext.zoras_sapphire;
            break;
        case(Gear_Menu_Pieces_of_Heart):
            break; //handled in another function
        case(Gear_Menu_Shard_of_Agony):
            gSaveContext.shard_of_agony = ~gSaveContext.shard_of_agony;
            InventoryLeftGearMenu.items[Gear_Menu_Shard_of_Agony].on = gSaveContext.shard_of_agony;
            break;
        case(Gear_Menu_Gerudo_Token):
            gSaveContext.gerudos_card = ~gSaveContext.gerudos_card;
            InventoryLeftGearMenu.items[Gear_Menu_Gerudo_Token].on = gSaveContext.gerudos_card;
            break;
        case(Gear_Menu_Gold_Skulltulas):
            break; //handled in another function
    }
}

void Inventory_HeartPiecesAmount(s32 selected){
    u8 curPieces = gSaveContext.heart_pieces >> 4;
    u32 curColor = COLOR_GREEN;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        char buf[65] = { 0 };
        sprintf(buf, "%d", curPieces);
        Draw_DrawString(10, 10, COLOR_TITLE, "Choose number of Heart Pieces using D-pad. A to save. B to return.");
        Draw_DrawString(30, 30, curColor, buf);
        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed;
        do
        {
            pressed = waitInputWithTimeout(50);
            if (pressed != 0) break;
        } while(pressed == 0);

        if (pressed & BUTTON_B){
            break;
        }
        if (pressed & BUTTON_A){
            gSaveContext.heart_pieces = curPieces << 4;
            curColor = COLOR_GREEN;
        }
        else if (pressed & BUTTON_LEFT){
            curPieces--;
            curColor = COLOR_RED;
        }
        else if (pressed & BUTTON_RIGHT){
            curPieces++;
            curColor = COLOR_RED;
        }

        if (curPieces < 0){
            curPieces = 3;
        }
        else if (curPieces > 3){
            curPieces = 0;
        }

    } while(true);
}

void Inventory_GoldSkulltulaAmount(s32 selected){
    u8 curSkulls = gSaveContext.golden_skulls_amount;
    u32 curColor = COLOR_GREEN;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        char buf[65] = { 0 };
        sprintf(buf, "%d", curSkulls);
        Draw_DrawString(10, 10, COLOR_TITLE, "Choose number of Gold Skulltulas using D-pad. A to save. B to return.");
        Draw_DrawString(30, 30, curColor, buf);
        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed;
        do
        {
            pressed = waitInputWithTimeout(50);
            if (pressed != 0) break;
        } while(pressed == 0);

        if (pressed & BUTTON_B){
            break;
        }
        if (pressed & BUTTON_A){
            gSaveContext.golden_skulls_amount = curSkulls;
            gSaveContext.gold_skulltula = (gSaveContext.golden_skulls_amount != 0);
            curColor = COLOR_GREEN;
        }
        else if (pressed & BUTTON_LEFT){
            curSkulls--;
            curColor = COLOR_RED;
        }
        else if (pressed & BUTTON_RIGHT){
            curSkulls++;
            curColor = COLOR_RED;
        }
        else if (pressed & BUTTON_UP){
            curSkulls += 10;
            curColor = COLOR_RED;
        }
        else if (pressed & BUTTON_DOWN){
            curSkulls -= 10;
            curColor = COLOR_RED;
        }

    } while(true);

}

void Inventory_AmountsMenuInit(void){ //TODO
    InventoryAmountsMenu.items[Amounts_Menu_Deku_Sticks].amount = gSaveContext.item_slot_amount[ItemSlots[ITEM_DEKU_STICK]];
    InventoryAmountsMenu.items[Amounts_Menu_Deku_Nuts].amount = gSaveContext.item_slot_amount[ItemSlots[ITEM_DEKU_NUT]];
    InventoryAmountsMenu.items[Amounts_Menu_Bombs].amount = gSaveContext.item_slot_amount[ItemSlots[ITEM_BOMB]];
    InventoryAmountsMenu.items[Amounts_Menu_Arrows].amount = gSaveContext.item_slot_amount[ItemSlots[ITEM_FAIRY_BOW]];
    InventoryAmountsMenu.items[Amounts_Menu_Deku_Seeds].amount = gSaveContext.item_slot_amount[ItemSlots[ITEM_FAIRY_SLINGSHOT]];
    InventoryAmountsMenu.items[Amounts_Menu_Bombchus].amount = gSaveContext.item_slot_amount[ItemSlots[ITEM_BOMBCHU]];
    InventoryAmountsMenu.items[Amounts_Menu_Magic_Beans].amount = gSaveContext.item_slot_amount[ItemSlots[ITEM_MAGIC_BEANS]];
    InventoryAmountsMenu.items[Amounts_Menu_Rupees].amount = gSaveContext.rupee_count;
    InventoryAmountsMenu.items[Amounts_Menu_Double_Defense].amount = 0; //TODO
    InventoryAmountsMenu.items[Amounts_Menu_Heart_Containers].amount = gSaveContext.max_health;
    InventoryAmountsMenu.items[Amounts_Menu_Current_Health].amount = gSaveContext.cur_health;
    InventoryAmountsMenu.items[Amounts_Menu_Magic_meter_size].amount = gSaveContext.magic_meter_size;
    InventoryAmountsMenu.items[Amounts_Menu_Current_Magic].amount = gSaveContext.magic_amt;
    InventoryAmountsMenu.items[Amounts_Menu_Giants_Knife_hits].amount = 0; //TODO
}

void Inventory_AmountsMenuFunc(void){
    Inventory_AmountsMenuInit();
    AmountMenuShow(&InventoryAmountsMenu);
}

void Inventory_AmountsSelect(s32 selected){ //TODO
    switch(selected){
        case(Amounts_Menu_Deku_Sticks):
            gSaveContext.item_slot_amount[ItemSlots[ITEM_DEKU_STICK]] = InventoryAmountsMenu.items[Amounts_Menu_Deku_Sticks].amount;
            break;
        case(Amounts_Menu_Deku_Nuts):
            gSaveContext.item_slot_amount[ItemSlots[ITEM_DEKU_NUT]] = InventoryAmountsMenu.items[Amounts_Menu_Deku_Nuts].amount;
            break;
        case(Amounts_Menu_Bombs):
            gSaveContext.item_slot_amount[ItemSlots[ITEM_BOMB]] = InventoryAmountsMenu.items[Amounts_Menu_Bombs].amount;
            break;
        case(Amounts_Menu_Arrows):
            gSaveContext.item_slot_amount[ItemSlots[ITEM_FAIRY_BOW]] = InventoryAmountsMenu.items[Amounts_Menu_Arrows].amount;
            break;
        case(Amounts_Menu_Deku_Seeds):
            gSaveContext.item_slot_amount[ItemSlots[ITEM_FAIRY_SLINGSHOT]] = InventoryAmountsMenu.items[Amounts_Menu_Deku_Seeds].amount;
            break;
        case(Amounts_Menu_Bombchus):
            gSaveContext.item_slot_amount[ItemSlots[ITEM_BOMBCHU]] = InventoryAmountsMenu.items[Amounts_Menu_Bombchus].amount;
            break;
        case(Amounts_Menu_Magic_Beans):
            gSaveContext.item_slot_amount[ItemSlots[ITEM_MAGIC_BEANS]] = InventoryAmountsMenu.items[Amounts_Menu_Magic_Beans].amount;
            break;
        case(Amounts_Menu_Rupees):
            gSaveContext.rupee_count = InventoryAmountsMenu.items[Amounts_Menu_Rupees].amount;
            break;
        case(Amounts_Menu_Double_Defense): //TODO
            break;
        case(Amounts_Menu_Heart_Containers):
            gSaveContext.max_health = InventoryAmountsMenu.items[Amounts_Menu_Heart_Containers].amount;
            break;
        case(Amounts_Menu_Current_Health):
            gSaveContext.cur_health = InventoryAmountsMenu.items[Amounts_Menu_Current_Health].amount;
            break;
        case(Amounts_Menu_Magic_meter_size):
            gSaveContext.magic_meter_size = InventoryAmountsMenu.items[Amounts_Menu_Magic_meter_size].amount;
            break;
        case(Amounts_Menu_Current_Magic):
            gSaveContext.magic_amt = InventoryAmountsMenu.items[Amounts_Menu_Magic_meter_size].amount;
            break;
        case(Amounts_Menu_Giants_Knife_hits): //TODO
            break;
    }
}