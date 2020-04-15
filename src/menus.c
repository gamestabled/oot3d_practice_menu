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
// #include "menus/process_list.h"
// #include "menus/process_patches.h"
// #include "menus/n3ds.h"
// #include "menus/debugger.h"
// #include "menus/miscellaneous.h"
// #include "menus/sysconfig.h"
// #include "menus/screen_filters.h"
// #include "ifile.h"

Menu gz3DMenu = {
    "Gamestabled's menu, fuck you",
    .nbItems = 2,
    {
        //TODO: make a menu
        // { "Test menu placeholder", MENU, .menu = 0x00000000 },
        { "Test mehotd placeholder", METHOD, .method = &gz3DMenu_Blank },
        { "Test method placeholder", METHOD, .method = &gz3DMenu_Blank }
    }
};

void gz3DMenu_Blank(void){
    z3d_file.rupee_count = 50;
    return;
}

// void RosalinaMenu_ShowCredits(void)
// {
//     Draw_Lock();
//     Draw_ClearFramebuffer();
//     Draw_FlushFramebuffer();
//     Draw_Unlock();

//     do
//     {
//         Draw_Lock();
//         Draw_DrawString(10, 10, COLOR_TITLE, "Rosalina -- Luma3DS credits");

//         u32 posY = Draw_DrawString(10, 30, COLOR_WHITE, "Luma3DS (c) 2016-2019 AuroraWright, TuxSH") + SPACING_Y;

//         posY = Draw_DrawString(10, posY + SPACING_Y, COLOR_WHITE, "3DSX loading code by fincs");
//         posY = Draw_DrawString(10, posY + SPACING_Y, COLOR_WHITE, "Networking code & basic GDB functionality by Stary");
//         posY = Draw_DrawString(10, posY + SPACING_Y, COLOR_WHITE, "InputRedirection by Stary (PoC by ShinyQuagsire)");

//         posY += 2 * SPACING_Y;

//         Draw_DrawString(10, posY, COLOR_WHITE,
//             (
//                 "Special thanks to:\n"
//                 "  Bond697, WinterMute, piepie62, yifanlu\n"
//                 "  Luma3DS contributors, ctrulib contributors,\n"
//                 "  other people"
//             ));

//         Draw_FlushFramebuffer();
//         Draw_Unlock();
//     }
//     while(!(waitInput() & BUTTON_B) && !terminationRequest);
// }
