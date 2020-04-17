#include "menu.h"
#include "menus/scene.h"
#include "draw.h"
#include "z3d.h"

Menu CollisionMenu;
Menu CameraMenu;

Menu SceneMenu = {
    "Scene",
    .nbItems = 2,
    {
        {"Collision", MENU, .menu = &CollisionMenu},
        {"Free camera", MENU, .menu = &CameraMenu},
    }
};

Menu CollisionMenu = {
    "Collision",
    .nbItems = 1,
    {
        {"TODO Placeholder", METHOD, .method = NULL}, //TODO: Collision options
    }
};

Menu CameraMenu = {
    "Free camera",
    .nbItems = 1,
    {
        {"TODO Placeholder", METHOD, .method = NULL}, //TODO: free camera options
    }
};