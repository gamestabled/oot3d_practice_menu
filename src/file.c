#include "menu.h"
#include "menus/file.h"
#include "z3D/z3D.h"

ToggleMenu FileMenu = {
    "File",
    .nbItems = 7,
    {
        {0, "Gold Skulltulas defeated", .method = File_ToggleSkulltulaFlags },
        {0, "Call Navi", .method = File_CallNavi },
        {0, "Epona Freed", .method = File_ToggleEponaFreed },
        {0, "Carpenters Freed", .method = File_ToggleCarpentersFreed },
        {0, "Intro Cutscenes", .method = File_ToggleIntroCutscenes },
        {0, "Blue Warps Cleared", .method = File_ToggleBlueWarps },
        {0, "Master Quest", .method = File_ToggleMasterQuest },
    }
};


void File_FileMenuInit(void) {
    FileMenu.items[FILE_GOLD_SKULLTULAS].on = (gSaveContext.gsFlags[0] == 0xFF);
    FileMenu.items[FILE_CALL_NAVI].on = (gSaveContext.naviTimer >= 2000);
    FileMenu.items[FILE_EPONA_FREED].on = (gSaveContext.eventChkInf[0x1] & 0x0100) == 0x0100;
    FileMenu.items[FILE_CARPENTERS_FREED].on = ((gSaveContext.eventChkInf[0x9] & 0x000F) == 0x000F);
    FileMenu.items[FILE_INTRO_CUTSCENES].on = ((gSaveContext.eventChkInf[0xA] & 0x01FB) +
                                              (gSaveContext.eventChkInf[0xB] & 0x07FE) +
                                              (gSaveContext.eventChkInf[0xC] & 0x8081) == 0x01FB + 0x07FE + 0x8081);
    FileMenu.items[FILE_BLUE_WARPS_CLEARED].on = ((gSaveContext.eventChkInf[0x0] & 0x0080) +
                                                 (gSaveContext.eventChkInf[0x2] & 0x0020) +
                                                 (gSaveContext.eventChkInf[0x3] & 0x0080) +
                                                 (gSaveContext.eventChkInf[0x4] & 0x0700) == 0x0080 + 0x0020 + 0x0080 + 0x0700);
    FileMenu.items[FILE_MASTER_QUEST].on = gSaveContext.masterQuestFlag;
}

void File_ShowFileMenu() {
    File_FileMenuInit();
    ToggleMenuShow(&FileMenu);
}

void File_ToggleSkulltulaFlags(s32 selected) {
    if (FileMenu.items[selected].on) {
        for (u32 i = 0; i < 22; i++) {
            gSaveContext.gsFlags[i] = 0;
        }
        FileMenu.items[selected].on = 0;
    }
    else {
        for (u32 i = 0; i < 22; i++) {
            gSaveContext.gsFlags[i] = 0xFF;
        }
        FileMenu.items[selected].on = 1;
    }
}

void File_CallNavi(s32 selected) {
    if (FileMenu.items[selected].on) {
        gSaveContext.naviTimer = 0;
        FileMenu.items[selected].on = 0;
    }
    else {
        gSaveContext.naviTimer = 2000;
        FileMenu.items[selected].on = 1;
    }
}

void File_ToggleEponaFreed(s32 selected) {
    if (FileMenu.items[selected].on) {
        gSaveContext.eventChkInf[0x1] &= ~0x0100;
        FileMenu.items[selected].on = 0;
    }
    else {
        gSaveContext.eventChkInf[0x1] |= 0x0100;
        FileMenu.items[selected].on = 1;
    }
}

void File_ToggleCarpentersFreed(s32 selected) {
    if (FileMenu.items[selected].on) {
        gSaveContext.eventChkInf[0x9] &= ~0x000F;
        FileMenu.items[selected].on = 0;
    }
    else {
        gSaveContext.eventChkInf[0x9] |= 0x000F;
        FileMenu.items[selected].on = 1;
    }
}

void File_ToggleIntroCutscenes(s32 selected) {
    if (FileMenu.items[selected].on) {
        gSaveContext.eventChkInf[0xA] &= ~0x01FB;
        gSaveContext.eventChkInf[0xB] &= ~0x07FE;
        gSaveContext.eventChkInf[0xC] &= ~0x8081;
        FileMenu.items[selected].on = 0;
    }
    else {
        gSaveContext.eventChkInf[0xA] |= 0x01FB;
        gSaveContext.eventChkInf[0xB] |= 0x07FE;
        gSaveContext.eventChkInf[0xC] |= 0x8081;
        FileMenu.items[selected].on = 1;
    }
}

void File_ToggleBlueWarps(s32 selected) {
    if (FileMenu.items[selected].on) {
        gSaveContext.eventChkInf[0x0] &= ~0x0080;
        gSaveContext.eventChkInf[0x2] &= ~0x0020;
        gSaveContext.eventChkInf[0x3] &= ~0x0080;
        gSaveContext.eventChkInf[0x4] &= ~0x0700;
        FileMenu.items[selected].on = 0;
    }
    else {
        gSaveContext.eventChkInf[0x0] |= 0x0080;
        gSaveContext.eventChkInf[0x2] |= 0x0020;
        gSaveContext.eventChkInf[0x3] |= 0x0080;
        gSaveContext.eventChkInf[0x4] |= 0x0700;
        FileMenu.items[selected].on = 1;
    }
}

void File_ToggleMasterQuest(s32 selected) {
    if (FileMenu.items[selected].on) {
        gSaveContext.masterQuestFlag = 0;
        FileMenu.items[selected].on = 0;
    }
    else {
        gSaveContext.masterQuestFlag = 1;
        FileMenu.items[selected].on = 1;
    }
}
