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

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100028
    b  0x100004

.global hook_PlaySound
hook_PlaySound:
    push {r1-r12, lr}
    bl Cheats_RemoveBGM
    pop {r1-r12, lr}
    push {r3-r7, lr}
    b 0x35C52C

.global hook_SetBGMEntrance
hook_SetBGMEntrance:
    push {r1-r12, lr}
    bl Cheats_RemoveBGM
    pop {r1-r12, lr}
    push {r4-r6, lr}
    b 0x33104C

.global hook_SetBGMDayNight
hook_SetBGMDayNight:
    push {r1-r12, lr}
    bl Cheats_RemoveBGM
    pop {r1-r12, lr}
    push {r4-r6, lr}
    b 0x483C8C

.global hook_SetBGMEvent
hook_SetBGMEvent:
    push {r0, r2-r12, lr}
    cpy r0,r1
    bl Cheats_RemoveBGM
    cpy r1,r0
    pop {r0, r2-r12, lr}
    push {r4-r11, lr}
    b 0x36EC44

.global hook_InstantTextFirstLine
hook_InstantTextFirstLine:
    cmp r9,#0x0
    bgt NoInstantText
    push {r0-r12, lr}
    bl Cheats_IsInstantText
    cmp r0,#0x1
    pop {r0-r12, lr}
    bne NoInstantText
    push {r0-r12, lr}
    ldr r0,[r5,#0x0]
    ldr r1,[r0,#0x20]
    cpy r0,r5
    blx r1
    strb r11,[r4,#0x24]
    pop {r0-r12, lr}
NoInstantText:
    cmp r10,#0xFF
    bx lr

.global hook_InstantTextBoxBreak
hook_InstantTextBoxBreak:
    push {r0-r12, lr}
    bl Cheats_IsInstantText
    cmp r0,#0x1
    pop {r0-r12, lr}
    bne 0x2E0EE0
    push {r0-r12, lr}
    ldr r0,[r5,#0x0]
    ldr r1,[r0,#0x20]
    cpy r0,r5
    blx r1
    strb r11,[r4,#0x24]
    pop {r0-r12, lr}
    b 0x2E0EE0

.global hook_InstantTextRemoveOff
hook_InstantTextRemoveOff:
    push {r0-r12, lr}
    bl Cheats_IsInstantText
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x2E0ED4
    ldr r0,[r5,#0x0]
    b 0x2E06CC

.global hook_TurboTextAdvance
hook_TurboTextAdvance:
    push {r0-r12, lr}
    bl Cheats_IsTurboText
    cmp r0,#0x0
    pop {r0-r12, lr}
    cmpeq r0,#0x0
    bx lr

.global hook_TurboTextClose
hook_TurboTextClose:
    push {r0-r12, lr}
    bl Cheats_IsTurboText
    cmp r0,#0x0
    pop {r0-r12, lr}
    cmpeq r0,#0x0
    bx lr

.global hook_TurboTextSignalNPC
hook_TurboTextSignalNPC:
    movne r4,#0x1
    push {r0-r12, lr}
    bl Cheats_IsTurboText
    cmp r0,#0x0
    pop {r0-r12, lr}
    movne r4,#0x1
    bx lr

.global hook_ItemUsability
hook_ItemUsability:
    push {r0-r12, lr}
    bl Cheats_UsableItems
    pop {r0-r12, lr}
    add sp,sp,#0x14
    bx lr
