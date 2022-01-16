#include "menu.h"
#include "menus/scene.h"
#include "draw.h"
#include "z3D/z3D.h"
#include "common.h"
#include "input.h"

u8 noClip = 0;
u8 releasedABbuttons = 0;
void dummyActorFunction(Actor* thisx, GlobalContext* globalCtx) {}
void* storedPlayerUpdateFunction = &dummyActorFunction;

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

AmountMenu RoomNumberMenu = {
    "Choose a Room Number, then void out :)",
    .nbItems = 1,
    {
        {0, 0, 28, "Room Number", .method = Scene_SetRoomNumberinEP},
    }
};

ToggleMenu HideEntitiesMenu = {
    "Hide Game Entities",
    .nbItems = 2,
    {
        {0, "Hide Rooms", .method = Scene_HideRoomsToggle},
        {0, "Hide Actors (TODO)", .method = NULL},
    }
};

Menu SceneMenu = {
    "Scene",
    .nbItems = 8,
    {
        {"NoClip / Move Link", METHOD, .method = Scene_NoClipDescription},
        {"Set Entrance Point", METHOD, .method = Scene_SetEntrancePoint},
        {"Set flags", METHOD, .method = Scene_SetFlags},
        {"Clear flags", METHOD, .method = Scene_ClearFlags},
        {"Room \"selector\" (not really)", METHOD, .method = Scene_RoomNumberMenuShow},
        {"Collision (TODO)", MENU, .menu = &CollisionMenu},
        {"Free camera (TODO)", MENU, .menu = &CameraMenu},
        {"Hide Game Entities", METHOD, .method = Scene_HideEntitiesMenuShow},
    }
};

void Scene_SetEntrancePoint(void) {
    gSaveContext.respawn[0] = (RespawnData){
        PLAYER->actor.world.pos,
        PLAYER->actor.shape.rot.y,
        (ADDITIONAL_FLAG_BUTTON ? 0x0EFF : 0x0DFF),
        gSaveContext.entranceIndex,
        gGlobalContext->roomCtx.currentRoomNumber,
        0,
        gGlobalContext->actorCtx.flags.tempSwch,
        gGlobalContext->actorCtx.flags.tempCollect,
    };
    alertMessage = ADDITIONAL_FLAG_BUTTON ? "EP set as from EPG" : "EP set!";
    alertFrames = 10;
    drawAlert();
}

void Scene_RoomNumberMenuInit(void) {
    RoomNumberMenu.items[0].amount = gSaveContext.respawn[0].roomIndex;
}

void Scene_RoomNumberMenuShow(void) {
    Scene_RoomNumberMenuInit();
    AmountMenuShow(&RoomNumberMenu);
}

void Scene_SetRoomNumberinEP(s32 selected) {
    gSaveContext.respawn[0].roomIndex = RoomNumberMenu.items[0].amount;
}

void Scene_SetFlags(void) {
    gGlobalContext->actorCtx.flags.swch = 0xFFFFFFFF;
    gGlobalContext->actorCtx.flags.tempSwch = 0xFFFFFFFF;
    gGlobalContext->actorCtx.flags.chest = 0xFFFFFFFF;
    gGlobalContext->actorCtx.flags.clear = 0xFFFFFFFF;
    gGlobalContext->actorCtx.flags.tempClear = 0xFFFFFFFF;
    gGlobalContext->actorCtx.flags.collect = 0xFFFFFFFF;
    gGlobalContext->actorCtx.flags.tempCollect = 0xFFFFFFFF;
}

void Scene_ClearFlags(void) {
    gGlobalContext->actorCtx.flags.swch = 0;
    gGlobalContext->actorCtx.flags.tempSwch = 0;
    gGlobalContext->actorCtx.flags.chest = 0;
    gGlobalContext->actorCtx.flags.clear = 0;
    gGlobalContext->actorCtx.flags.tempClear = 0;
    gGlobalContext->actorCtx.flags.collect = 0;
    gGlobalContext->actorCtx.flags.tempCollect = 0;
}

void Scene_NoClipToggle(void) {
    if (isInGame()) {
        if (!noClip) {
            storedPlayerUpdateFunction = PLAYER->actor.update;
            PLAYER->actor.update = dummyActorFunction;
            PLAYER->stateFlags2 |= 0x08000000; //freeze actors (ocarina state)
            noClip = 1;
        }
        else {
            PLAYER->actor.update = storedPlayerUpdateFunction;
            PLAYER->stateFlags2 &= ~0x08000000; //unfreeze actors
            noClip = 0;
        }
        menuOpen = 0;
        releasedABbuttons = 0;
    }
}

void Scene_NoClipDescription(void) {

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_DrawString(10, 10, COLOR_TITLE, "NoClip");
    Draw_DrawString(30, 30, COLOR_WHITE, "Move Link freely in the 3D space, bypassing\n"
                                        "collision detection.\n"
                                        "Press A to start, B to cancel.\n\n"
                                        "Commands:\n"
                                        "DPad   - Move horizontally\n"
                                        "L+DPad - Move vertically\n"
                                        "Hold R - Move fast\n"
                                        "X/Y    - Freeze/Unfreeze actors\n"
                                        "A      - Quit and confirm position\n"
                                        "B      - Quit and cancel movement\n\n"
                                        "For now, movement only follows the cardinal\n"
                                        "directions, regardless of camera orientation.");
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        u32 pressed = Input_WaitWithTimeout(1000);

        if (pressed & BUTTON_B){
            break;
        }
        if (pressed & BUTTON_A){
            Scene_NoClipToggle();
        }
    }while(menuOpen);
}

void Scene_HideEntitiesMenuShow() {
    ToggleMenuShow(&HideEntitiesMenu);
}

void Scene_HideRoomsToggle(s32 selected) {
    gStaticContext.renderGeometryDisable = !gStaticContext.renderGeometryDisable;
    HideEntitiesMenu.items[0].on = !HideEntitiesMenu.items[0].on;
}
