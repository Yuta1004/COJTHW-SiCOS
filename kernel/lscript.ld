OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY {
    MEM(rwx) : ORIGIN = 0x20000000, LENGTH = 512M
}

SECTIONS {
    .text : ALIGN(4) {
        *(.text .text.*)
    } > MEM

    _end = .;
}
