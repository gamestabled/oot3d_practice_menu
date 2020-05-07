OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(main_patch)
SECTIONS
{
	. = 0x100000;
	.patch_loader : {
		*(.patch_loader*)
	}

	. = 0x2E32A8;
    . = ALIGN(4);
	.patch_load : {
		*(.patch_load*)
	}

	. = 0x30FD6C;
	. = ALIGN(4);
	.patch_main : {
		*(.patch_main*)
	}

    . = 0x45240C;
    . = ALIGN(4);
    .patch_get_global_context : {
        *(.patch_get_global_context*)
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
