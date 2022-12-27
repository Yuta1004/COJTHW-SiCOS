#ifndef FS_H
#define FS_H

typedef struct {
    unsigned char magic[3];
    unsigned char permission;
    unsigned char name[12];
    unsigned int  size;
    unsigned char *body;
} FS_Entry;

#define FS_SIZE     (256 * 1024 * 1024)
#define FS_SADDR    ((unsigned char*)0x25000000)
#define FS_EADDR    (FS_SADDR + FS_SIZE)

#define FCHECK(fp)  ((*((unsigned int*)(fp)) & 0xffffff) == 0x410412)
#define FUSED(fp)   (FCHECK(fp) && (*((unsigned int*)(fp)) & 0xff000000) != 0)

void fs_init();
FS_Entry *fs_head();
FS_Entry *fs_next(FS_Entry *fp);

int f_create(char *fname, unsigned int size);
void f_remove(char *fname);
FS_Entry *f_get(char *fname);

#endif
