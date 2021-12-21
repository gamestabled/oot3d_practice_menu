.arm

.section .patch_Gfx_Update
.global Gfx_Update_patch
Gfx_Update_patch:
    b hook_into_Gfx_Update

.section .patch_load
.global load_patch
load_patch:
    b hook_into_area_load

.section .patch_after_GlobalContext_Update
.global after_GlobalContext_Update_patch
after_GlobalContext_Update_patch:
    b hook_into_global_context_update

.section .patch_loader
.global loader_patch
loader_patch:
    b hook_into_loader
