/*
 * This file is a distant descendent of a file originally written by n3rdswithgame
 */

#include "menu.h"
#include "MyThread.h"
#include "advance.h"
#include "draw.h"
#include "menus/watches.h"
#include <string.h>

#include "z3D/z3D.h"

advance_ctx_t advance_ctx = {};
advance_input_t inputs = {};
uint8_t advance_init;

GlobalContext* gGlobalContext;

static void scan_inputs() {
    inputs.cur.val = real_hid.pad.pads[real_hid.pad.index].curr.val;
    inputs.pressed.val = (inputs.cur.val) & (~inputs.old.val);
    inputs.up.val = (~inputs.cur.val) & (inputs.old.val);
    inputs.old.val = inputs.cur.val;
}

static void toggle_advance() {
    //scan_inputs();
    if(inputs.pressed.d_up && advance_ctx.advance_state == NORMAL && !advance_ctx.d_down_latched){
        advance_ctx.advance_state = PAUSED;
        advance_ctx.d_down_latched = 1;
    } else if(inputs.pressed.d_up && advance_ctx.advance_state != NORMAL && !advance_ctx.d_down_latched) {
        advance_ctx.advance_state = NORMAL;
        advance_ctx.d_down_latched = 1;
    } else if (advance_ctx.advance_state == NORMAL && inputs.pressed.d_down){
        advance_ctx.advance_state = LATCHED;
    } else if(!inputs.pressed.d_up) {
        advance_ctx.d_down_latched = 0;
    }
}

static void drawWatches(void) {
    for(u32 i = 0; i < WATCHES_MAX; ++i) {
        if (watches[i].display){
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
    }
    Draw_FlushFramebuffer();
}

void advance_main() {

    scan_inputs();

    if(inputs.cur.l && inputs.cur.r && inputs.cur.sel) {
        MyThread* menuThread = menuCreateThread();
        MyThread_Join(menuThread, -1LL);
    }

    drawWatches();

    /*Frame Advance begins here
    Stolen from n3rdswithgame <3
    ---------------------------*/
    if(advance_init == 0) {
        advance_init = 1;
    }

    //up to enable, left to advance
    toggle_advance();
    scan_inputs();


    if(advance_ctx.advance_state == STEP) {
        if(inputs.cur.d_down) {
            advance_ctx.advance_state = LATCHED;
        } else {
            advance_ctx.advance_state = PAUSED;
        }
    }


    while(advance_ctx.advance_state == PAUSED || advance_ctx.advance_state == LATCHED) {
        scan_inputs();
        toggle_advance();
        if(advance_ctx.advance_state == LATCHED && !inputs.cur.d_down) {
            advance_ctx.advance_state = PAUSED;
        }
        if(advance_ctx.advance_state == PAUSED && inputs.cur.d_down) {
            advance_ctx.advance_state = STEP;
        }
        svcSleepThread(16e6);
    }

}

void setGlobalContext(GlobalContext* globalContext){
    gGlobalContext = globalContext;
}

void area_load_main(){}

int main(void){}