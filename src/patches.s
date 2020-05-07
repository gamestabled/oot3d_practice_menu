.arm

.section .patch_main
.global main_patch

main_patch:
    b hook_into_main    

.section .patch_load
.global load_patch

load_patch:
    b hook_into_area_load

.section .patch_load_j
.global load_patch_j

load_patch_j:
    b hook_into_area_load_j

.section .patch_loader
.global loader_patch

loader_patch:
    b hook_into_loader

.section .patch_get_global_context
.global get_global_context_patch

get_global_context_patch:
    b hook_into_global_context_update

.section .patch_get_global_context_j
.global get_global_context_patch_j

get_global_context_patch_j:
    b hook_into_global_context_update_j