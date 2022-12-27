#include "fs.h"

#include "lib/uart.h"

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

int f_create(char *fname, unsigned int size) {
    // 使用ページ数算出
    int pages = ((size + 0x18) >> 12) + 1;

    // 空きエントリ検索 -> エントリ作成
    for (FS_Entry *fp = fs_head(); fp != 0; fp = fs_next(fp)) {
        if (FUSED(fp)) continue;

        int cnt = 1;
        FS_Entry *sfp = fp;
        for (; cnt < pages; ++ cnt) {
            sfp = fs_next(sfp);
            if (FUSED(sfp) || sfp == 0) {
                break;
            }
        }
        if (cnt != pages) continue;

        // エントリ作成
        fp->permission = 0b100;
        fp->size = size;
        for (int cnt = 0; cnt < 11; ++ cnt) {
            fp->name[cnt] = fname[cnt];
        }
        fp->name[11] = '\0';

        // 連続して使用するエントリを使用済みにする
        for (int cnt = 1; cnt < pages; ++ cnt) {
            fp[cnt].permission = 0b100;
        }

        return 0;
    }

    return 1;
}


// int f_remove(char *fname);
// FS_Entry *f_read(char *fname);
