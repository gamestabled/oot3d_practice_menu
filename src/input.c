#include "input.h"

#include "z3D/z3D.h"
#include "hid.h"
#include "3ds/svc.h"
#include "utils.h"

u32 GetCurrentPadState(void) {
    u32 hid_shared_mem = *(u32*)(0x005AEC5C);
    return *(volatile u32*)(hid_shared_mem + 0x1C);
}
#define HID_PAD (GetCurrentPadState())

InputContext rInputCtx;

void Input_Update(void) {
    rInputCtx.cur.val = real_hid.pad.pads[real_hid.pad.index].curr.val;
    rInputCtx.pressed.val = (rInputCtx.cur.val) & (~rInputCtx.old.val);
    rInputCtx.up.val = (~rInputCtx.cur.val) & (rInputCtx.old.val);
    rInputCtx.old.val = rInputCtx.cur.val;
}

u32 buttonCheck(u32 key) {
    for (u32 i = 0x26000; i > 0; i--) {
        if (key != real_hid.pad.pads[real_hid.pad.index].curr.val)
            return 0;
    }
    return 1;
}

u32 Input_WaitWithTimeout(u32 msec) {
    u32 pressedKey = 0;
    u32 key = 0;
    u32 n = 0;

    const bool isDPadPressed = (HID_PAD & BUTTON_UP) != 0 ||
                               (HID_PAD & BUTTON_DOWN) != 0 ||
                               (HID_PAD & BUTTON_LEFT) != 0 ||
                               (HID_PAD & BUTTON_RIGHT) != 0;

    // We special the D-Pad as we want to automatically scroll the cursor or
    // allow amount editing at a reasonable pace as long as it's held down.
    if (isDPadPressed)
    {
        // By default wait 75 milliseconds before moving the cursor so that
        // we don't scroll the menu too fast.
        svcSleepThread(75 * 1000 * 1000LL);
    }
    else
    {
        // Wait for no keys to be pressed in the event that up and down are not pressed.
        while (HID_PAD && (msec == 0 || n <= msec))
        {
            svcSleepThread(1 * 1000 * 1000LL);
            n++;
        }
    }

    if (msec != 0 && n >= msec) {
        return 0;
    }

    do {
        // Wait for a key to be pressed
        while (!HID_PAD && (msec == 0 || n < msec)) {
            svcSleepThread(1 * 1000 * 1000LL);
            n++;
        }

        if (msec != 0 && n >= msec) {
            return 0;
        }

        key = HID_PAD;

        // Make sure it's pressed
        pressedKey = buttonCheck(key);
    } while (!pressedKey);

    return key;
}

u32 Input_Wait(void) {
    return Input_WaitWithTimeout(0);
}
