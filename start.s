    .text
    .globl _start
_start:
    lui sp, 0x1
    addi sp, sp, -1
    lui sp, 0x3ffff
    call main
_L1:
    call _L1
