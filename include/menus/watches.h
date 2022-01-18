#pragma once

#include "menu.h"

#define WATCHES_MAX 15
#define WATCHES_MAXNAME 6

typedef enum {
    S8 = 0,
    U8,
    X8,
    S16,
    U16,
    X16,
    S32,
    U32,
    X32,
    F32,
} WatchType;

typedef struct Watch {
    WatchType type;
    u32 posX;
    u32 posY;
    void* addr;
    u8 display; //whether to display on top screen
    char name[WATCHES_MAXNAME + 1];
} Watch;

extern Watch watches[WATCHES_MAX];
extern bool shouldDrawWatches;

void WatchesMenuFunc(void);
//void Watches_ToggleWatches(void);
