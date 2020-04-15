.arm
.text

.global hook_into_main
hook_into_main:
    push {r0-r12, lr}
    bl advance_main
    pop {r0-r12, lr}
    pop {r4- r8, pc}


.global hook_into_area_load
hook_into_area_load:
    push {r0-r12, lr}
    bl area_load_main
    pop {r0-r12, lr}
    b 0x2E37D4

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100028
    b  0x100004
