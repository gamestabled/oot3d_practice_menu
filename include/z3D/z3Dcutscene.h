#ifndef _Z3DCUTSCENE_H_
#define _Z3DCUTSCENE_H_

#include "z3Dvec.h"

typedef struct {
    /* 0x00 */ u16 action; // "dousa"
    /* 0x02 */ u16 startFrame;
    /* 0x04 */ u16 endFrame;
    /* 0x06 */ Vec3s rot;
    /* 0x0C */ Vec3i startPos;
    /* 0x18 */ Vec3i endPos;
    /* 0x24 */ Vec3i normal;
} CsCmdActorAction; // size = 0x30

#endif //_Z3DCUTSCENE_H_