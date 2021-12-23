#pragma once

#include "menu.h"

extern ToggleMenu CheatsMenu;

void Cheats_ShowCheatsMenu();
void applyCheats();

typedef enum {
    /* 0x00*/ CHEATS_HEALTH = 0,
    /* 0x01*/ CHEATS_MAGIC,
    /* 0X02*/ CHEATS_STICKS,
    /* 0X03*/ CHEATS_NUTS,
    /* 0X04*/ CHEATS_BOMBS,
    /* 0X05*/ CHEATS_ARROWS,
    /* 0X06*/ CHEATS_SEEDS,
    /* 0X07*/ CHEATS_BOMBCHUS,
    /* 0X08*/ CHEATS_BEANS,
    /* 0X09*/ CHEATS_KEYS,
    /* 0X0A*/ CHEATS_RUPEES,
    /* 0X0B*/ CHEATS_NAYRUS_LOVE,
    /* 0X0C*/ CHEATS_FREEZE_TIME,
    /* 0X0D*/ CHEATS_NO_MUSIC,
    /* 0X0E*/ CHEATS_USABLE_ITEMS,
    /* 0X0F*/ CHEATS_ISG,
    /* 0X10*/ CHEATS_QUICK_TEXT,
    /* 0X11*/ CHEATS_MQ,
} CheatNames;
