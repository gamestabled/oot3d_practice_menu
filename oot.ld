OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(loader_patch)
SECTIONS
{
	. = 0x100000;
	.patch_loader 0x100000 : {
		*(.patch_loader)
	}

	.patch_InstantTextFirstLine 0x2E049C : {
		*(.patch_InstantTextFirstLine)
	}

	.patch_InstantTextBoxBreak 0x2E0664 : {
		*(.patch_InstantTextBoxBreak)
	}

	.patch_InstantTextRemoveOff 0x2E06C8 : {
		*(.patch_InstantTextRemoveOff)
	}

	.patch_load 0x2E3790 : {
		*(.patch_load)
	}

	.patch_Gfx_Update 0x310254 : {
		*(.patch_Gfx_Update)
	}

	.patch_SetBGMEntrance 0x331048 : {
		*(.patch_SetBGMEntrance)
	}

	.patch_TurboTextSignalNPC 0x3469F4 : {
		*(.patch_TurboTextSignalNPC)
	}

	.patch_PlaySound 0x35C528 : {
		*(.patch_PlaySound)
	}

	.patch_SetBGMEvent 0x36EC40 : {
		*(.patch_SetBGMEvent)
	}

	.patch_SleepQueryCallback 0x3FD6C4 : {
		*(.patch_SleepQueryCallback)
	}

	.patch_ItemUsability_Shield 0x42E2F0 : {
		*(.patch_ItemUsability_Shield)
	}

	.patch_OverrideSceneSetup 0x4487B8 : {
		*(.patch_OverrideSceneSetup)
	}

	.patch_before_GlobalContext_Update 0x452390 : {
		*(.patch_before_GlobalContext_Update)
	}

	.patch_after_GlobalContext_Update 0x452434 : {
		*(.patch_after_GlobalContext_Update)
	}

	.patch_ItemUsability 0x476D1C : {
		*(.patch_ItemUsability)
	}

	.patch_TurboTextAdvance 0x480928 : {
		*(.patch_TurboTextAdvance)
	}

	.patch_SetBGMDayNight 0x483C88 : {
		*(.patch_SetBGMDayNight)
	}

	.patch_TurboTextClose 0x488214 : {
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
