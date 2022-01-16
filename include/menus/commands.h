#pragma once

#include "menu.h"
#include "z3D/z3D.h"

#define COMMAND_COMBO_MAX 4
#define COMMAND_COMBO_TIMEOUT 3
#define COMMAND_MENU_MAX_SHOW 17
#define STORED_POS_COUNT 9

typedef enum {
    COMMAND_HOLD_TYPE, //command works as long as combo is held
    COMMAND_PRESS_TYPE, //command can be repeated with only the final input
    COMMAND_PRESS_ONCE_TYPE, //command is only repeated after redoing full combo
} commandType;

typedef enum {
    COMMAND_OPEN_MENU,
    COMMAND_LEVITATE,
    COMMAND_FALL,
    COMMAND_RUN_FAST,
    COMMAND_RESET,
    COMMAND_RELOAD_SCENE,
    COMMAND_VOID_OUT,
    COMMAND_TOGGLE_AGE,
    COMMAND_STORE_POS,
    COMMAND_LOAD_POS,
    COMMAND_PREVIOUS_POS,
    COMMAND_NEXT_POS,
    COMMAND_TOGGLE_PAUSE,
    COMMAND_FRAME_ADVANCE,
    COMMAND_HITBOX_VIEW,
    COMMAND_TOGGLE_WATCHES,
    COMMAND_BREAK,
    COMMAND_NOCLIP,
    NUMBER_OF_COMMANDS,
} commandNames;

typedef enum {
    COMMAND_EDIT_COMBO,
    COMMAND_EDIT_STRICT,
} commandOptionsNames;

typedef struct Command {
    const char* title;

    u32 comboLen;
    u32 curIdx;
    u32 inputs[COMMAND_COMBO_MAX];
    void(*method)(void);
    commandType type;
    u32 waiting; //to prevent press types from re-executing. unused for other types
    u32 strict; //whether the button combo is strict or not
} Command;

extern Command commandList[NUMBER_OF_COMMANDS];

void Commands_ShowCommandsMenu(void);
void Command_UpdateCommands(u32 inputs);
void Commands_ComboToString(char* buf, u32 commandIdx);

extern u32 pauseUnpause;
extern u32 frameAdvance;
extern PosRot storedPosRot[STORED_POS_COUNT];
extern u32 commandInit;
