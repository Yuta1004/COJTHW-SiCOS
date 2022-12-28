    .text
    .globl _start

_start:
    j _start2

_syscall:
    j m_alloc       # 0x2000_0004 : void *m_alloc(unsigned int size)
    j m_free        # 0x2000_0008 : void m_free(void *p)
    j f_create      # 0x2000_000C : int f_create(char *fname, unsigned char permission, unsigned int size)
    j f_remove      # 0x2000_0010 : void f_remove(char*fname)
    j f_get         # 0x2000_0014 : FS_Entry *f_get(char *fname)

_start2:
    lui sp, 0x1
    addi sp, sp, -1
    lui sp, 0x3ffff
    call main

_L1:
    call _L1
