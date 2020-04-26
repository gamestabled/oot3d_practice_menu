#include "menu.h"
#include "menus/debug.h"
#include "draw.h"
#include "z3D/z3D.h"
#include <stdio.h>


Menu DebugMenu = {
    "Debug",
    .nbItems = 3,
    {
        {"Actors", METHOD, .method = DebugActors_ShowActors},
        {"Flags", METHOD, .method = NULL}, //TODO
        {"Memory", METHOD, .method = NULL}, //TODO
    }
};

typedef struct {
    Actor* instance;
    s16    id;
    s16    params;
} ShowActor_Info;

/* give type 0xC for "all" */
s32 PopulateActorList(ShowActor_Info* list, ActorType type){
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

void DebugActors_ShowMoreInfo(Actor* actor){ //TODO

}

void DebugActors_ShowActors(void){
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
            char buf[65] = { 0 };
            s32 j = page * ACTOR_LIST_MAX_SHOW + i;
            // sprintf(buf, "Addr: %08X ID: %04X Params: %04X", actorList[j].instance, actorList[j].id, actorList[j].params);
            sprintf(buf, "Addr: %08X ID: %04X", actorList[j].instance, actorList[j].id);

            Draw_DrawString(30, 30 + (1 + i) * SPACING_Y, COLOR_WHITE, buf);
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

const char* ActorTypeNames[] = {
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