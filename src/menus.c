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

#include "3ds/os.h"
#include "menus.h"
#include "menu.h"
#include "draw.h"
#include "z3d.h"

#include "menus/warps.h"
#include "menus/scene.h"
#include "menus/cheats.h"
#include "menus/inventory.h"
#include "menus/equips.h"
#include "menus/file.h"

Menu gz3DMenu = {
    "Gamestabled's menu, fuck you",
    .nbItems = 7,
    {
        { "Test method placeholder, sets rupees to 50", METHOD, .method = &gz3DMenu_Test },
        { "Warps", MENU, .menu = &WarpsMenu },
        { "Scene", MENU, .menu = &SceneMenu },
        { "Cheats", MENU, .menu = &CheatsMenu },
        { "Inventory", MENU, .menu = &InventoryMenu },
        { "Equips", MENU, .menu = &EquipsMenu },
        { "File", MENU, .menu = &FileMenu },
    }
};

void gz3DMenu_Test(void){
    gSaveContext.rupee_count = 50;
    return;
}
