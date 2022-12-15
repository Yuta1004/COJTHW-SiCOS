OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY {
    MEM(rwx) : ORIGIN = 0x20000000, LENGTH = 512M
}

SECTIONS {
    .text : {
        *(.text .text.*)
    } > MEM

    .data : ALIGN(8) {
        *(.data .data.*)
    } > MEM

    _end = .;
}
