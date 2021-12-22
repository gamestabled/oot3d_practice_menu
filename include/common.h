#ifndef _COMMON_H_
#define _COMMON_H_

#include "3ds/svc.h"

extern MemInfo query_memory_permissions(u32 address);
extern bool is_valid_memory_read(const MemInfo* info);

#endif //_COMMON_H_
