#include "menu.h"
#include "input.h"
#include "common.h"
#include "menus/cheats.h"
#include "z3D/z3D.h"

#define SEQ_AUDIO_BLANK 0x1000142

u8 cheats[0x12] = {0};
u8 forcedUsableItems = 0;
u16 frozenTime = 0;

/*void Cheats_CheatsMenuInit() {
    for (int i = 0; i < 12; i++) {
        CheatsMenu.items[i].on = cheats[i];
    }
};*/

void Cheats_ShowCheatsMenu(){
    //Cheats_CheatsMenuInit();
    ToggleMenuShow(&CheatsMenu);
}

void Cheats_Toggle(s32 selected){
    cheats[selected] = !cheats[selected];
    CheatsMenu.items[selected].on = !CheatsMenu.items[selected].on;

    switch (selected) {
        case (CHEATS_USABLE_ITEMS):
            if (ADDITIONAL_FLAG_BUTTON) {
                forcedUsableItems = 1;
                CheatsMenu.items[CHEATS_USABLE_ITEMS].title = "Unrestricted Items - Forced mode ON";
            } else {
                forcedUsableItems = 0;
                CheatsMenu.items[CHEATS_USABLE_ITEMS].title = "Unrestricted Items - Forced mode OFF";
            }
            break;
        case (CHEATS_FREEZE_TIME):
            frozenTime = gSaveContext.dayTime;
            break;
        case (CHEATS_NAYRUS_LOVE):
            if (!CheatsMenu.items[selected].on)
                gSaveContext.nayrusLoveTimer = 0x6E0;
            break;
    }

    applyCheats();
}

ToggleMenu CheatsMenu = {
    "Cheats",
    .nbItems = 17,
    {
        {0, "Infinite Health", .method = Cheats_Toggle},
        {0, "Infinite Magic", .method = Cheats_Toggle},
        {0, "Infinite Deku Sticks", .method = Cheats_Toggle},
        {0, "Infinite Deku Nuts", .method = Cheats_Toggle},
        {0, "Infinite Bombs", .method = Cheats_Toggle},
        {0, "Infinite Arrows", .method = Cheats_Toggle},
        {0, "Infinite Deku Seeds", .method = Cheats_Toggle},
        {0, "Infinite Bombchus", .method = Cheats_Toggle},
        {0, "Infinite Beans", .method = Cheats_Toggle},
        {0, "Infinite Keys", .method = Cheats_Toggle},
        {0, "Infinite Rupees", .method = Cheats_Toggle},
        {0, "Infinite Nayru's Love", .method = Cheats_Toggle},
        {0, "Freeze time of day", .method = Cheats_Toggle},
        #ifdef Version_JP
        {0, "No music (TODO)", .method = NULL},
        {0, "Usable Items (TODO)", .method = NULL},
        {0, "ISG", .method = Cheats_Toggle},
        {0, "Turbo Text (TODO)", .method = NULL},
        #else
        {0, "No music", .method = Cheats_Toggle},
        {0, "Unrestricted Items - Forced mode OFF", .method = Cheats_Toggle},
        {0, "ISG", .method = Cheats_Toggle},
        {0, "Turbo Text", .method = Cheats_Toggle},
        #endif
    }
};

void applyCheats() {
    if(cheats[CHEATS_HEALTH]) {
        gSaveContext.health = gSaveContext.healthCapacity;
    };
    if(cheats[CHEATS_MAGIC]) {
        gSaveContext.magic = 0x30 * gSaveContext.magicLevel;
    };
    if(cheats[CHEATS_STICKS]) {
        gSaveContext.ammo[SLOT_STICK] = 10 * ((gSaveContext.upgrades >> 17) & 0x7);
    };
    if(cheats[CHEATS_NUTS]) {
        gSaveContext.ammo[SLOT_NUT] = 10 + 10 * ((gSaveContext.upgrades >> 20) & 0x7);
    };
    if(cheats[CHEATS_BOMBS]) {
        gSaveContext.ammo[SLOT_BOMB] = 10 + 10 * ((gSaveContext.upgrades >> 3) & 0x7);
    };
    if(cheats[CHEATS_ARROWS]) {
        gSaveContext.ammo[SLOT_BOW] = 20 + 10 * (gSaveContext.upgrades & 0x7);
    };
    if(cheats[CHEATS_SEEDS]) {
        gSaveContext.ammo[SLOT_SLINGSHOT] = 20 + 10 * ((gSaveContext.upgrades >> 14) & 0x7);
    };
    if(cheats[CHEATS_BOMBCHUS]) {
        gSaveContext.ammo[SLOT_BOMBCHU] = 50;
    };
    if(cheats[CHEATS_BEANS]) {
        gSaveContext.ammo[SLOT_BEAN] = 10;
    };
    if(cheats[CHEATS_KEYS]) {
        for (int i = 0; i < 19; i++) {
            gSaveContext.dungeonKeys[i] = 1;
        }
    }
    if(cheats[CHEATS_RUPEES]) {
        u8 walletUpgrade = (gSaveContext.upgrades >> 12) & 0x3;
        switch(walletUpgrade){
            case 0:
                gSaveContext.rupees = 99;
                break;
            case 1:
                gSaveContext.rupees = 200;
                break;
            default:
                gSaveContext.rupees = 500;
                break;
        }
    };
    if(cheats[CHEATS_NAYRUS_LOVE]) {
        gSaveContext.nayrusLoveTimer = 1;
    };
    if(cheats[CHEATS_FREEZE_TIME]) {
        gSaveContext.dayTime = frozenTime;
    }
    //Loading a new area with these cheats active could crash. Checking isInGame() prevents that.
    //Note that calling isInGame() while the game is loading (triforce icon) crashes.
    //So don't enable the ISG cheat or forcedUsableItems there.
    if(cheats[CHEATS_ISG] && isInGame()) {
        PLAYER->isg = 1;
    };
    if(forcedUsableItems && isInGame()) {
        Cheats_UsableItems();
    }
}

u32 Cheats_RemoveBGM(u32 original) {
    if (cheats[CHEATS_NO_MUSIC]) {
        return SEQ_AUDIO_BLANK;
    }
    return original;
}

u32 Cheats_IsInstantText() {
    return cheats[CHEATS_QUICK_TEXT];
}

u32 Cheats_IsTurboText() {
    return (cheats[CHEATS_QUICK_TEXT] && rInputCtx.cur.b);
}

void Cheats_UsableItems() {
    // Leave restriction for states that disable buttons.
    if (!cheats[CHEATS_USABLE_ITEMS] || (!forcedUsableItems &&
        (gSaveContext.unk_1586[4] & 0x1 ||  // Ingo's Minigame state
        PLAYER->stateFlags1 & 0x08A02000 || // Swimming, riding horse, Down A, hanging from a ledge
        PLAYER->stateFlags2 & 0x00040000))  // Blank A
        // Shielding, spinning and getting skull tokens still disable buttons automatically
        ) {
        return;
    }

    for (int i = 1; i < 5; i++) {
        gSaveContext.buttonStatus[i] = BTN_ENABLED;
    }
    gSaveContext.ocarinaButtonStatus = BTN_ENABLED;
}

u32 Cheats_areItemsForcedUsable() {
    return cheats[CHEATS_USABLE_ITEMS] && forcedUsableItems;
}
