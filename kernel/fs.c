#include "fs.h"

void fs_init() {
    for (unsigned char *p = FS_SADDR; p < FS_EADDR; p += 4096) {
        FS_Entry *entry = (FS_Entry*)p;
        entry->body = (unsigned char*)(entry) + 0x18;
        if (entry->magic[0] == 0x12 && entry->magic[1] == 0x04 && entry->magic[2] == 0x41) {
            p += (entry->size & (~0xfff));
        } else {
            entry->magic[0] = 0x12;
            entry->magic[1] = 0x04;
            entry->magic[2] = 0x41;
            entry->permission = 0;
        }
    }
}

// int f_create(char *fname);
// int f_remove(char *fname);
// FS_Entry *f_read(char *fname);
