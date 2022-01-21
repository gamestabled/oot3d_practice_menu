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

#define DPAD_BUTTONS  (BUTTON_UP | BUTTON_DOWN | BUTTON_LEFT | BUTTON_RIGHT)

InputContext rInputCtx;
u8 scrollDelay = 1;

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

    const bool isScrollButtonPressed = (HID_PAD & (DPAD_BUTTONS | BUTTON_A)) != 0;

    // We special some buttons as we want to automatically scroll the cursor or
    // allow amount editing at a reasonable pace as long as it's held down.
    if (isScrollButtonPressed && scrollDelay)
    {
        // Wait 250 ms the first time, as long as the button isn't released
        for(u32 i = 0; HID_PAD && i < 250; i+=10) {
            svcSleepThread(10 * 1000 * 1000LL);
        }
        scrollDelay = 0;
    }
    else if (isScrollButtonPressed)
    {
        // By default wait 50 milliseconds before moving the cursor so that
        // we don't scroll the menu too fast.
        svcSleepThread(50 * 1000 * 1000LL);
    }
    else
    {
        rInputCtx.cur.val = HID_PAD;
        // Wait for a new key to be pressed in the event that up and down are not pressed.
        while (HID_PAD <= rInputCtx.cur.val && (msec == 0 || n <= msec))
        {
            scrollDelay = 1;
            rInputCtx.cur.val = HID_PAD;
            svcSleepThread(1 * 1000 * 1000LL);
            n++;
        }
    }

    do {
        if (msec != 0 && n >= msec) {
            return 0;
        }

        key = HID_PAD;

        // Make sure it's pressed
        pressedKey = buttonCheck(key);
    } while (!pressedKey);

    rInputCtx.cur.val = key;
    return key;
}

u32 Input_Wait(void) {
    return Input_WaitWithTimeout(0);
}
