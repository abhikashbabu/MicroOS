ENTRY(_start)

SECTIONS
{
    /* Kernel ko 1MB (0x100000) memory address par load karna hai (GRUB ki requirement) */
    . = 1M;

    /* SABSE PEHLE: Multiboot Header yahan aayega taaki GRUB ko turant mil jaye! */
    .multiboot ALIGN(4K) :
    {
        *(.multiboot)
    }

    /* Uske baad tumhara assembly aur C ka main code */
    .text ALIGN(4K) :
    {
        *(.text)
    }

    /* Read-only data (jaise tumhare strings aur fonts) */
    .rodata ALIGN(4K) :
    {
        *(.rodata)
    }

    /* Initialized variables */
    .data ALIGN(4K) :
    {
        *(.data)
    }

    /* Uninitialized variables (BSS) aur Stack */
    .bss ALIGN(4K) :
    {
        *(COMMON)
        *(.bss)
    }
}