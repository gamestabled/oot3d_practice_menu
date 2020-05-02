#include "menu.h"
#include "menus/scene.h"
#include "draw.h"
#include "z3D/z3D.h"

static Menu CollisionMenu = {
    "Collision",
    .nbItems = 1,
    {
        {"TODO Placeholder", METHOD, .method = NULL}, //TODO: Collision options
    }
};

static Menu CameraMenu = {
    "Free camera",
    .nbItems = 1,
    {
        {"TODO Placeholder", METHOD, .method = NULL}, //TODO: free camera options
    }
};

Menu SceneMenu = {
    "Scene",
    .nbItems = 2,
    {
        {"Collision (TODO)", MENU, .menu = &CollisionMenu},
        {"Free camera (TODO)", MENU, .menu = &CameraMenu},
    }
};
