#pragma once

#include "menu.h"

#define COMMAND_COMBO_MAX 4
#define COMMAND_COMBO_TIMEOUT 3
#define COMMAND_MENU_MAX_SHOW 18
#define COMMAND_NUM_COMMANDS 14

typedef enum {
    COMMAND_HOLD_TYPE, //command works as long as combo is held
    COMMAND_PRESS_TYPE, //command can be repeated with only the final input
    COMMAND_PRESS_ONCE_TYPE, //command is only repeated after redoing full combo
} commandType;

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

void Commands_ShowCommands(void);
void Command_UpdateCommands(u32 inputs);
void Commands_ComboToString(char* buf, u32 commandIdx);

extern u32 pauseUnpause;
extern u32 frameAdvance;
