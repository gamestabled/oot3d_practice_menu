/*
*   This file is a modified part of Luma3DS
*   Copyright (C) 2016-2019 Aurora Wright, TuxSH
*   Modified 2020 Gamestabled
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
#include "utils.h"
#include <stdio.h>

u32 waitInputWithTimeout(u32 msec)
{
    bool pressedKey = false;
    u32 key = 0;
    u32 n = 0;

    //Wait for no keys to be pressed
    while(HID_PAD && (msec == 0 || n < msec))
    {
        svcSleepThread(1 * 1000 * 1000LL);
        n++;
    }

    if(msec != 0 && n >= msec)
        return 0;

    do
    {
        //Wait for a key to be pressed
        while(!HID_PAD && (msec == 0 || n < msec))
        {
            svcSleepThread(1 * 1000 * 1000LL);
            n++;
        }

        if(msec != 0 && n >= msec)
            return 0;

        key = HID_PAD;

        //Make sure it's pressed
        for(u32 i = 0x26000; i > 0; i --)
        {
            if(key != HID_PAD) break;
            if(i == 1) pressedKey = true;
        }
    }
    while(!pressedKey);

    return key;
}

u32 waitInput(void)
{
    return waitInputWithTimeout(0);
}

static MyThread menuThread;
static u8 ALIGN(8) menuThreadStack[0x3000];

MyThread *menuCreateThread(void)
{
    if(R_FAILED(MyThread_Create(&menuThread, menuThreadMain, menuThreadStack, 0x3000, 52, CORE_DEFAULT)))
        svcBreak(USERBREAK_PANIC);
    return &menuThread;
}

void menuThreadMain(void)
{
    menuEnter();
    menuShow(&gz3DMenu);
}

void menuEnter(void)
{
    Draw_SetupFramebuffer();
    Draw_ClearFramebuffer();
}

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

void menuShow(Menu *root)
{
    u32 selectedItem = 0;
    Menu *currentMenu = root;
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
        u32 pressed = waitInputWithTimeout(1000);

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
    while(true);
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
            char buf[65] = { 0 };
            s32 j = page * TOGGLE_MENU_MAX_SHOW + i;
            const char* checkbox = (menu->items[j].on ? "(x) " : "( ) ");
            sprintf(buf, "%s%s", checkbox, menu->items[j].title);

            Draw_DrawString(30, 30 + i * SPACING_Y, COLOR_WHITE, buf);
            Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, j == selected ? '>' : ' ');
        }

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = waitInputWithTimeout(1000);
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
    } while(true);
}

void AmountMenuShow(AmountMenu* menu){ //displays an amount menu
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
            char buf[65] = { 0 };
            s32 j = page * AMOUNT_MENU_MAX_SHOW + i;
            if (menu->items[j].hex)
            {
                sprintf(buf, "0x%03x", menu->items[j].amount);
            }
            else 
            {
                sprintf(buf, "  %03d", menu->items[j].amount);
            }
            Draw_DrawString(70, 30 + i * SPACING_Y, COLOR_WHITE, menu->items[j].title);
            Draw_DrawString(10, 30 + i * SPACING_Y, j == selected ? curColor : COLOR_TITLE, buf);
        }

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = waitInputWithTimeout(1000);
        if(pressed & BUTTON_B && !chosen)
            break;
        else if(pressed & BUTTON_B && chosen)
        {
            curColor = COLOR_GREEN;
            chosen = 0;
        }
        else if(pressed & BUTTON_A && !chosen)
        {
            curColor = COLOR_RED;
            chosen = 1;
        }
        else if(pressed & BUTTON_A && chosen)
        {
            if(menu->items[selected].method != NULL) {
                menu->items[selected].method(selected); //the method will handle changing amount
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
            menu->items[selected].amount--;
        }
        else if(pressed & BUTTON_UP && !chosen)
        {
            selected--;
        }
        else if(pressed & BUTTON_UP && chosen)
        {
            menu->items[selected].amount++;
        }
        else if(pressed & BUTTON_LEFT && !chosen)
        {
            selected -= AMOUNT_MENU_MAX_SHOW;
        }
        else if(pressed & BUTTON_LEFT && chosen)
        {
            menu->items[selected].amount -= (menu->items[selected].hex ? 16 : 10);
        }
        else if(pressed & BUTTON_RIGHT && !chosen)
        {
            if(selected + AMOUNT_MENU_MAX_SHOW < menu->nbItems)
                selected += AMOUNT_MENU_MAX_SHOW;
            else if((menu->nbItems - 1) / AMOUNT_MENU_MAX_SHOW == page)
                selected %= AMOUNT_MENU_MAX_SHOW;
            else selected = menu->nbItems - 1;
        }
        else if(pressed & BUTTON_RIGHT && chosen)
        {
            menu->items[selected].amount += (menu->items[selected].hex ? 16 : 10);
        }
        if(selected < 0)
            selected = menu->nbItems - 1;
        else if(selected >= menu->nbItems) selected = 0;

        pagePrev = page;
        page = selected / AMOUNT_MENU_MAX_SHOW;
    } while(true);
}