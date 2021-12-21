.arm
.text

.global hook_into_Gfx_Update
hook_into_Gfx_Update:
    push {r0-r12, lr}
    bl advance_main
    pop {r0-r12, lr}
    pop {r4-r8, pc}


.global hook_into_area_load
hook_into_area_load:
    push {r0-r12, lr}
    bl area_load_main
    pop {r0-r12, lr}
.if _USA_==1
    b 0x2E37D4
.endif
.if _JP_==1
    b 0x2E32EC
.endif

#.global hook_into_area_load_j
#hook_into_area_load_j:
#    push {r0-r12, lr}
#    bl area_load_main
#    pop {r0-r12, lr}
#    b 0x2E32EC

.global gGlobalContext
.global hook_into_global_context_update
hook_into_global_context_update:
    push {r0-r12, lr}
    bl setGlobalContext
    pop {r0-r12, lr}
.if _USA_==1
    b 0x2E25F0
.endif
.if _JP_==1
    b 0x2E2108
.endif

#.global hook_into_global_context_update_j
#hook_into_global_context_update_j:
#    push {r0-r12, lr}
#    bl setGlobalContext
#    pop {r0-r12, lr}
#    b 0x2E2108

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100028
    b  0x100004
