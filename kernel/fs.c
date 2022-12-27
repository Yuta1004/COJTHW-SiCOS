#include "fs.h"

void fs_init() {
    for (unsigned char *p = FS_SADDR; p < FS_EADDR; p += 4096) {
        FS_Entry *entry = (FS_Entry*)p;
        entry->body = p + 0x18;
        if (FUSED(entry)) {
            entry += ((entry->size + 0x18) & (~0xfff));
        } else {
            entry->magic[0] = 0x12;
            entry->magic[1] = 0x04;
            entry->magic[2] = 0x41;
            entry->permission = 0;
            entry->size = 0;
        }
    }
}

FS_Entry *fs_head() {
    return (FS_Entry*)FS_SADDR;
}

FS_Entry *fs_next(FS_Entry *fp) {
    unsigned char *p = (unsigned char*)fp;
    p += ((fp->size + 0x18) & (~0xfff)) + 4096;
    if (p < FS_EADDR) {
        return (FS_Entry*)p;
    }
    return 0;
}

// int f_create(char *fname);
// int f_remove(char *fname);
// FS_Entry *f_read(char *fname);
