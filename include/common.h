#ifndef _COMMON_H_
#define _COMMON_H_

#include "3ds/svc.h"

extern MemInfo query_memory_permissions(u32 address);
extern bool is_valid_memory_read(const MemInfo* info);
extern bool is_valid_memory_write(const MemInfo* info);
extern bool isInGame();
extern void drawAlert();
extern void pauseDisplay();

extern u32 alertFrames;
extern char* alertMessage;

#endif //_COMMON_H_
