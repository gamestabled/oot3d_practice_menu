#include "menu.h"
#include "menus/debug.h"
#include "menus/commands.h"
#include "menus/watches.h"
#include "draw.h"
#include "input.h"
#include "common.h"
#include "loader.h"
#include "z3D/z3D.h"
#include <stdio.h>
#include <string.h>


#define ACTOR_LIST_MAX_SHOW 15

//new actor values
static s16 newId = 0x0010;
static s16 newParams = 0x0000;
static u8  storedPosRotIndex = 0;

//Memory Editor values
u32 memoryEditorAddress = (int)&gSaveContext;
static s32 selectedRow = 0;
static s32 selectedColumn = 0;
static u8  isValidMemory = 0;

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

static const char* const FlagGroupNames[] = {
    "switch", //0x0
    "temp_switch",
    "unknown_1",
    "unknown_2",
    "chest",
    "clear",
    "temp_clear",
    "collect",
    "temp_collect",
    "gold_skulltulas",
    "event_chk_inf",
    "item_get_inf",
    "inf_table (part 1/2)",
    "inf_table (part 2/2)",
    "event_inf", // 0xE
};

Menu DebugMenu = {
    "Debug",
    .nbItems = 5,
    {
        {"Objects", METHOD, .method = Debug_ShowObjects},
        {"Actors", METHOD, .method = DebugActors_ShowActors},
        {"Flags", METHOD, .method = Debug_FlagsEditor},
        {"Player States", METHOD, .method = Debug_PlayerStatesMenuShow},
        {"Memory Editor", METHOD, .method = Debug_MemoryEditor},
    }
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

        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 40, COLOR_TITLE, "Press Y to open Memory Editor");
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
        else if(pressed & BUTTON_Y){
            memoryEditorAddress = (int)actor;
            Debug_MemoryEditor();
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
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

void DebugActors_ShowActors(void) {
    if(!isInGame()) {
        return;
    }
    static ShowActor_Info actorList[200];
    static s32 type = 0xC;
    s32 selected = 0, page = 0, pagePrev = 0;
    s32 listSize = 0;

    listSize = PopulateActorList(actorList, type);

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

void Debug_ShowObjects(void) {
    static u16 objectId = 0;
    static s8  digitIdx = 0;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Currently Loaded Objects: %02d/%02d", gGlobalContext->objectCtx.num, OBJECT_EXCHANGE_BANK_MAX);
        Draw_DrawFormattedString(30, 50, COLOR_TITLE, "Object ID: %04X      (Y) Push    (X) Pop", objectId);
        Draw_DrawFormattedString(30 + (14 - digitIdx) * SPACING_X, 50, COLOR_GREEN, "%01X", (objectId >> (digitIdx*4)) & 0xF);

        for (int i = 0; i < gGlobalContext->objectCtx.num; i++) {
            Draw_DrawFormattedString((i % 2 ? 171 : 51), 70 + (i / 2) * SPACING_Y, COLOR_WHITE, "%08X %04X",
                                        &gGlobalContext->objectCtx.status[i], gGlobalContext->objectCtx.status[i].id);
        }
        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);
        if(pressed & BUTTON_B)
            break;
        else if((pressed & BUTTON_Y) && objectId != 0 && gGlobalContext->objectCtx.num < OBJECT_EXCHANGE_BANK_MAX) {
            Object_Spawn(&(gGlobalContext->objectCtx), (s16)objectId);
        }
        else if((pressed & BUTTON_X) && gGlobalContext->objectCtx.num > 0) {
            gGlobalContext->objectCtx.status[--gGlobalContext->objectCtx.num].id = 0;
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
        }
        else if(pressed & BUTTON_UP) {
            objectId += (1 << digitIdx*4);
        }
        else if(pressed & BUTTON_DOWN) {
            objectId -= (1 << digitIdx*4);
        }
        else if(pressed & BUTTON_RIGHT) {
            digitIdx--;
        }
        else if(pressed & BUTTON_LEFT) {
            digitIdx++;
        }

        if(digitIdx > 3)
            digitIdx = 0;
        else if(digitIdx < 0)
            digitIdx = 3;

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

void Debug_FlagsEditor() {
    static s32 row = 0;
    static s32 column = 0;
    static s32 group = 10;
    static u16* flags = (u16*)&gSaveContext.eventChkInf;

    static const u8 RowAmounts[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 11, 14, 4, 16, 14, 4};

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    #define WHITE_OR_BLUE_AT(X,Y) ((row == X && column == Y) ? COLOR_TITLE : COLOR_WHITE)
    #define FLAG_STATUS(X,Y)  (*(flags + X) >> Y & 1)
    #define CURSOR_CHAR 176

    do
    {
        Draw_Lock();
        // Title
        Draw_DrawString(10, 10, COLOR_TITLE, "Flags");
        // Arrows to change group
        Draw_DrawCharacter(70, 30, WHITE_OR_BLUE_AT(0,0), 17);
        Draw_DrawCharacter(90, 30, WHITE_OR_BLUE_AT(0,1), 16);
        // Group name
        Draw_DrawString(120, 30, COLOR_WHITE, FlagGroupNames[group]);
        // Flags column indices
        for (s32 j = 0; j < 16; j++) {
            Draw_DrawFormattedString(70 + j * 2 * SPACING_X, 50, (row > 0 && column == j) ? COLOR_TITLE : COLOR_GRAY, "%X", j);
        }
        // Flags row indices
        for (s32 i = 0; i < RowAmounts[group]; i++) {
            Draw_DrawFormattedString(30, 50 + (i + 1) * SPACING_Y, (row == i + 1) ? COLOR_TITLE : COLOR_GRAY, "%04X", i * 16 + (group == FLAGS_INF_TABLE_2 ? 0x100 : 0));
        }
        // Flags
        for (s32 i = 0; i < RowAmounts[group]; i++) {
            for (s32 j = 0; j < 16; j++) {
                Draw_DrawCharacter(70 + j * 2 * SPACING_X, 50 + (i + 1) * SPACING_Y, FLAG_STATUS(i, j) ? COLOR_GREEN : COLOR_RED, FLAG_STATUS(i, j) ? '1' : '0');
            }
        }
        // Cursor
        if (row > 0) {
            Draw_DrawOverlaidCharacter(70 + column * 2 * SPACING_X, 50 + (row) * SPACING_Y, COLOR_TITLE, CURSOR_CHAR);
        }

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);

        if (pressed & BUTTON_B){
            break;
        }
        else if (pressed & BUTTON_A){
            if(row != 0) {
                *(flags + row - 1) ^= 1 << column;
            }
            else {
                group += (column == 0 ? -1 : 1);
                if(group > 14) group = 0;
                else if(group < 0) group = 14;

                switch (group) {
                    case FLAGS_GOLD_SKULLTULAS  : flags = (u16*)&gSaveContext.gsFlags; break;
                    case FLAGS_EVENT_CHK_INF    : flags = (u16*)&gSaveContext.eventChkInf; break;
                    case FLAGS_ITEM_GET_INF     : flags = (u16*)&gSaveContext.itemGetInf; break;
                    case FLAGS_INF_TABLE_1      : flags = (u16*)&gSaveContext.infTable; break;
                    case FLAGS_INF_TABLE_2      : flags = ((u16*)&gSaveContext.infTable) + 16; break;
                    case FLAGS_EVENT_INF        : flags = (u16*)&gSaveContext.eventInf; break;
                    default : flags = ((u16*)&(gGlobalContext->actorCtx.flags.swch)) + group * 2; break;
                }

                Draw_Lock();
                Draw_ClearFramebuffer();
                Draw_Unlock();
            }
        }
        else{
            if (pressed & BUTTON_UP){
                row--;
                if (row == 0 && column > 1) column = 1;
            }
            if (pressed & BUTTON_DOWN){
                row++;
                if (row > RowAmounts[group] && column > 1) column = 1;
            }
            if (pressed & BUTTON_RIGHT){
                column++;
            }
            if (pressed & BUTTON_LEFT){
                column--;
            }
        }

        if(row > RowAmounts[group])
            row = 0;
        else if(row < 0)
            row = RowAmounts[group];

        if(column > 15 || (row == 0 && column > 1))
            column = 0;
        else if(column < 0) {
            column = (row == 0 ? 1 : 15);
        }

    } while(menuOpen);

    #undef WHITE_OR_BLUE_AT
}

AmountMenu PlayerStatesMenu = {
    "Player States",
    .nbItems = 5,
    {
        {0, 1,   0, "Lock=2000, DownA=0020, ReturnA=0010,...", .method = NULL},
        {0, 1,   0, "LedgeCancel=4000, GID=0400, GJ=0800,...", .method = NULL},
        {0, 1,   0, "Invisible=2000, BlankA=0004,...", .method = NULL},
        {0, 1,   0, "Underwater=0400,...", .method = NULL},
        {0, 0, 255, "Held Item ID (simulate QuickDraw)", .method = NULL},
    }
};

void PlayerStatesMenuInit() {
    PlayerStatesMenu.items[PLAYERSTATES_PART1].amount = (PLAYER->stateFlags1 >> 0x10) & 0xFFFF;
    PlayerStatesMenu.items[PLAYERSTATES_PART2].amount = PLAYER->stateFlags1 & 0xFFFF;
    PlayerStatesMenu.items[PLAYERSTATES_PART3].amount = (PLAYER->stateFlags2 >> 0x10) & 0xFFFF;
    PlayerStatesMenu.items[PLAYERSTATES_PART4].amount = PLAYER->stateFlags2 & 0xFFFF;
    PlayerStatesMenu.items[PLAYERSTATES_HELD_ITEM].amount = PLAYER->heldItemId;
}

void Debug_PlayerStatesMenuShow() {
    if (isInGame()) {
        PlayerStatesMenuInit();
        AmountMenuShow(&PlayerStatesMenu);
        PLAYER->stateFlags1 = (PlayerStatesMenu.items[PLAYERSTATES_PART1].amount << 0x10) | PlayerStatesMenu.items[PLAYERSTATES_PART2].amount;
        PLAYER->stateFlags2 = (PlayerStatesMenu.items[PLAYERSTATES_PART3].amount << 0x10) | PlayerStatesMenu.items[PLAYERSTATES_PART4].amount;
        PLAYER->heldItemId = PlayerStatesMenu.items[PLAYERSTATES_HELD_ITEM].amount;
        Draw_Lock();
        Draw_ClearFramebuffer();
        Draw_FlushFramebuffer();
        Draw_Unlock();
    }
}

static void checkValidMemory() {
    MemInfo address_start_info = query_memory_permissions((int)memoryEditorAddress);
    MemInfo address_end_info = query_memory_permissions((int)memoryEditorAddress + 127);
    isValidMemory = is_valid_memory_read(&address_start_info) && is_valid_memory_read(&address_end_info);
}

void Debug_MemoryEditor() {

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    checkValidMemory();
    if (!isValidMemory) selectedColumn = selectedRow = 0;

    #define WHITE_OR_GREEN_AT(X,Y) ((selectedRow == X && selectedColumn == Y) ? COLOR_GREEN : COLOR_WHITE)
    #define WHITE_OR_BLUE_AT(X,Y)  ((selectedRow == X && selectedColumn == Y) ? COLOR_TITLE : COLOR_WHITE)

    do
    {
        Draw_Lock();
        // Title
        Draw_DrawString(10, 10, COLOR_TITLE, "Memory Editor");
        // Address selection
        Draw_DrawFormattedString(30, 30, selectedRow == 0 ? COLOR_GREEN : COLOR_WHITE, "%08X", memoryEditorAddress);
        // Scroll buttons
        Draw_DrawCharacter(40, 30 + SPACING_Y, WHITE_OR_BLUE_AT(1,0), 31);
        Draw_DrawCharacter(60, 30 + SPACING_Y, WHITE_OR_BLUE_AT(1,1), 30);
        // Byte index markers
        for (s32 j = 0; j < 8; j++) {
            Draw_DrawFormattedString(90 + j * SPACING_X * 3, 30 + SPACING_Y, (selectedRow > 1 && selectedColumn == j) ? COLOR_TITLE : COLOR_GRAY, "%d", j);
        }
        // Memory addresses and values
        for (s32 i = 0; i < 16; i++) {
            u32 yPos = 30 + (i + 2) * SPACING_Y;
            Draw_DrawFormattedString(30, yPos, selectedRow == (i+2) ? COLOR_TITLE : COLOR_GRAY, "%08X", memoryEditorAddress + i * 8);
            if (isValidMemory) {
                for (s32 j = 0; j < 8; j++) {
                    u8 dst;
                    memcpy(&dst, (void*)(memoryEditorAddress + i * 8 + j), sizeof(dst));
                    Draw_DrawFormattedString(90 + j * SPACING_X * 3, yPos, WHITE_OR_GREEN_AT(i+2,j), "%02X", dst);
                }
            }
            else {
                Draw_DrawString(120, 30 + 10 * SPACING_Y, COLOR_RED, "Invalid Memory");
            }
        }

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);

        if (pressed & BUTTON_B){
            break;
        }
        else if (pressed & BUTTON_A){
            if (selectedRow == 0) {
                MemoryEditor_EditAddress();
            }
            else if (selectedRow == 1) {
                u8 amount = ADDITIONAL_FLAG_BUTTON ? 0x80 : 8;
                memoryEditorAddress += (selectedColumn == 0 ? amount : -amount);
                checkValidMemory();
            }
            else {
                MemoryEditor_EditValue();
            }
        }
        else {
            if (pressed & BUTTON_UP){
                selectedRow--;
                if (selectedRow == 1) selectedColumn = 1;
            }
            if (pressed & BUTTON_DOWN){
                selectedRow++;
                if (selectedRow == 2) selectedColumn = 0;
            }
            if (pressed & BUTTON_RIGHT){
                selectedColumn++;
            }
            if (pressed & BUTTON_LEFT){
                selectedColumn--;
            }
        }

        if(selectedRow > 17 || (selectedRow > 1 && !isValidMemory))
            selectedRow = 0;
        else if(selectedRow < 0)
            selectedRow = isValidMemory ? 17 : 1;

        if(selectedColumn > 7 || selectedRow == 0 || (selectedRow == 1 && selectedColumn > 1))
            selectedColumn = 0;
        else if(selectedColumn < 0) {
            switch (selectedRow) {
                case 0: selectedColumn = 0; break;
                case 1: selectedColumn = 1; break;
                default: selectedColumn = 7; break;
            }
        }

    } while(menuOpen);
}

void MemoryEditor_EditAddress() {
    static s8 digitIndex = 0;

    do
    {
        Draw_Lock();
        Draw_DrawFormattedString(30, 30, COLOR_GREEN, "%08X", memoryEditorAddress);
        Draw_DrawFormattedString(30 + (7 - digitIndex) * SPACING_X, 30, COLOR_RED, "%X", (memoryEditorAddress >> (digitIndex*4)) & 0xF);
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);

        if (pressed & (BUTTON_B | BUTTON_A)){
            break;
        }
        else if (pressed & BUTTON_UP){
            memoryEditorAddress += (1 << digitIndex*4);
        }
        else if (pressed & BUTTON_DOWN){
            memoryEditorAddress -= (1 << digitIndex*4);
        }
        else if (pressed & BUTTON_RIGHT){
            digitIndex--;
        }
        else if (pressed & BUTTON_LEFT){
            digitIndex++;
        }

        if(digitIndex > 7)
            digitIndex = 0;
        else if(digitIndex < 0)
            digitIndex = 7;

    } while(menuOpen);

    checkValidMemory();

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();
}

void MemoryEditor_EditValue() {
    u32 posX = 90 + selectedColumn * SPACING_X * 3;
    u32 posY = 30 + selectedRow * SPACING_Y;
    void* address = (void*)(memoryEditorAddress + (selectedRow - 2) * 8 + selectedColumn);

    u8 value;
    memcpy(&value, address, sizeof(value));

    do
    {
        Draw_Lock();
        Draw_DrawFormattedString(posX, posY, COLOR_RED, "%02X", value);
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);

        if (pressed & (BUTTON_B | BUTTON_A)){
            break;
        }
        else if (pressed & BUTTON_UP){
            value++;
        }
        else if (pressed & BUTTON_DOWN){
            value--;
        }
        else if (pressed & BUTTON_RIGHT){
            value+=0x10;
        }
        else if (pressed & BUTTON_LEFT){
            value-=0x10;
        }

    } while(menuOpen);

    MemInfo address_info = query_memory_permissions((int)address);
    if (is_valid_memory_write(&address_info)) {
        memcpy(address, &value, sizeof(value));
    }
    else if (MemoryEditor_ConfirmPermissionOverride()) {
        // hack to allow writing to read-only memory, if the user chooses to do so after being asked
        int truncated_address = (((int)address) & 0xFFFFF000);
        svcControlProcessMemory(getCurrentProcessHandle(), truncated_address, truncated_address, 0x1000, MEMOP_PROT,
                                    MEMPERM_READ | MEMPERM_WRITE | MEMPERM_EXECUTE);

        memcpy(address, &value, sizeof(value));
    }
}

bool MemoryEditor_ConfirmPermissionOverride() {
    bool ret = false;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_DrawString(52, 70, COLOR_RED, "NO WRITE PERMISSION ON THIS ADDRESS!");
    Draw_DrawString(40, 90, COLOR_WHITE, "Do you want to overwrite the permission?");
    Draw_DrawString(76, 120, COLOR_WHITE, "(X) Cancel       (Y) Confirm");
    Draw_DrawString(40, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "This will give RWX perms to 0x1000 bytes");
    Draw_Unlock();

    do
    {
        u32 pressed = Input_WaitWithTimeout(1000);
        if (pressed & BUTTON_X)
            break;
        else if (pressed & BUTTON_Y) {
            ret = true;
            break;
        }
    } while(menuOpen);

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();
    return ret;
}
