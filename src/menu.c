/*
*   This file is a modified part of Luma3DS
*   Copyright (C) 2016-2019 Aurora Wright, TuxSH
*   Modified 2020 Gamestabled
*   Modified 2021 HylianFreddy
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "3ds/srv.h"
#include "menu.h"
#include "draw.h"
#include "menus.h"
#include "z3D/z3D.h"
#include "utils.h"
#include "input.h"
#include "menus/commands.h"
#include <stdio.h>
#include <string.h>

static void menuDraw(Menu *menu, u32 selected)
{
    Draw_DrawString(10, 10, COLOR_TITLE, menu->title);

    for(u32 i = 0; i < 15; i++)
    {
        if(i >= menu->nbItems)
            break;
        Draw_DrawString(30, 30 + i * SPACING_Y, COLOR_WHITE, menu->items[i].title);
        Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, i == selected ? '>' : ' ');
    }

    Draw_DrawFormattedString(SCREEN_BOT_WIDTH - 10 - 4 * SPACING_X, SCREEN_BOT_HEIGHT - 20, COLOR_WHITE, "    ");
    Draw_FlushFramebuffer();
}

void menuShow()
{
    u32 selectedItem = 0;
    Menu *currentMenu = &gz3DMenu;
    u32 nbPreviousMenus = 0;
    Menu *previousMenus[0x80];
    u32 previousSelectedItems[0x80];

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    menuDraw(currentMenu, selectedItem);
    Draw_Unlock();

    do
    {
        u32 pressed = Input_WaitWithTimeout(1000);

        if(pressed & BUTTON_A)
        {
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();

            switch(currentMenu->items[selectedItem].action_type)
            {
                case METHOD:
                    if(currentMenu->items[selectedItem].method != NULL)
                        currentMenu->items[selectedItem].method();
                    break;
                case MENU:
                    previousSelectedItems[nbPreviousMenus] = selectedItem;
                    previousMenus[nbPreviousMenus++] = currentMenu;
                    currentMenu = currentMenu->items[selectedItem].menu;
                    selectedItem = 0;
                    break;
            }

            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
        }
        else if(pressed & BUTTON_B)
        {
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();

            if(nbPreviousMenus > 0)
            {
                currentMenu = previousMenus[--nbPreviousMenus];
                selectedItem = previousSelectedItems[nbPreviousMenus];
            }
            else
            {
                menuOpen = 0;
                break;
            }
        }
        else if(pressed & BUTTON_DOWN)
        {
            if(++selectedItem >= currentMenu->nbItems)
                selectedItem = 0;
        }
        else if(pressed & BUTTON_UP)
        {
            if(selectedItem-- <= 0)
                selectedItem = currentMenu->nbItems - 1;
        }

        Draw_Lock();
        menuDraw(currentMenu, selectedItem);
        Draw_Unlock();
    }
    while(menuOpen);

    if(gGlobalContext->sceneLoadFlag != 0x14) {
        svcSleepThread(1000 * 1000 * 300LL); //wait 300 milliseconds for users to buffer inputs
    }
}

void ToggleMenuShow(ToggleMenu *menu) //displays a toggle menu, analogous to rosalina cheats page
{
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
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, menu->title);

        for (s32 i = 0; i < TOGGLE_MENU_MAX_SHOW && page * TOGGLE_MENU_MAX_SHOW + i < menu->nbItems; ++i)
        {
            s32 j = page * TOGGLE_MENU_MAX_SHOW + i;
            const char* checkbox = (menu->items[j].on ? "(x) " : "( ) ");
            Draw_DrawFormattedString(30, 30 + i * SPACING_Y, COLOR_WHITE, "%s%s", checkbox, menu->items[j].title);
            Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, j == selected ? '>' : ' ');
        }

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

            if(menu->items[selected].method != NULL) {
                menu->items[selected].method(selected); //the method will handle swapping on/off
            }

            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
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
            selected -= TOGGLE_MENU_MAX_SHOW;
        }
        else if(pressed & BUTTON_RIGHT){
            if(selected + TOGGLE_MENU_MAX_SHOW < menu->nbItems)
                selected += TOGGLE_MENU_MAX_SHOW;
            else if((menu->nbItems - 1) / TOGGLE_MENU_MAX_SHOW == page)
                selected %= TOGGLE_MENU_MAX_SHOW;
            else selected = menu->nbItems - 1;
        }

        if(selected < 0)
            selected = menu->nbItems - 1;
        else if(selected >= menu->nbItems) selected = 0;

        pagePrev = page;
        page = selected / TOGGLE_MENU_MAX_SHOW;
    } while(menuOpen);
}

void AmountMenuShow(AmountMenu* menu){ //displays an amount menu TODO: seems messed up
    s32 selected = 0, page = 0, pagePrev = 0;
    u32 curColor = COLOR_GREEN;
    u32 chosen = 0;

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
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, menu->title);

        for (s32 i = 0; i < AMOUNT_MENU_MAX_SHOW && page * AMOUNT_MENU_MAX_SHOW + i < menu->nbItems; ++i)
        {
            s32 j = page * AMOUNT_MENU_MAX_SHOW + i;
            Draw_DrawString(70, 30 + i * SPACING_Y, COLOR_WHITE, menu->items[j].title);
            Draw_DrawFormattedString(10, 30 + i * SPACING_Y, j == selected ? curColor : COLOR_TITLE,
                menu->items[j].hex ? " 0x%04X" : "  %05d", menu->items[j].amount);
        }

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);
        if(pressed & BUTTON_B && !chosen)
            break;
        else if(pressed & BUTTON_A && !chosen)
        {
            curColor = COLOR_RED;
            chosen = 1;
        }
        else if(pressed & (BUTTON_A | BUTTON_B) & chosen)
        {
            if(menu->items[selected].method != NULL) {
                menu->items[selected].method(selected);
            }
            curColor = COLOR_GREEN;
            chosen = 0;
        }
        else if(pressed & BUTTON_DOWN && !chosen)
        {
            selected++;
        }
        else if(pressed & BUTTON_DOWN && chosen)
        {
            if (pressed & BUTTON_X)
                menu->items[selected].amount-= (menu->items[selected].hex ? 0x100 : 100);
            else
                menu->items[selected].amount--;
        }
        else if(pressed & BUTTON_UP && !chosen)
        {
            selected--;
        }
        else if(pressed & BUTTON_UP && chosen)
        {
            if (pressed & BUTTON_X)
                menu->items[selected].amount+= (menu->items[selected].hex ? 0x100 : 100);
            else
                menu->items[selected].amount++;
        }
        else if(pressed & BUTTON_LEFT && !chosen)
        {
            selected -= AMOUNT_MENU_MAX_SHOW;
        }
        else if(pressed & BUTTON_RIGHT && chosen)
        {
            if (pressed & BUTTON_X)
                menu->items[selected].amount+= (menu->items[selected].hex ? 0x1000 : 1000);
            else
                menu->items[selected].amount += (menu->items[selected].hex ? 0x10 : 10);
        }
        else if(pressed & BUTTON_RIGHT && !chosen)
        {
            if(selected + AMOUNT_MENU_MAX_SHOW < menu->nbItems)
                selected += AMOUNT_MENU_MAX_SHOW;
            else if((menu->nbItems - 1) / AMOUNT_MENU_MAX_SHOW == page)
                selected %= AMOUNT_MENU_MAX_SHOW;
            else selected = menu->nbItems - 1;
        }
        else if(pressed & BUTTON_LEFT && chosen)
        {
            if (pressed & BUTTON_X)
                menu->items[selected].amount-= (menu->items[selected].hex ? 0x1000 : 1000);
            else
                menu->items[selected].amount -= (menu->items[selected].hex ? 0x10 : 10);
        }

        while(chosen && (menu->items[selected].max != 0) && (menu->items[selected].amount > menu->items[selected].max)) {
            u16 overDiff = menu->items[selected].amount - menu->items[selected].max;
            u16 underDiff = 0xFFFF - menu->items[selected].amount;
            if(overDiff < underDiff) {
                menu->items[selected].amount = overDiff - 1;
            }
            else {
                menu->items[selected].amount = menu->items[selected].max - underDiff;
            }
        }

        if(selected < 0)
            selected = menu->nbItems - 1;
        else if(selected >= menu->nbItems) selected = 0;

        if(chosen && menu->items[selected].method != NULL) {
            menu->items[selected].method(selected);
        }

        pagePrev = page;
        page = selected / AMOUNT_MENU_MAX_SHOW;
    } while(menuOpen);
}

u32 KeyboardFill(char * buf, u32 len){
    const char* Upper = "1234567890QWERTYUIOPASDFGHJKL'ZXCVBNM,.+";
    const char* Lower = "1234567890qwertyuiopasdfghjkl'zxcvbnm,.+";

    const char* keys = Lower;
    s32 selected = 0;
    u32 idx = strlen(buf);

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        Draw_DrawString(10, 10, COLOR_TITLE, "Edit Watch Name");


        for(u32 i = 0; i < 10; ++i){
            Draw_DrawFormattedString(30 + (i * 2 * SPACING_X), 30, selected == i ? COLOR_GREEN : COLOR_WHITE, "%c ", keys[i]);
        }
        for(u32 i = 0; i < 10; ++i){
            u32 j = 10 + i;
            Draw_DrawFormattedString(30 + (i * 2 * SPACING_X), 30 + 2 * SPACING_Y, selected == j ? COLOR_GREEN : COLOR_WHITE, "%c ", keys[j]);
        }
        for(u32 i = 0; i < 10; ++i){
            u32 j = 20 + i;
            Draw_DrawFormattedString(30 + (i * 2 * SPACING_X), 30 + 4 * SPACING_Y, selected == j ? COLOR_GREEN : COLOR_WHITE, "%c ", keys[j]);
        }
        for(u32 i = 0; i < 10; ++i){
            u32 j = 30 + i;
            Draw_DrawFormattedString(30 + (i * 2 * SPACING_X), 30 + 6 * SPACING_Y, selected == j ? COLOR_GREEN : COLOR_WHITE, "%c ", keys[j]);
        }
        Draw_DrawString(30, 30 + 7 * SPACING_Y, COLOR_RED, buf);

        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "L/R to switch case. Start to save and return.");

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = Input_WaitWithTimeout(1000);
        if(pressed & BUTTON_B){
            idx--;
            if(idx < 0) idx = 0;
            buf[idx] = '\0';
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
        }
        else if(pressed & BUTTON_A){
            if(idx >= len) idx = len - 1;
            buf[idx] = keys[selected];
            idx++;
            buf[idx] = '\0';
        }
        else if(pressed & (BUTTON_R1 | BUTTON_L1)){
            keys = (keys == Lower) ? Upper : Lower;
        }
        else if(pressed & BUTTON_DOWN){
            selected += 10;
        }
        else if(pressed & BUTTON_UP){
            selected -= 10;
        }
        else if(pressed & BUTTON_RIGHT){
            selected++;
        }
        else if(pressed & BUTTON_LEFT){
            selected--;
        }
        else if(pressed & BUTTON_START){
            break;
        }

        if (selected >= 40) selected = 0;
        if (selected < 0) selected = 39;
    } while(menuOpen);

    return idx;
}