#include "menu.h"
#include "menus/warps.h"
#include "draw.h"
#include "z3D/z3D.h"

Menu WarpsMenu = {
    "Warps",
    .nbItems = 2,
    {
        {"Places", MENU, .menu = &WarpsPlacesMenu}, //TODO: list of scenes/entrances to warp to
        {"Manually Enter Entrance Index", METHOD, .method = NULL},    
    }
};

Menu WarpsPlacesMenu = {
    "Places",
    .nbItems = 7,
    {
        {"Dungeons", MENU, .menu = &WarpsPlacesDungeonsMenu},
        {"Bosses", MENU, .menu = &WarpsPlacesBossesMenu},
        {"Towns", MENU, .menu = &WarpsPlacesTownsMenu},
        {"Houses", MENU, .menu = &WarpsPlacesHousesMenu},
        {"Shops", MENU, .menu = &WarpsPlacesShopsMenu},
        {"Misc", MENU, .menu = &WarpsPlacesMiscMenu},
        {"Overworld", MENU, .menu = &WarpsPlacesOverworldMenu},
    }
};

Menu WarpsPlacesDungeonsMenu = {
    "Dungeons",
    .nbItems = 17,
    {
        {"0: Inside the Deku Tree", MENU, .menu = NULL},
        {"1: Dodongo's Cavern", MENU, .menu = NULL},
        {"2: Inside Jabu-Jabu's Belly", MENU, .menu = NULL},
        {"3: Forest Temple", MENU, .menu = NULL},
        {"4: Fire Temple", MENU, .menu = NULL},
        {"5: Water Temple", MENU, .menu = NULL},
        {"6: Spirit Temple", MENU, .menu = NULL},
        {"7: Shadow Temple", MENU, .menu = NULL},
        {"8: Bottom of the Well", MENU, .menu = NULL},
        {"9: Ice Cavern", MENU, .menu = NULL},
        {"10: Ganon's Tower", MENU, .menu = NULL},
        {"11: Gerudo Training Ground", MENU, .menu = NULL},
        {"12: Thieve's Hideout", MENU, .menu = NULL},
        {"13: Inside Ganon's Castle", MENU, .menu = NULL},
        {"14: Ganon's Tower (Collapsing)", MENU, .menu = NULL},
        {"15: Inside Ganon's Castle (Collapsing)", MENU, .menu = NULL},
        {"26: Ganon's Tower Exterior (Collapsing)", MENU, .menu = NULL},
    }
};

Menu WarpsPlacesBossesMenu = {
    "Bosses",
    .nbItems = 10,
    {
        {"17: Gohma's Lair", MENU, .menu = NULL},
        {"18: King Dodongo's Lair", MENU, .menu = NULL},
        {"19: Barinade's Lair", MENU, .menu = NULL},
        {"20: Phantom Ganon's Lair", MENU, .menu = NULL},
        {"21: Volvagia's Lair", MENU, .menu = NULL},
        {"22: Morpha's Lair", MENU, .menu = NULL},
        {"23: Twinrova's Lair & Nabooru's Mini-Boss Room", MENU, .menu = NULL},
        {"24: Bongo Bongo's Lair", MENU, .menu = NULL},
        {"25: Ganondorf's Lair", MENU, .menu = NULL},
        {"79: Ganon's Tower Collapse & Battle Arena", MENU, .menu = NULL},
    }
};

Menu WarpsPlacesTownsMenu = {
    "Towns",
    .nbItems = 16,
    {
        {"82: Kakariko Village", MENU, .menu = NULL},
        {"85: Kokiri Forest", MENU, .menu = NULL},
        {"88: Zora's Domain", MENU, .menu = NULL},
        {"98: Goron City", MENU, .menu = NULL},
        {"99: Lon Lon Ranch", MENU, .menu = NULL},
        {"32: Market (Child - Day)", MENU, .menu = NULL},
        {"33: Market (Child - Night)", MENU, .menu = NULL},
        {"34: Market (Ruins)", MENU, .menu = NULL},
        {"27: Market Entrance (Child - Day)", MENU, .menu = NULL},
        {"28: Market Entrance (Child - Night)", MENU, .menu = NULL},
        {"29: Market Entrance (Ruins)", MENU, .menu = NULL},
        {"30: Back Alley (Child - Day)", MENU, .menu = NULL},
        {"31: Back Alley (Child - Night)", MENU, .menu = NULL},
        {"35: Temple of Time Exterior (Child - Day)", MENU, .menu = NULL},
        {"36: Temple of Time Exterior (Child - Night)", MENU, .menu = NULL},
        {"37: Temple of Time Exterior (Ruins)", MENU, .menu = NULL},
    }
};

Menu WarpsPlacesHousesMenu = {
    "Houses",
    .nbItems = 15,
    {
        {"52: Link's House", MENU, .menu = NULL},
        {"38: Know-It-All Brothers' House", MENU, .menu = NULL},
        {"39: House of Twins", MENU, .menu = NULL},
        {"40: Mido's House", MENU, .menu = NULL},
        {"41: Saria's House", MENU, .menu = NULL},
        {"42: Carpenter Boss's House", MENU, .menu = NULL},
        {"43: Back Alley House (Man in Green)", MENU, .menu = NULL},
        {"53: Back Alley House (Dog Lady)", MENU, .menu = NULL},
        {"54: Stable", MENU, .menu = NULL},
        {"55: Impa's House", MENU, .menu = NULL},
        {"57: Carpenters' Tent", MENU, .menu = NULL},
        {"58: Gravekeeper's Hut", MENU, .menu = NULL},
        {"76: Ranch House & Silo", MENU, .menu = NULL},
        {"77: Guard House", MENU, .menu = NULL},
        {"80: House of Skulltula", MENU, .menu = NULL},
    }
};

Menu WarpsPlacesShopsMenu = {
    "Shops",
    .nbItems = 12,
    {
        {"44: Bazaar", MENU, .menu = NULL},
        {"45: Kokiri Shop", MENU, .menu = NULL},
        {"46: Goron Shop", MENU, .menu = NULL},
        {"47: Zora Shop", MENU, .menu = NULL},
        {"48: Kakariko Potion Shop", MENU, .menu = NULL},
        {"49: Market Potion Shop", MENU, .menu = NULL},
        {"50: Bombchu Shop", MENU, .menu = NULL},
        {"51: Happy Mask Shop", MENU, .menu = NULL},
        {"66: Shooting Gallery", MENU, .menu = NULL},
        {"75: Bombchu Bowling Alley", MENU, .menu = NULL},
        {"78: Granny's Potion Shop", MENU, .menu = NULL},
        {"16: Treasure Box Shop", MENU, .menu = NULL},
    }
};

Menu WarpsPlacesMiscMenu = {
    "Misc",
    .nbItems = 15,
    {
        {"67: Temple of Time", MENU, .menu = NULL},
        {"74: Castle Courtyard", MENU, .menu = NULL},
        {"72: Dampe's Grace & Windmill", MENU, .menu = NULL},
        {"69: Castle Hedge Maze (Day)", MENU, .menu = NULL},
        {"70: Castle Hedge Maze (Night)", MENU, .menu = NULL},
        {"56: Lakeside Laboratory", MENU, .menu = NULL},
        {"59: Great Fairy's Fountain (Upgrades)", MENU, .menu = NULL},
        {"61: Great Fairy's Fountain (Spells)", MENU, .menu = NULL},
        {"65: Royal Family's Tomb", MENU, .menu = NULL},
        {"62: Grottos", MENU, .menu = NULL},
        {"63: Grave (Redead)", MENU, .menu = NULL},
        {"64: Grave (Fairy's Fountain)", MENU, .menu = NULL},
        {"68: Chamber of the Sages", MENU, .menu = NULL},
        {"71: Cutscene Map", MENU, .menu = NULL},
        {"60: Fairy's Fountain", MENU, .menu = NULL},
    }
};

Menu WarpsPlacesOverworldMenu = {
    "Overworld",
    .nbItems = 16,
    {
        {"81: Hyrule Field", MENU, .menu = NULL},
        {"91: Lost Woods", MENU, .menu = NULL},
        {"86: Sacred Forest Meadow", MENU, .menu = NULL},
        {"96: Death Mountain Trail", MENU, .menu = NULL},
        {"97: Death Mountain Crater", MENU, .menu = NULL},
        {"84: Zora's River", MENU, .menu = NULL},
        {"89: Zora's Fountain", MENU, .menu = NULL},
        {"87: Lake Hylia", MENU, .menu = NULL},
        {"95: Hyrule Castle", MENU, .menu = NULL},
        {"100: Ganon's Castle Exterior", MENU, .menu = NULL},
        {"90: Gerudo Valley", MENU, .menu = NULL},
        {"93: Gerudo's Fortress", MENU, .menu = NULL},
        {"94: Haunted Wasteland", MENU, .menu = NULL},
        {"92: Desert Colossus", MENU, .menu = NULL},
        {"83: Graveyard", MENU, .menu = NULL},
        {"73: Fishing Pond", MENU, .menu = NULL},
    }
};
