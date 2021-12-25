#include "menu.h"
#include "menus/commands.h"
#include "menus/warps.h"
#include "menus/watches.h"
#include "input.h"
#include "common.h"
#include "z3D/z3D.h"
#include "draw.h"
#include "advance.h"

u32 pauseUnpause = 0; //tells main to pause/unpause
u32 frameAdvance = 0; //tells main to frame advance
bool menuOpen = 0;    //tells main to open menu

static PosRot storedPosRot[STORED_POS_COUNT];
static u8 storedPosIndex = 0;

static void Command_OpenMenu(void){
    menuOpen = 1;
}

static void Command_Break(void){
    if (isInGame()) {
        /* TODO
        if (z64_game.event_flag != -1)
            z64_game.event_flag = 0x0000;
        */

        gGlobalContext->csCtx.state = 0x03;

        /*if (gGlobalContext->msgMode != 0x00) {
            gGlobalContext->msgMode = 0x36; // doesn't work to close text boxes
            //z64_game.message_state_2 = 0x00;
            //z64_game.message_state_3 = 0x02;
        }
        if (aggressive) {
            z64_game.camera_mode = 0x0001;
            z64_game.camera_flag_1 = 0x0000;
            if (z64_link.action != 0x00)
                z64_link.action = 0x07;
        }*/

        PLAYER->stateFlags1 = 0x0;
        PLAYER->stateFlags2 = 0x0;
        alertMessage = "Break";
        alertFrames = 20;
    }
}

static void Command_Levitate(void){
    if (isInGame()) PLAYER->actor.velocity.y = 6.34375f;
}

static void Command_Fall(void){
    if (isInGame()){
        PLAYER->actor.home.pos.y = -4096.f;
    }
}

static void Command_RunFast(void){
    if (isInGame()) PLAYER->xzSpeed = 27.f;
}

static void Command_Reset(void){
    if (isInGame()) EntranceWarp(0xFFFF, gSaveContext.linkAge, -1, 0);
}

static void Command_ReloadScene(void){
    if (isInGame()) {
        if(gGlobalContext->nextEntranceIndex != -1)
            EntranceWarp(gGlobalContext->nextEntranceIndex, gGlobalContext->linkAgeOnLoad, -1, 0);
        else
            EntranceWarp(gSaveContext.entranceIndex, gGlobalContext->linkAgeOnLoad, -1, 0);
    }
}

static void Command_VoidOut(void){
    if (isInGame()) {
        gSaveContext.respawn[RESPAWN_MODE_DOWN].tempSwchFlags = gGlobalContext->actorCtx.flags.tempSwch;
        gSaveContext.respawn[RESPAWN_MODE_DOWN].tempCollectFlags = gGlobalContext->actorCtx.flags.tempCollect;
        gSaveContext.respawnFlag = 1;
        if (gGlobalContext->sceneLoadFlag == 0 || gGlobalContext->sceneLoadFlag == -20) {
            EntranceWarp(gSaveContext.respawn[RESPAWN_MODE_DOWN].entranceIndex, gGlobalContext->linkAgeOnLoad, -1, 0);
        }
    }
}

static void Command_ToggleAge(void){
    gGlobalContext->linkAgeOnLoad = 1 - gGlobalContext->linkAgeOnLoad;
    alertMessage = gGlobalContext->linkAgeOnLoad ? "Child on next load" : "Adult on next load";
    alertFrames = menuOpen ? 10 : 75;
}

// static void Command_SaveState(void);
// static void Command_LoadState(void);

static void Command_StorePos(void){
    if (isInGame()){
        storedPosRot[storedPosIndex].pos = PLAYER->actor.world.pos;
        storedPosRot[storedPosIndex].rot = PLAYER->actor.world.rot;

        alertMessage = "Stored position X";
        alertMessage[16] = storedPosIndex + 48; //ASCII digit
        alertFrames = menuOpen ? 10 : 90;
    }
}

static void Command_LoadPos(void){
    if (isInGame()){
        PLAYER->actor.home.pos = storedPosRot[storedPosIndex].pos;
        PLAYER->actor.world.pos = storedPosRot[storedPosIndex].pos;
        PLAYER->actor.world.rot = storedPosRot[storedPosIndex].rot;
        PLAYER->actor.focus.rot = storedPosRot[storedPosIndex].rot;
        PLAYER->actor.shape.rot = storedPosRot[storedPosIndex].rot;

        alertMessage = "Loaded position X";
        alertMessage[16] = storedPosIndex + 48; //ASCII digit
        alertFrames = menuOpen ? 10 : 90;
    }
}

static void AlertPosIndex(void) {
    alertMessage = "Position X";
    alertMessage[9] = storedPosIndex + 48; //ASCII digit
    alertFrames = menuOpen ? 10 : 75;
}

static void Command_PreviousPos(void) {
    storedPosIndex = (storedPosIndex+STORED_POS_COUNT-1) % STORED_POS_COUNT;
    AlertPosIndex();
}
static void Command_NextPos(void) {
    storedPosIndex = (storedPosIndex+1) % STORED_POS_COUNT;
    AlertPosIndex();
}

static void Command_PauseUnpause(void){
    pauseUnpause = 1;
    if (advance_ctx.advance_state == NORMAL) {
        pauseDisplay(); // appear when triggered from menu
    }
}

static void Command_FrameAdvance(void){
    frameAdvance = 1;
    if (advance_ctx.advance_state == NORMAL) {
        pauseDisplay(); // appear when triggered from menu
    }
}

// static void Command_RecordMacro(void);
// static void Command_PlayMacro(void);
// static void Command_CollisionView(void);
static void Command_HitboxView(void){
    gStaticContext.collisionDisplay = !gStaticContext.collisionDisplay;
}

static void Command_ToggleWatches(void){
    Watches_ToggleWatches();
}

static Command commandList[] = {
    {"Open Menu", 0, 0, { 0 }, Command_OpenMenu, COMMAND_PRESS_ONCE_TYPE, 0, 0},
    {"Levitate", 0, 0, { 0 }, Command_Levitate, COMMAND_HOLD_TYPE, 0, 0},
    {"Fall", 0, 0, { 0 }, Command_Fall, COMMAND_HOLD_TYPE, 0, 0},
    {"Run Fast", 0, 0, { 0 }, Command_RunFast, COMMAND_HOLD_TYPE, 0, 0},
    {"Reset", 0, 0, { 0 }, Command_Reset, COMMAND_PRESS_ONCE_TYPE, 0, 0},
    {"Reload Scene", 0, 0, { 0 }, Command_ReloadScene, COMMAND_PRESS_ONCE_TYPE, 0, 0},
    {"Void Out", 0, 0, { 0 }, Command_VoidOut, COMMAND_PRESS_ONCE_TYPE, 0, 0},
    {"Toggle Age", 0, 0, { 0 }, Command_ToggleAge, COMMAND_PRESS_TYPE, 0, 0},
    {"Store Position", 0, 0, { 0 }, Command_StorePos, COMMAND_HOLD_TYPE, 0, 0},
    {"Load Position", 0, 0, { 0 }, Command_LoadPos, COMMAND_HOLD_TYPE, 0, 0},
    {"Previous Position", 0, 0, { 0 }, Command_PreviousPos, COMMAND_PRESS_TYPE, 0, 0},
    {"Next Position", 0, 0, { 0 }, Command_NextPos, COMMAND_PRESS_TYPE, 0, 0},
    {"Pause/Unpause", 0, 0, { 0 }, Command_PauseUnpause, COMMAND_PRESS_TYPE, 0, 0},
    {"Frame Advance", 0, 0, { 0 }, Command_FrameAdvance, COMMAND_PRESS_TYPE, 0, 0},
    {"Toggle Hitbox View", 0, 0, { 0 }, Command_HitboxView, COMMAND_PRESS_TYPE, 0, 0},
    {"Toggle Watches", 0, 0, { 0 }, Command_ToggleWatches, COMMAND_PRESS_TYPE, 0, 0},
    {"Break Free", 0, 0, { 0 }, Command_Break, COMMAND_HOLD_TYPE, 0, 0},
};

static void Commands_ListInitDefaults(void){
    commandList[COMMAND_OPEN_MENU].comboLen = 3;
    commandList[COMMAND_OPEN_MENU].inputs[0] = BUTTON_L1;
    commandList[COMMAND_OPEN_MENU].inputs[1] = BUTTON_R1;
    commandList[COMMAND_OPEN_MENU].inputs[2] = BUTTON_SELECT;
    commandList[COMMAND_OPEN_MENU].strict = 0;

    commandList[COMMAND_LEVITATE].comboLen = 2;
    commandList[COMMAND_LEVITATE].inputs[0] = BUTTON_R1;
    commandList[COMMAND_LEVITATE].inputs[1] = BUTTON_X;
    commandList[COMMAND_LEVITATE].strict = 0;

    commandList[COMMAND_FALL].comboLen = 2;
    commandList[COMMAND_FALL].inputs[0] = BUTTON_R1;
    commandList[COMMAND_FALL].inputs[1] = BUTTON_RIGHT;
    commandList[COMMAND_FALL].strict = 0;

    commandList[COMMAND_RUN_FAST].comboLen = 2;
    commandList[COMMAND_RUN_FAST].inputs[0] = BUTTON_R1;
    commandList[COMMAND_RUN_FAST].inputs[1] = BUTTON_Y;
    commandList[COMMAND_RUN_FAST].strict = 0;

    commandList[COMMAND_VOID_OUT].comboLen = 3;
    commandList[COMMAND_VOID_OUT].inputs[0] = BUTTON_A;
    commandList[COMMAND_VOID_OUT].inputs[1] = BUTTON_X;
    commandList[COMMAND_VOID_OUT].inputs[2] = BUTTON_SELECT;
    commandList[COMMAND_VOID_OUT].strict = 0;

    commandList[COMMAND_STORE_POS].comboLen = 2;
    commandList[COMMAND_STORE_POS].inputs[0] = BUTTON_L1;
    commandList[COMMAND_STORE_POS].inputs[1] = BUTTON_LEFT;
    commandList[COMMAND_STORE_POS].strict = 0;

    commandList[COMMAND_LOAD_POS].comboLen = 2;
    commandList[COMMAND_LOAD_POS].inputs[0] = BUTTON_L1;
    commandList[COMMAND_LOAD_POS].inputs[1] = BUTTON_RIGHT;
    commandList[COMMAND_LOAD_POS].strict = 0;

    commandList[COMMAND_PREVIOUS_POS].comboLen = 1;
    commandList[COMMAND_PREVIOUS_POS].inputs[0] = BUTTON_LEFT;
    commandList[COMMAND_PREVIOUS_POS].strict = 1;

    commandList[COMMAND_NEXT_POS].comboLen = 1;
    commandList[COMMAND_NEXT_POS].inputs[0] = BUTTON_RIGHT;
    commandList[COMMAND_NEXT_POS].strict = 1;

    commandList[COMMAND_TOGGLE_PAUSE].comboLen = 1;
    commandList[COMMAND_TOGGLE_PAUSE].inputs[0] = BUTTON_DOWN;
    commandList[COMMAND_TOGGLE_PAUSE].strict = 0;

    commandList[COMMAND_FRAME_ADVANCE].comboLen = 1;
    commandList[COMMAND_FRAME_ADVANCE].inputs[0] = BUTTON_UP;
    commandList[COMMAND_FRAME_ADVANCE].strict = 0;

    // reset the other commands for when default settings are restored
    for(u32 i = 0; i < COMMAND_NUM_COMMANDS; ++i){
        if ((i > COMMAND_RUN_FAST) && i != COMMAND_VOID_OUT &&
            (i < COMMAND_STORE_POS || i > COMMAND_FRAME_ADVANCE)){
            commandList[i].comboLen = 0;
            commandList[i].strict = 0;
        }
    }
}

static u32 commandInit = 0;
void Command_UpdateCommands(u32 curInputs){ //curInputs should be all the held and pressed buttons
    if (!commandInit){
        Commands_ListInitDefaults();
        commandInit = 1;
    }

    if (commandList[COMMAND_OPEN_MENU].comboLen == 0) { // prevent getting locked out of the menu
        commandList[COMMAND_OPEN_MENU].comboLen = 3;
        commandList[COMMAND_OPEN_MENU].inputs[0] = BUTTON_L1;
        commandList[COMMAND_OPEN_MENU].inputs[1] = BUTTON_R1;
        commandList[COMMAND_OPEN_MENU].inputs[2] = BUTTON_SELECT;
        commandList[COMMAND_OPEN_MENU].strict = 0;
    }

    for (int i = 0; i < COMMAND_NUM_COMMANDS; i++){
        if (commandList[i].comboLen == 0) continue;
        if ((commandList[i].strict && curInputs == commandList[i].inputs[commandList[i].curIdx]) ||
            (!commandList[i].strict && (curInputs & commandList[i].inputs[commandList[i].curIdx]) == commandList[i].inputs[commandList[i].curIdx])){ //case where we hit the new button

            commandList[i].curIdx++;
            if(commandList[i].curIdx == commandList[i].comboLen){ //time to execute the command
                if (commandList[i].type == COMMAND_HOLD_TYPE){
                    commandList[i].method();
                    commandList[i].curIdx = commandList[i].comboLen - 1;
                }
                else if(commandList[i].type == COMMAND_PRESS_ONCE_TYPE){
                    commandList[i].method();
                    commandList[i].curIdx = 0;
                }
                else if(commandList[i].type == COMMAND_PRESS_TYPE){
                    if(commandList[i].waiting == 0){
                        commandList[i].method();
                        commandList[i].waiting = 1;
                    }
                    commandList[i].curIdx = commandList[i].comboLen - 1;
                }
            }
        }
        else if(commandList[i].curIdx > 0 && ((commandList[i].strict && curInputs == commandList[i].inputs[commandList[i].curIdx - 1]) ||
                (!commandList[i].strict && (curInputs & commandList[i].inputs[commandList[i].curIdx - 1]) == commandList[i].inputs[commandList[i].curIdx - 1]))){ //case where inputs still held

            commandList[i].waiting = 0;
        }
        else { //case where command resets
            commandList[i].curIdx = 0;
            commandList[i].waiting = 0;
        }
    }
}

void Commands_ComboToString(char* buf, u32 commandIdx){
    u32 prevInput = 0;

    for (u32 i = 0; i < commandList[commandIdx].comboLen; ++i){
        u32 newInput = commandList[commandIdx].inputs[i] & ~prevInput;
        switch(newInput){
            case(BUTTON_A):
                buf[i] = 'A';
                break;
            case(BUTTON_B):
                buf[i] = 'B';
                break;
            case(BUTTON_X):
                buf[i] = 'X';
                break;
            case(BUTTON_Y):
                buf[i] = 'Y';
                break;
            case(BUTTON_START):
                buf[i] = 'S';
                break;
            case(BUTTON_SELECT):
                buf[i] = 's';
                break;
            case(BUTTON_UP):
                buf[i] = '^';
                break;
            case(BUTTON_DOWN):
                buf[i] = 'v';
                break;
            case(BUTTON_LEFT):
                buf[i] = '<';
                break;
            case(BUTTON_RIGHT):
                buf[i] = '>';
                break;
            case(BUTTON_L1):
                buf[i] = 'L';
                break;
            case(BUTTON_R1):
                buf[i] = 'R';
                break;
        }
        prevInput = commandList[commandIdx].inputs[i];
    }
}

static void Commands_EditCommand(u32 commandIndex){
    u32 selected = 0;
    u32 editing = 0;
    u32 curColor = COLOR_WHITE;
    char comboString[COMMAND_COMBO_MAX + 1];
    u32 prevInput[COMMAND_COMBO_MAX] = {0};

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do{

        Draw_Lock();
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Edit Command: %s", commandList[commandIndex].title);

        Commands_ComboToString(comboString, commandIndex);
        Draw_DrawFormattedString(30, 30, curColor, "Combo: %c  %c  %c  %c",
            commandList[commandIndex].comboLen >= 1 ? comboString[0] : ' ',
            commandList[commandIndex].comboLen >= 2 ? comboString[1] : ' ',
            commandList[commandIndex].comboLen >= 3 ? comboString[2] : ' ',
            commandList[commandIndex].comboLen >= 4 ? comboString[3] : ' ');
        Draw_DrawCharacter(10, 30, COLOR_TITLE, selected == 0 ? '>' : ' ');

        Draw_DrawFormattedString(30, 30 + SPACING_Y, COLOR_WHITE, "Type: %s", commandList[commandIndex].strict ? "Strict " : "Relaxed");
        Draw_DrawCharacter(10, 30 + SPACING_Y, COLOR_TITLE, selected == 1 ? '>' : ' ');

        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "Use X to clear the command");

        Draw_FlushFramebuffer();
        Draw_Unlock();

        if (!editing){
            Draw_Lock();
            Draw_DrawCharacter(300, 10, COLOR_WHITE, ' ');
            Draw_FlushFramebuffer();
            Draw_Unlock();
            for(u8 i = 0; i < COMMAND_COMBO_MAX; i++) {
                prevInput[i] = 0;
            }
            u32 pressed = Input_WaitWithTimeout(1000);
            if (pressed & BUTTON_A){
                if (selected == 1){
                    commandList[commandIndex].strict = !commandList[commandIndex].strict;
                }
                else if (selected == 0){
                    editing = 1;
                    curColor = COLOR_RED;
                    commandList[commandIndex].comboLen = 0;
                }
            }
            else if (pressed & BUTTON_X){
                commandList[commandIndex].comboLen = 0;
            }
            else if (pressed & BUTTON_B){
                break;
            }
            else if (pressed & (BUTTON_DOWN | BUTTON_UP)){
                selected = (selected + 1) % 2;
            }
        }
        else {
            for (u32 secs = COMMAND_COMBO_TIMEOUT; secs > 0; --secs){
                Draw_Lock();
                Draw_DrawFormattedString(300, 10, COLOR_RED, "%u", secs);
                Draw_FlushFramebuffer();
                Draw_Unlock();

                u32 pressed = Input_WaitWithTimeout(1000);
                if (!pressed){
                    editing = (secs > 1);
                    curColor = (editing ? COLOR_RED : COLOR_WHITE);
                    continue;
                }

                u32 pressedCopy = pressed;
                u8 bitCount = 0;
                for (bitCount = 0; pressedCopy; pressedCopy >>= 1){
                    bitCount += pressedCopy & 1;
                }
                if(bitCount > 1) break;
                for(u8 i = 0; i < COMMAND_COMBO_MAX; i++) {
                    if(pressed == prevInput[i]){
                        editing = 0;
                        curColor = COLOR_WHITE;
                    }
                }
                if(!editing) break;

                prevInput[commandList[commandIndex].comboLen] = pressed;


                if(commandList[commandIndex].comboLen > 0){
                    commandList[commandIndex].inputs[commandList[commandIndex].comboLen] = pressed | commandList[commandIndex].inputs[commandList[commandIndex].comboLen - 1];
                }
                else {
                    commandList[commandIndex].inputs[0] = pressed;
                }
                commandList[commandIndex].comboLen++;

                if (commandList[commandIndex].comboLen >= COMMAND_COMBO_MAX){
                    editing = 0;
                    curColor = COLOR_WHITE;
                }
                break;
            }
        }

    } while(menuOpen);
    Draw_ClearFramebuffer();
}

void Commands_ShowCommands(void){
    s32 selected = 0, page = 0, pagePrev = 0;

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
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Commands. Press START to restore defaults");

        for (s32 i = 0; i < COMMAND_MENU_MAX_SHOW && page * COMMAND_MENU_MAX_SHOW + i < COMMAND_NUM_COMMANDS; ++i)
        {
            char comboString[COMMAND_COMBO_MAX + 1];
            s32 j = page * COMMAND_MENU_MAX_SHOW + i;
            Commands_ComboToString(comboString, j);
            Draw_DrawFormattedString(30, 30 + i * SPACING_Y, COLOR_WHITE, "%s: %c  %c  %c  %c",
                commandList[j].title,
                commandList[j].comboLen >= 1 ? comboString[0] : ' ',
                commandList[j].comboLen >= 2 ? comboString[1] : ' ',
                commandList[j].comboLen >= 3 ? comboString[2] : ' ',
                commandList[j].comboLen >= 4 ? comboString[3] : ' ');
            Draw_DrawString(200, 30 + i * SPACING_Y, COLOR_WHITE, commandList[j].strict ? "Strict " : "Relaxed");
            Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, j == selected ? '>' : ' ');
        }

        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "Use Y to execute the commands from here");

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);
        if(pressed & BUTTON_B)
            break;
        if(pressed & BUTTON_A)
        {
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();

            Commands_EditCommand(selected);

            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
        }
        else if(pressed & BUTTON_Y)
        {
            commandList[selected].method();
            drawAlert();
        }
        else if(pressed & BUTTON_DOWN)
        {
            selected++;
        }
        else if(pressed & BUTTON_UP)
        {
            selected--;
        }
        else if(pressed & BUTTON_LEFT){
            selected -= COMMAND_MENU_MAX_SHOW;
        }
        else if(pressed & BUTTON_RIGHT){
            if(selected + COMMAND_MENU_MAX_SHOW < COMMAND_NUM_COMMANDS)
                selected += COMMAND_MENU_MAX_SHOW;
            else if((COMMAND_NUM_COMMANDS - 1) / COMMAND_MENU_MAX_SHOW == page)
                selected %= COMMAND_MENU_MAX_SHOW;
            else selected = COMMAND_NUM_COMMANDS - 1;
        }
        else if(pressed & BUTTON_START)
        {
            Commands_ListInitDefaults();
        }

        if(selected < 0)
            selected = COMMAND_NUM_COMMANDS - 1;
        else if(selected >= COMMAND_NUM_COMMANDS) selected = 0;

        pagePrev = page;
        page = selected / COMMAND_MENU_MAX_SHOW;
    } while(menuOpen);
}