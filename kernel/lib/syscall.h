#ifndef SYSCALL_H
#define SYSCALL_H

typedef struct {
    unsigned char magic[3];
    unsigned char permission;
    unsigned char name[12];
    unsigned int  size;
    unsigned char *body;
} FS_Entry;

#define SYSCALL_M_ALLOC     (*((void*(*)(unsigned int))0x20000004))
#define SYSCALL_M_FREE      (*((void(*)(void*))0x20000008))
#define SYSCALL_F_CREATE    (*((int(*)(char*, unsigned char, unsigned int))0x2000000C))
#define SYSCALL_F_REMOVE    (*((void(*)(char*))0x20000010))
#define SYSCALL_F_GET       (*((FS_Entry*(*)(char*))0x20000014))

#endif
