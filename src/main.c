/*
 * This file is a distant descendent of a file originally written by n3rdswithgame
 */

#include "menu.h"
#include "advance.h"
#include "draw.h"
#include "input.h"
#include "common.h"
#include "menus/cheats.h"
#include "menus/watches.h"
#include "menus/commands.h"
#include <string.h>

#include "z3D/z3D.h"

advance_ctx_t advance_ctx = {};
uint8_t framebuffers_init = 0;
static bool isAsleep = false;
u32 alertFrames = 0;
char* alertMessage;

GlobalContext* gGlobalContext;

static void toggle_advance(void) {
    if(pauseUnpause && advance_ctx.advance_state == NORMAL && !advance_ctx.latched){
        advance_ctx.advance_state = PAUSED;
        advance_ctx.latched = 1;
    } else if(pauseUnpause && advance_ctx.advance_state != NORMAL && !advance_ctx.latched) {
        advance_ctx.advance_state = NORMAL;
        advance_ctx.latched = 1;
    } else if (frameAdvance && advance_ctx.advance_state == NORMAL){
        advance_ctx.advance_state = LATCHED;
    } else if(!pauseUnpause) {
        advance_ctx.latched = 0;
    }
}

static void drawWatches(void) {
    for(u32 i = 0; i < WATCHES_MAX; ++i) {
        if (!watches[i].display) {
            continue;
        }

        // Skip attempting to draw the address if it would otherwise be an invalid read.
        // Attempting to read these locations would crash the game.
        const MemInfo address_info = query_memory_permissions((int)watches[i].addr);
        if (!is_valid_memory_read(&address_info)) {
            Draw_DrawFormattedString(70, 40 + i * SPACING_Y, COLOR_WHITE, "%s: Invalid address", watches[i].name);
            continue;
        }


        switch(watches[i].type) {
            case(S8): {
                s8 dst;
                memcpy(&dst, watches[i].addr, sizeof(dst));
                Draw_DrawFormattedString(70, 40 + i * SPACING_Y, COLOR_WHITE, "%s: %03d", watches[i].name, dst);
                break;
            }
            case(U8): {
                u8 dst;
                memcpy(&dst, watches[i].addr, sizeof(dst));
                Draw_DrawFormattedString(70, 40 + i * SPACING_Y, COLOR_WHITE, "%s: %03u", watches[i].name, dst);
                break;
            }
            case(X8): {
                u8 dst;
                memcpy(&dst, watches[i].addr, sizeof(dst));
                Draw_DrawFormattedString(70, 40 + i * SPACING_Y, COLOR_WHITE, "%s: %02X", watches[i].name, dst);
                break;
            }
            case(S16): {
                s16 dst;
                memcpy(&dst, watches[i].addr, sizeof(dst));
                Draw_DrawFormattedString(70, 40 + i * SPACING_Y, COLOR_WHITE, "%s: %05d", watches[i].name, dst);
                break;
            }
            case(U16): {
                u16 dst;
                memcpy(&dst, watches[i].addr, sizeof(dst));
                Draw_DrawFormattedString(70, 40 + i * SPACING_Y, COLOR_WHITE, "%s: %05u", watches[i].name, dst);
                break;
            }
            case(X16): {
                u16 dst;
                memcpy(&dst, watches[i].addr, sizeof(dst));
                Draw_DrawFormattedString(70, 40 + i * SPACING_Y, COLOR_WHITE, "%s: %04X", watches[i].name, dst);
                break;
            }
            case(S32): {
                s32 dst;
                memcpy(&dst, watches[i].addr, sizeof(dst));
                Draw_DrawFormattedString(70, 40 + i * SPACING_Y, COLOR_WHITE, "%s: %010d", watches[i].name, dst);
                break;
            }
            case(U32): {
                u32 dst;
                memcpy(&dst, watches[i].addr, sizeof(dst));
                Draw_DrawFormattedString(70, 40 + i * SPACING_Y, COLOR_WHITE, "%s: %010u", watches[i].name, dst);
                break;
            }
            case(X32): {
                u32 dst;
                memcpy(&dst, watches[i].addr, sizeof(dst));
                Draw_DrawFormattedString(70, 40 + i * SPACING_Y, COLOR_WHITE, "%s: %08X", watches[i].name, dst);
                break;
            }
            case(F32): {
                float dst;
                memcpy(&dst, watches[i].addr, sizeof(dst));
                Draw_DrawFormattedString(70, 40 + i * SPACING_Y, COLOR_WHITE, "%s: %05.2F", watches[i].name, dst);
                break;
            }
        }
    }
    Draw_FlushFramebuffer();
}

void drawAlert() {
    if (alertFrames > 0) {
        Draw_DrawFormattedStringTop(280, 220, COLOR_WHITE, alertMessage);
        Draw_FlushFramebufferTop();
        alertFrames--;
    }
}

static void titleScreenDisplay(void){
    Draw_DrawFormattedStringTop(150, 20, COLOR_WHITE, "OoT3D Practice Patch");
    Draw_FlushFramebufferTop();

    char menuComboString[COMMAND_COMBO_MAX + 1] = {0};
    Commands_ComboToString(menuComboString, 0);
    Draw_DrawFormattedString(150, 0, COLOR_WHITE, menuComboString);
    Draw_FlushFramebuffer();
}

static void pauseDisplay(void) {
    Draw_DrawFormattedStringTop(20, 20, COLOR_WHITE, "Paused");
    Draw_FlushFramebufferTop();
}

void advance_main(void) {
    if(framebuffers_init == 0){
        Draw_SetupFramebuffer();
        framebuffers_init = 1;
    }

    if(gSaveContext.entranceIndex == 0x0629 && gSaveContext.cutsceneIndex == 0xFFF3 && gSaveContext.gameMode != 2){
        titleScreenDisplay();
    }

    drawWatches();
    drawAlert();
    Input_Update();
    Command_UpdateCommands(rInputCtx.cur.val);

    if(menuOpen) {
        menuShow();
    }
    applyCheats();

    toggle_advance();

    if(advance_ctx.advance_state == STEP) {
        if(frameAdvance) {
            advance_ctx.advance_state = LATCHED;
        } else {
            advance_ctx.advance_state = PAUSED;
        }
    }
    pauseUnpause = 0;
    frameAdvance = 0;

    while(!isAsleep &&(advance_ctx.advance_state == PAUSED || advance_ctx.advance_state == LATCHED)) {
        pauseDisplay();
        drawAlert();
        Input_Update();
        Command_UpdateCommands(rInputCtx.cur.val);
        if(menuOpen) {
            menuShow();
        }
        applyCheats();
        toggle_advance();
        if(advance_ctx.advance_state == LATCHED && !frameAdvance) {
            advance_ctx.advance_state = PAUSED;
        }
        if(advance_ctx.advance_state == PAUSED && frameAdvance) {
            advance_ctx.advance_state = STEP;
        }
        pauseUnpause = 0;
        frameAdvance = 0;
        svcSleepThread(16E6);
    }
    isAsleep = false;
}

void setGlobalContext(GlobalContext* globalContext){
    gGlobalContext = globalContext;
}

void Gfx_SleepQueryCallback(void) {
    menuOpen = false;
    isAsleep = true;
}

void area_load_main(void){}
int main(void){}