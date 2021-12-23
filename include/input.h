#include "z3D/z3D.h"
#include "hid.h"

#define ADDITIONAL_FLAG_BUTTON rInputCtx.cur.r

typedef struct {
    btn_t cur;
    btn_t up;
    btn_t pressed;
    btn_t old;
} InputContext;

void Input_Update(void);
u32 Input_WaitWithTimeout(u32 msec);
u32 Input_Wait(void);

extern InputContext rInputCtx;
