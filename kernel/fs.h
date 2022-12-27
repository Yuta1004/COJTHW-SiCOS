#ifndef FS_H
#define FS_H

#define FS_SIZE     (256 * 1024 * 1024)
#define FS_SADDR    ((unsigned char*)0x25000000)
#define FS_EADDR    (FS_SADDR + FS_SIZE)

typedef struct {
    unsigned char magic[3];
    unsigned char permission;
    unsigned char name[12];
    unsigned int  size;
    unsigned char *body;
} FS_Entry;

void fs_init();

int f_create(char *fname);
int f_remove(char *fname);
FS_Entry *f_read(char *fname);

#endif
