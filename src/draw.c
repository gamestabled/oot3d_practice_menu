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

#include "fmt.h"
#include "draw.h"
#include "font.h"
#include "utils.h"
#include "3ds/svc.h"
#include "3ds/synchronization.h"
#include <string.h>

u8 FRAMEBUFFER[FB_BOTTOM_SIZE] __attribute__ ((aligned (0x80)));
static RecursiveLock lock;

void Draw_Lock(void)
{
    static bool lockInitialized = false;
    if(!lockInitialized)
    {
        RecursiveLock_Init(&lock);
        lockInitialized = true;
    }

    RecursiveLock_Lock(&lock);
}

void Draw_Unlock(void)
{
    RecursiveLock_Unlock(&lock);
}

void Draw_DrawCharacter(u32 posX, u32 posY, u32 color, char character)
{
    volatile u16 *const fb = (volatile u16 *const)FRAMEBUFFER;


    s32 y;
    for(y = 0; y < 10; y++)
    {
        char charPos = font[character * 10 + y];

        s32 x;
        for(x = 6; x >= 1; x--)
        {
            u32 screenPos = (posX * SCREEN_BOT_HEIGHT * 2 + (SCREEN_BOT_HEIGHT - y - posY - 1) * 2) + (5 - x) * 2 * SCREEN_BOT_HEIGHT;
            u32 pixelColor = ((charPos >> x) & 1) ? color : COLOR_BLACK;
            fb[screenPos / 2] = pixelColor;
        }
    }
}


u32 Draw_DrawString(u32 posX, u32 posY, u32 color, const char *string)
{
    for(u32 i = 0, line_i = 0; i < strlen(string); i++)
        switch(string[i])
        {
            case '\n':
                posY += SPACING_Y;
                line_i = 0;
                break;

            case '\t':
                line_i += 2;
                break;

            default:
                //Make sure we never get out of the screen
                if(line_i >= ((SCREEN_BOT_WIDTH) - posX) / SPACING_X)
                {
                    posY += SPACING_Y;
                    line_i = 1; //Little offset so we know the same string continues
                    if(string[i] == ' ') break; //Spaces at the start look weird
                }

                Draw_DrawCharacter(posX + line_i * SPACING_X, posY, color, string[i]);

                line_i++;
                break;
        }

    return posY;
}

u32 Draw_DrawFormattedString(u32 posX, u32 posY, u32 color, const char *fmt, ...)
{
    char buf[DRAW_MAX_FORMATTED_STRING_SIZE + 1];
    va_list args;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);

    return Draw_DrawString(posX, posY, color, buf);
}

void Draw_FillFramebuffer(u32 value)
{
    memset(FRAMEBUFFER, value, FB_BOTTOM_SIZE);
}

void Draw_ClearFramebuffer(void)
{
    Draw_FillFramebuffer(0xFF);
}

void Draw_SetupFramebuffer(void)
{
    u16 format = GSP_RGB565_OES; // https://www.3dbrew.org/wiki/GPU/External_Registers#Framebuffer_format 

    gspInit(); //todo, figure out what to do with this
    
    memset(FRAMEBUFFER, 0, FB_BOTTOM_SIZE); //probably not necessary

    GSPGPU_FramebufferInfo gsp_info = {
        0, FRAMEBUFFER, NULL, SCREEN_BOT_HEIGHT * 2, format, 0, 0
    };

    if (R_FAILED(GSPGPU_SetBufferSwap(1, &gsp_info)))
        svcBreak(USERBREAK_PANIC);
    // GSPGPU_SetBufferSwap(1, &gsp_info);
}

void Draw_FlushFramebuffer(void)
{
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER, FB_BOTTOM_SIZE);
}
