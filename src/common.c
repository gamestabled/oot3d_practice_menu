#include "common.h"
#include "z3D/z3D.h"

MemInfo query_memory_permissions(u32 address) {
    MemInfo memory_info = {};
    PageInfo page_info = {};
    svcQueryMemory(&memory_info, &page_info, address);
    return memory_info;
}

bool is_valid_memory_read(const MemInfo* info) {
    return (info->perm & MEMPERM_READ) != 0;
}

bool isInGame() { // TODO: recognize other states like Visions
    // these are file select and boss challenge menu
    return gSaveContext.gameMode != 2 && gSaveContext.gameMode != 4;
}
