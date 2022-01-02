OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(loader_patch)
SECTIONS
{
	. = 0x100000;
	.patch_loader 0x100000 : {
		*(.patch_loader)
	}

	.patch_InstantTextFirstLine 0x2DFFB4 : {
		*(.patch_InstantTextFirstLine)
	}

	.patch_InstantTextBoxBreak 0x2E017C : {
		*(.patch_InstantTextBoxBreak)
	}

	.patch_InstantTextRemoveOff 0x2E01E0 : {
		*(.patch_InstantTextRemoveOff)
	}

	/*.patch_load 0x2E32A8 : {
		*(.patch_load)
	}*/

	.patch_Gfx_Update 0x30FD6C : {
		*(.patch_Gfx_Update)
	}

	.patch_SetBGMEntrance 0x330B60 : {
		*(.patch_SetBGMEntrance)
	}

	.patch_TurboTextSignalNPC 0x34650C : {
		*(.patch_TurboTextSignalNPC)
	}

	.patch_PlaySound 0x35C040 : {
		*(.patch_PlaySound)
	}

	.patch_SetBGMEvent 0x36E758 : {
		*(.patch_SetBGMEvent)
	}

	.patch_SleepQueryCallback 0x3FD6C4 : {
		*(.patch_SleepQueryCallback)
	}

	.patch_ItemUsability_Shield 0x42E2C8 : {
		*(.patch_ItemUsability_Shield)
	}

	.patch_OverrideSceneSetup 0x448790 : {
		*(.patch_OverrideSceneSetup)
	}

	.patch_after_GlobalContext_Update 0x45240C : {
		*(.patch_after_GlobalContext_Update)
	}

	.patch_ItemUsability 0x476CF4 : {
		*(.patch_ItemUsability)
	}

	.patch_TurboTextAdvance 0x480900 : {
		*(.patch_TurboTextAdvance)
	}

	.patch_SetBGMDayNight 0x483C60 : {
		*(.patch_SetBGMDayNight)
	}

	.patch_TurboTextClose 0x4881EC : {
		*(.patch_TurboTextClose)
	}

	. = 0x4C99A8;
	. = ALIGN(4);
	.loader : {
		*(.loader*)
	}

	. = 0x005C7000;
    .text : {
        __text_start = . ;
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.data)
        *(.bss)
        *(COMMON)
        __text_end  = . ;
    }
}
