#include "menu.h"
#include "menus/debug.h"
#include "draw.h"
#include "z3D/z3D.h"
#include <stdio.h>


#define ACTOR_LIST_MAX_SHOW 15

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
    "ITEMACTION",
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
        Draw_DrawFormattedString(30, 30 + 3 * SPACING_Y, COLOR_WHITE, "Pos:             x:%05.2f  y:%05.2f  z:%05.2f", actor->posRot.pos.x, actor->posRot.pos.y, actor->posRot.pos.z);
        Draw_DrawFormattedString(30, 30 + 4 * SPACING_Y, COLOR_WHITE, "Rot:             x:%04X  y:%04X  z:%04X", actor->posRot.rot.x & 0xFFFF, actor->posRot.rot.y & 0xFFFF, actor->posRot.rot.z & 0xFFFF);
        Draw_DrawFormattedString(30, 30 + 5 * SPACING_Y, COLOR_WHITE, "Vel:             x:%05.2f  y:%05.2f  z:%05.2f", actor->velocity.x, actor->velocity.y, actor->velocity.z);
        Draw_DrawFormattedString(30, 30 + 6 * SPACING_Y, COLOR_WHITE, "Floor:           %08X", actor->floorPoly);
        Draw_DrawFormattedString(30, 30 + 7 * SPACING_Y, COLOR_WHITE, "Dist. from Link: xz:%05.2f  y:%05.2f", actor->xzDistanceFromLink, actor->yDistanceFromLink);
        Draw_DrawFormattedString(30, 30 + 8 * SPACING_Y, COLOR_WHITE, "Text ID:         %04X", actor->textId & 0xFFFF);
        Draw_DrawFormattedString(30, 30 + 9 * SPACING_Y, COLOR_WHITE, "Held By:         %08X", actor->attachedA);
        Draw_DrawFormattedString(30, 30 + 10 * SPACING_Y, COLOR_WHITE, "Holding:         %08X", actor->attachedB);

        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "Press START to bring actor to Link");

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = waitInputWithTimeout(1000);
        if(pressed & BUTTON_B)
            break;
        else if(pressed & BUTTON_START)
        {
            actor->posRot.pos = PLAYER->actor.posRot.pos;
            actor->posRot.rot = PLAYER->actor.posRot.rot;
        }

    } while(true);
}

static void DebugActors_ShowActors(void) {
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
        
        char typeBuf[65] = { 0 };
        sprintf(typeBuf, "Filter by type (R/L to move): %s", ActorTypeNames[type]);
        Draw_DrawString(30, 30, COLOR_RED, typeBuf);

        for (s32 i = 0; i < ACTOR_LIST_MAX_SHOW && page * ACTOR_LIST_MAX_SHOW + i < listSize; ++i)
        {
            s32 j = page * ACTOR_LIST_MAX_SHOW + i;
            Draw_DrawFormattedString(30, 30 + (1 + i) * SPACING_Y, COLOR_WHITE, "Addr: %08X  ID: %04X", actorList[j].instance, actorList[j].id & 0xFFFF);
            Draw_DrawCharacter(10, 30 + (1 + i) * SPACING_Y, COLOR_TITLE, j == selected ? '>' : ' ');
        }

        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "Select with A to show more details, X to delete");

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = waitInputWithTimeout(1000);
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
        else if(pressed & BUTTON_X)
        {
            Actor_Kill(actorList[selected].instance);
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

    } while(true);
}

Menu DebugMenu = {
    "Debug",
    .nbItems = 2,
    {
        {"Actors", METHOD, .method = DebugActors_ShowActors},
        {"Flags (TODO)", METHOD, .method = NULL}, //TODO
    }
};
