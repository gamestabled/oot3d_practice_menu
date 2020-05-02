#include "menu.h"
#include "menus/equips.h"
#include "draw.h"
#include "z3D/z3D.h"

static const char* const EquipButtonNames[] = {
    "B Button",
    "Y Button",
    "X Button",
    "I Button",
    "II Button",
};

static void Equips_ModifyButton(u32 button){

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();

        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Select item for the %s:", EquipButtonNames[button]);
        Draw_DrawFormattedString(30, 30, COLOR_WHITE, "%03u", gSaveContext.equips.buttonItems[button] & 0xFF);

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = waitInputWithTimeout(1000);
        if(pressed & (BUTTON_B | BUTTON_A)){
            break;
        }
        else if(pressed & BUTTON_UP){
            gSaveContext.equips.buttonItems[button]++;
        }
        else if(pressed & BUTTON_DOWN){
            gSaveContext.equips.buttonItems[button]--;
        }
        else if(pressed & BUTTON_LEFT){
            gSaveContext.equips.buttonItems[button] += 10;
        }
        else if(pressed & BUTTON_RIGHT){
            gSaveContext.equips.buttonItems[button] -= 10;
        }

    } while (true);
}

static void Equips_ModifyBButton(void){
    Equips_ModifyButton(EQUIP_BUTTON_B);
}

static void Equips_ModifyYButton(void){
    Equips_ModifyButton(EQUIP_BUTTON_Y);
}

static void Equips_ModifyXButton(void){
    Equips_ModifyButton(EQUIP_BUTTON_X);
}

static void Equips_ModifyIButton(void){
    Equips_ModifyButton(EQUIP_BUTTON_I);
}

static void Equips_ModifyIIButton(void){
    Equips_ModifyButton(EQUIP_BUTTON_II);
}

Menu EquipsMenu = {
    "Equips",
    .nbItems = 5,
    {
        {"B button", METHOD, .method = Equips_ModifyBButton},
        {"Y button", METHOD, .method = Equips_ModifyYButton},
        {"X button", METHOD, .method = Equips_ModifyXButton},
        {"I button", METHOD, .method = Equips_ModifyIButton},
        {"II button", METHOD, .method = Equips_ModifyIIButton},
    }
};
