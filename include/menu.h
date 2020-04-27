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

#pragma once

#include <stdbool.h>
#include "MyThread.h"
#include "utils.h"

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

#define HID_PAD           (REG32(0x10146000) ^ 0xFFF)

#define BUTTON_A          (1 << 0)
#define BUTTON_B          (1 << 1)
#define BUTTON_SELECT     (1 << 2)
#define BUTTON_START      (1 << 3)
#define BUTTON_RIGHT      (1 << 4)
#define BUTTON_LEFT       (1 << 5)
#define BUTTON_UP         (1 << 6)
#define BUTTON_DOWN       (1 << 7)
#define BUTTON_R1         (1 << 8)
#define BUTTON_L1         (1 << 9)
#define BUTTON_X          (1 << 10)
#define BUTTON_Y          (1 << 11)

#define CORE_APPLICATION  0
#define CORE_SYSTEM       1
#define CORE_DEFAULT     -2

typedef enum MenuItemAction {
    METHOD,
    MENU
} MenuItemAction;

typedef struct MenuItem {
    const char *title;

    MenuItemAction action_type;
    union {
        struct Menu *menu;
        void (*method)(void);
    };
} MenuItem;

typedef struct Menu {
    const char *title;

    u32 nbItems;
    MenuItem items[0x40];
} Menu;

typedef struct ToggleMenuItem {
    u8 on;
    const char *title;
    void (*method)(s32);
} ToggleMenuItem;

typedef struct ToggleMenu {
    const char *title;

    u32 nbItems;
    ToggleMenuItem items[0x40];
} ToggleMenu;

typedef struct AmountMenuItem {
    u16 amount; //current amount
    u16 hex;    //display in hex or decimal
    const char *title;
    void (*method)(s32);
} AmountMenuItem;

typedef struct AmountMenu {
    const char *title;

    u32 nbItems;
    AmountMenuItem items[0x40];
} AmountMenu;

#define TOGGLE_MENU_MAX_SHOW 18
#define AMOUNT_MENU_MAX_SHOW 18

u32 waitInputWithTimeout(u32 msec);
u32 waitInput(void);

MyThread *menuCreateThread(void);
void menuEnter(void);
void menuThreadMain(void);

void menuShow(Menu *root);
void ToggleMenuShow(ToggleMenu *menu);
void AmountMenuShow(AmountMenu *menu);

u32 KeyboardFill(char* buf, u32 len);