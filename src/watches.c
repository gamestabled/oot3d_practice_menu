#include "menu.h"
#include "menus/watches.h"
#include "draw.h"
#include "input.h"
#include "z3D/z3D.h"
#include <stdio.h>
#include <string.h>

Watch watches[WATCHES_MAX];

static const char* const WatchTypeNames[] = {
    "S8 ",
    "U8 ",
    "X8 ",
    "S16",
    "U16",
    "X16",
    "S32",
    "U32",
    "X32",
    "F32",
};

static void WatchesEditName(char* nameBuf){
    KeyboardFill(nameBuf, WATCHES_MAXNAME);
    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();
}

static void WatchesEditWatch(s32 selected){
    s32 selectedItem = 0;
    s32 selectedByte = 0;
    u32 chosen = 0;
    u8 bytes[4];

    bytes[0] = ((u32)watches[selected].addr >> 24) & 0xFF;
    bytes[1] = ((u32)watches[selected].addr >> 16) & 0xFF;
    bytes[2] = ((u32)watches[selected].addr >> 8) & 0xFF;
    bytes[3] = (u32)watches[selected].addr & 0xFF;

    watches[selected].posX = 5; //TODO: make these editable
    watches[selected].posY = 30 + selected * SPACING_Y;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        Draw_DrawString(10, 10, COLOR_TITLE, "Watch Edit");

        Draw_DrawFormattedString(30, 30, COLOR_WHITE, "Name: %s", watches[selected].name);
        Draw_DrawCharacter(10, 30, COLOR_TITLE, selectedItem == 0 ? '>' : ' ');

        Draw_DrawFormattedString(30, 30 + SPACING_Y, COLOR_WHITE, "Type: %s", WatchTypeNames[watches[selected].type]);
        Draw_DrawCharacter(10, 30 + SPACING_Y, COLOR_TITLE, selectedItem == 1 ? '>' : ' ');

        Draw_DrawFormattedString(30, 30 + 2 * SPACING_Y, COLOR_WHITE, "Addr: %02X %02X %02X %02X", bytes[0] & 0xFF, bytes[1] & 0xFF, bytes[2] & 0xFF, bytes[3] & 0xFF);
        if(selectedItem == 2){
            Draw_DrawFormattedString(30 + (6 * SPACING_X) + (3 * SPACING_X * selectedByte), 30 + 2 * SPACING_Y, chosen ? COLOR_RED : COLOR_GREEN, "%02X", bytes[selectedByte] & 0xFF);
        }
        Draw_DrawCharacter(10, 30 + 2 * SPACING_Y, COLOR_TITLE, selectedItem == 2 ? '>' : ' ');

        Draw_DrawFormattedString(30, 30 + 3 * SPACING_Y, COLOR_WHITE, "Draw: %s", watches[selected].display ? "ON " : "OFF");
        Draw_DrawCharacter(10, 30 + 3 * SPACING_Y, COLOR_TITLE, selectedItem == 3 ? '>' : ' ');

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);

        if(chosen){
            if (pressed & (BUTTON_B | BUTTON_A))
                chosen = 0;
            else if(pressed & BUTTON_RIGHT)
                bytes[selectedByte] -= 0x10;
            else if(pressed & BUTTON_LEFT)
                bytes[selectedByte] += 0x10;
            else if(pressed & BUTTON_UP)
                bytes[selectedByte]++;
            else if(pressed & BUTTON_DOWN)
                bytes[selectedByte]--;
        }
        else {
            if(pressed & BUTTON_B)
                break;
            else if(pressed & BUTTON_A){
                if (selectedItem == 0)
                    WatchesEditName(watches[selected].name);
                else if(selectedItem == 1)
                    watches[selected].type++;
                else if(selectedItem == 2)
                    chosen = 1;
                else if(selectedItem == 3)
                    watches[selected].display = !watches[selected].display;
            }
            else if(pressed & BUTTON_UP)
                selectedItem--;
            else if(pressed & BUTTON_DOWN)
                selectedItem++;
            else if(selectedItem == 2 && pressed & BUTTON_LEFT)
                selectedByte--;
            else if(selectedItem == 2 && pressed & BUTTON_RIGHT)
                selectedByte++;
        }

        if(selectedItem > 3) selectedItem = 0;
        if(selectedItem < 0) selectedItem = 3;
        if(selectedByte > 3) selectedByte = 0;
        if(selectedByte < 0) selectedByte = 3;
        if(watches[selected].type > F32) watches[selected].type = S8;
        if(watches[selected].type < S8) watches[selected].type = F32;

    } while(menuOpen);

    watches[selected].addr = (u8*)((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3]));
    if (watches[selected].addr == NULL){
        watches[selected].display = 0;
    }
}

static void WatchesDeleteWatch(u32 selected){
    watches[selected].type = S8;
    watches[selected].posX = 0;
    watches[selected].posY = 0;
    watches[selected].addr = NULL;
    watches[selected].display = 0;
    memset(watches[selected].name, 0, WATCHES_MAXNAME + 1);
}

void Watches_ToggleWatches(void){
    u8 display = watches[0].display;

    for (u32 i = 0; i < WATCHES_MAX; ++i){
        if (watches[i].addr != NULL){
            watches[i].display = !display;
        }
    }
}

void WatchesMenuFunc(void){

    s32 selected = 0;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        Draw_DrawString(10, 10, COLOR_TITLE, "Watches");

        for (u32 i = 0; i < WATCHES_MAX; ++i){
            Draw_DrawString(30, 30 + i * SPACING_Y, COLOR_WHITE, watches[i].addr == NULL ? "." : watches[i].name);
            Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, selected == i ? '>' : ' ');
        }

        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "A to edit. X to delete.");
        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);
        if(pressed & BUTTON_B)
            break;
        else if(pressed & BUTTON_A){
            WatchesEditWatch(selected);
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
        }
        else if(pressed & BUTTON_X){
            WatchesDeleteWatch(selected);
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
        }
        else if(pressed & BUTTON_UP){
            selected--;
        }
        else if(pressed & BUTTON_DOWN){
            selected++;
        }

        if(selected >= WATCHES_MAX) selected = 0;
        if(selected < 0) selected = WATCHES_MAX - 1;

    } while(menuOpen);
}
