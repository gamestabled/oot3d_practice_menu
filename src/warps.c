#include "menu.h"
#include "menus/warps.h"
#include "draw.h"
#include "z3d.h"

Menu WarpsMenu = {
    "Warps",
    .nbItems = 1,
    {
        {"TODO Placeholder", METHOD, .method = NULL}, //TODO: list of scenes/entrances to warp to
    }
};
