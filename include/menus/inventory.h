#pragma once

#include "menu.h"
#include "z3D/z3D.h"

extern Menu InventoryMenu;
extern ToggleMenu InventoryItemsMenu;
extern ToggleMenu InventoryBottlesMenu;
extern ToggleMenu InventoryChildTradeMenu;
extern ToggleMenu InventoryAdultTradeMenu;
extern ToggleMenu InventoryRightGearMenu;
extern ToggleMenu InventoryLeftGearMenu;
extern AmountMenu InventoryAmountsMenu;

void Inventory_ItemsMenuFunc(void);
void Inventory_ItemsToggle(s32);
void Inventory_BottlesMenuFunc(s32);
void Inventory_BottleSelect(s32);
void Inventory_ChildTradeMenuFunc(s32);
void Inventory_AdultTradeMenuFunc(s32);
void Inventory_ChildTradeSelect(s32);
void Inventory_AdultTradeSelect(s32);
void Inventory_BootsToggle(s32);

void Inventory_RightGearMenuFunc(void);
void Inventory_RightGearToggle(s32);
void Inventory_LeftGearMenuFunc(void);
void Inventory_LeftGearToggle(s32);
void Inventory_HeartPiecesAmount(s32);
void Inventory_GoldSkulltulaAmount(s32);

void Inventory_SongsMenuFunc(void);
void Inventory_SongsToggle(s32);

void Inventory_AmountsMenuFunc(void);
void Inventory_AmountsSelect(s32);

enum { //Right Side Gear Menu Choices
    Gear_Menu_Kokiri_Sword = 0,
    Gear_Menu_Master_Sword,
    Gear_Menu_Giants_Knife,
    Gear_Menu_Broken_Giants_Knife,
    Gear_Menu_Biggoron_Sword,
    Gear_Menu_Deku_Shield,
    Gear_Menu_Hylian_Shield,
    Gear_Menu_Mirror_Shield,
    Gear_Menu_Kokiri_Tunic,
    Gear_Menu_Goron_Tunic,
    Gear_Menu_Zora_Tunic,
    Gear_Menu_Bullet_Bag_30,
    Gear_Menu_Bullet_Bag_40,
    Gear_Menu_Bullet_Bag_50,
    Gear_Menu_Quiver_30,
    Gear_Menu_Quiver_40,
    Gear_Menu_Quiver_50,
    Gear_Menu_Bomb_Bag_20,
    Gear_Menu_Bomb_Bag_30,
    Gear_Menu_Bomb_Bag_40,
    Gear_Menu_Gorons_Bracelet,
    Gear_Menu_Silver_Gauntlets,
    Gear_Menu_Golden_Gauntlets,
    Gear_Menu_Silver_Scale,
    Gear_Menu_Golden_Scale,
    Gear_Menu_Adults_Wallet,
    Gear_Menu_Giants_Wallet,
    Gear_Menu_Unused_Wallet,
};

enum { //Left Side Gear Menu Choices
    Gear_Menu_Forest_Medallion,
    Gear_Menu_Fire_Medallion,
    Gear_Menu_Water_Medallion,
    Gear_Menu_Spirit_Medallion,
    Gear_Menu_Shadow_Medallion,
    Gear_Menu_Light_Medallion,
    Gear_Menu_Kokiri_Emerald,
    Gear_Menu_Gorons_Ruby,
    Gear_Menu_Zoras_Sapphire,
    Gear_Menu_Pieces_of_Heart,
    Gear_Menu_Shard_of_Agony,
    Gear_Menu_Gerudo_Token,
    Gear_Menu_Gold_Skulltulas,
};

enum { //Songs Menu Choices
    Songs_Menu_Zeldas_Lullaby,
    Songs_Menu_Eponas_Song,
    Songs_Menu_Sarias_Song,
    Songs_Menu_Suns_Song,
    Songs_Menu_Song_of_Time,
    Songs_Menu_Song_of_Storms,
    Songs_Menu_Minuet,
    Songs_Menu_Bolero,
    Songs_Menu_Serenade,
    Songs_Menu_Requiem,
    Songs_Menu_Nocturne,
    Songs_Menu_Prelude,
};

enum { //Amounts Menu Choices
    Amounts_Menu_Deku_Sticks,
    Amounts_Menu_Deku_Nuts,
    Amounts_Menu_Bombs,
    Amounts_Menu_Arrows,
    Amounts_Menu_Deku_Seeds,
    Amounts_Menu_Bombchus,
    Amounts_Menu_Magic_Beans,
    Amounts_Menu_Rupees,
    Amounts_Menu_Giants_Knife_hits,
    Amounts_Menu_Double_Defense,
    Amounts_Menu_Magic_meter_size,
    Amounts_Menu_Heart_Containers,
    Amounts_Menu_Current_Health,
    Amounts_Menu_Current_Magic,
};