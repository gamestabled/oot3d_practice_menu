#include "menu.h"
#include "menus/debug.h"
#include "menus/commands.h"
#include "menus/watches.h"
#include "draw.h"
#include "input.h"
#include "common.h"
#include "z3D/z3D.h"
#include <stdio.h>


#define ACTOR_LIST_MAX_SHOW 15

//new actor values
static s16 newId = 0x0010;
static s16 newParams = 0x0000;
static u8  storedPosRotIndex = 0;

typedef struct {
    Actor* instance;
    s16    id;
    s16    params;
} ShowActor_Info;

static const char* const ActorTypeNames[] = {
    "SWITCH", //0x0
    "BG",
    "PLAYER",
    "EXPLOSIVES",
    "NPC",
    "ENEMY",
    "PROP",
    "ITEM/ACTION",
    "MISC",
    "BOSS",
    "DOOR",
    "CHEST",
    "ALL", //0xC
};

/* give type 0xC for "all" */
static s32 PopulateActorList(ShowActor_Info* list, ActorType type){
    s32 i = 0;
    ActorHeapNode* cur = (ActorHeapNode*)((u32)PLAYER - sizeof(ActorHeapNode));
    while (cur){
        if (!cur->free){
            Actor* actor = (Actor*)((u32)cur + sizeof(ActorHeapNode));
            if (type == 0xC || actor->type == type){
                list[i].instance = actor;
                list[i].id = actor->id;
                list[i].params = actor->params;
                ++i;
            }
        }
        cur = cur->next;
    }
    return i;
}

static void DebugActors_ShowMoreInfo(Actor* actor) {
    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        Draw_DrawString(10, 10, COLOR_TITLE, "Actor Details");
        Draw_DrawFormattedString(30, 30, COLOR_WHITE, "ID:              %04X", actor->id);
        Draw_DrawFormattedString(30, 30 + SPACING_Y, COLOR_WHITE, "Type:            %s", ActorTypeNames[actor->type]);
        Draw_DrawFormattedString(30, 30 + 2 * SPACING_Y, COLOR_WHITE, "Params:          %04X", actor->params & 0xFFFF);
        Draw_DrawFormattedString(30, 30 + 3 * SPACING_Y, COLOR_WHITE, "Pos:             x:%05.2f  y:%05.2f  z:%05.2f", actor->world.pos.x, actor->world.pos.y, actor->world.pos.z);
        Draw_DrawFormattedString(30, 30 + 4 * SPACING_Y, COLOR_WHITE, "Rot:             x:%04X  y:%04X  z:%04X", actor->world.rot.x & 0xFFFF, actor->world.rot.y & 0xFFFF, actor->world.rot.z & 0xFFFF);
        Draw_DrawFormattedString(30, 30 + 5 * SPACING_Y, COLOR_WHITE, "Vel:             x:%05.2f  y:%05.2f  z:%05.2f", actor->velocity.x, actor->velocity.y, actor->velocity.z);
        Draw_DrawFormattedString(30, 30 + 6 * SPACING_Y, COLOR_WHITE, "Floor:           %08X", actor->floorPoly);
        Draw_DrawFormattedString(30, 30 + 7 * SPACING_Y, COLOR_WHITE, "Dist. from Link: xz:%05.2f  y:%05.2f", actor->xyzDistToPlayerSq, actor->xzDistToPlayer);
        Draw_DrawFormattedString(30, 30 + 8 * SPACING_Y, COLOR_WHITE, "Text ID:         %04X", actor->textId & 0xFFFF);
        Draw_DrawFormattedString(30, 30 + 9 * SPACING_Y, COLOR_WHITE, "Held By:         %08X", actor->parent);
        Draw_DrawFormattedString(30, 30 + 10 * SPACING_Y, COLOR_WHITE, "Holding:         %08X", actor->child);

        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 30, COLOR_TITLE, "Press START to bring this actor to Link");
        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "Press SELECT to bring Link to this actor");

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);
        if(pressed & BUTTON_B)
            break;
        else if(pressed & BUTTON_START)
        {
            actor->world.pos = PLAYER->actor.world.pos;
            actor->world.rot = PLAYER->actor.world.rot;
        }
        else if(pressed & BUTTON_SELECT)
        {
            PLAYER->actor.world.pos = actor->world.pos;
            PLAYER->actor.world.rot = actor->world.rot;
            PLAYER->actor.home.pos = actor->world.pos;
            PLAYER->actor.home.rot = actor->world.rot;
        }

    } while(menuOpen);
}

static void DebugActors_SpawnActor(void) {
    PosRot selectedPosRot = storedPosRot[storedPosRotIndex];

    do
    {
        Draw_Lock();
        Draw_DrawString(10, 10, COLOR_TITLE, "Spawn new Actor");
        Draw_DrawFormattedString(30, 70, COLOR_WHITE, "ID: %04X", (u16)newId);
        Draw_DrawFormattedString(100, 70, COLOR_WHITE, "Params: %04X", (u16)newParams);
        Draw_DrawFormattedString(200, 70, COLOR_WHITE, "Stored Position: %01d", storedPosRotIndex);

        Draw_DrawFormattedString(30, 100, COLOR_WHITE, "Pos:      X:%05.2f  Y:%05.2f  Z:%05.2f", selectedPosRot.pos.x, selectedPosRot.pos.y, selectedPosRot.pos.z);
        Draw_DrawFormattedString(30, 120, COLOR_WHITE, "Rot:      X:%04X  Y:%04X  Z:%04X", (u16)selectedPosRot.rot.x, (u16)selectedPosRot.rot.y, (u16)selectedPosRot.rot.z);

        Draw_DrawString(30, 160, COLOR_TITLE, "A: Edit      X: Fetch Position from Link\n"
                                              "B: Cancel    Y: Confirm and Spawn");

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);

        if (pressed & BUTTON_B){
            break;
        }
        if (pressed & BUTTON_A){
            Debug_NewActorValuesMenuShow();
            selectedPosRot = storedPosRot[storedPosRotIndex];
        }
        else if ((pressed & BUTTON_X)){
            selectedPosRot = PLAYER->actor.world;
        }
        else if (pressed & BUTTON_Y){
            PosRot p = selectedPosRot;
            Actor_Spawn(&(gGlobalContext->actorCtx), gGlobalContext, newId, p.pos.x, p.pos.y, p.pos.z, p.rot.x, p.rot.y, p.rot.z, newParams);
            break;
        }

    } while(menuOpen);
}

static void DebugActors_ShowActors(void) {
    if(!isInGame()) {
        return;
    }
    static ShowActor_Info actorList[200];
    s32 selected = 0, page = 0, pagePrev = 0;
    s32 type = 0xC;
    s32 listSize = 0;

    listSize = PopulateActorList(actorList, 0xC);

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        if (page != pagePrev)
        {
            Draw_ClearFramebuffer();
        }
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Currently Loaded Actors");
        Draw_DrawFormattedString(30, 30, COLOR_RED, "Filter by type (R/L to move): %s", ActorTypeNames[type]);

        for (s32 i = 0; i < ACTOR_LIST_MAX_SHOW && page * ACTOR_LIST_MAX_SHOW + i < listSize; ++i)
        {
            s32 j = page * ACTOR_LIST_MAX_SHOW + i;
            Actor* act = actorList[j].instance;
            u32 curColor = ((act->flags & 0x1) || act->draw != NULL || act->update != NULL) ? COLOR_WHITE : COLOR_GRAY;
            Draw_DrawFormattedString(30, 30 + (1 + i) * SPACING_Y, curColor, "Addr: %08X  ID: %04X", actorList[j].instance, actorList[j].id & 0xFFFF);
            Draw_DrawCharacter(10, 30 + (1 + i) * SPACING_Y, COLOR_TITLE, j == selected ? '>' : ' ');
        }

        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "A: Details    X: Delete    Y: Spawn new Actor");

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);
        if(pressed & BUTTON_B)
            break;
        if(pressed & BUTTON_A)
        {
            DebugActors_ShowMoreInfo(actorList[selected].instance);
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
        }
        else if(pressed & BUTTON_Y)
        {
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();

            DebugActors_SpawnActor();

            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
        }
        else if(pressed & BUTTON_X)
        {
            // prevent accidentally deleting the player actor
            if(actorList[selected].instance->id != 0 || ADDITIONAL_FLAG_BUTTON) {
                Actor_Kill(actorList[selected].instance);
            }
        }
        else if(pressed & BUTTON_DOWN)
        {
            selected++;
        }
        else if(pressed & BUTTON_UP)
        {
            selected--;
        }
        else if(pressed & BUTTON_LEFT)
        {
            selected -= ACTOR_LIST_MAX_SHOW;
        }
        else if(pressed & BUTTON_RIGHT)
        {
            selected += ACTOR_LIST_MAX_SHOW;
        }
        else if(pressed & BUTTON_R1)
        {
            type++;
            if (type > 0xC) type = 0;
            selected = 0;
            page = 0;
            pagePrev = -1;
            listSize = PopulateActorList(actorList, type);
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
            continue;
        }
        else if(pressed & BUTTON_L1)
        {
            type--;
            if (type < 0) type = 0xC;
            selected = 0;
            page = 0;
            pagePrev = -1;
            listSize = PopulateActorList(actorList, type);
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
            continue;
        }

        if(selected < 0)
        {
            selected = listSize - 1;
        }
        else if(selected >= listSize)
        {
            selected = 0;
        }

        pagePrev = page;
        page = selected / ACTOR_LIST_MAX_SHOW;

    } while(menuOpen);
}

AmountMenu NewActorValuesMenu = {
    "New Actor Values",
    .nbItems = 3,
    {
        {0, 1, 0, "ID", .method = NULL},
        {0, 1, 0, "Params", .method = NULL},
        {0, 0, 8, "Stored Position Index", .method = NULL},
    }
};

void NewActorValuesMenuInit() {
    NewActorValuesMenu.items[0].amount = newId;
    NewActorValuesMenu.items[1].amount = newParams;
    NewActorValuesMenu.items[2].amount = storedPosRotIndex;
}

void Debug_NewActorValuesMenuShow() {
    NewActorValuesMenuInit();
    AmountMenuShow(&NewActorValuesMenu);
    newId = NewActorValuesMenu.items[0].amount;
    newParams = NewActorValuesMenu.items[1].amount;
    storedPosRotIndex = NewActorValuesMenu.items[2].amount;
    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();
}

Menu DebugMenu = {
    "Debug",
    .nbItems = 2,
    {
        {"Actors", METHOD, .method = DebugActors_ShowActors},
        {"Flags (TODO)", METHOD, .method = NULL}, //TODO
    }
};
