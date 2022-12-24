#include "mem.h"

void mem_alloc_table_init() {
    for (unsigned char *p = MEMMAN_SADDR; p < MEMMAN_BADDR; ++ p) {
        *p = 0;
    }
}

void *m_alloc(unsigned int size) {
    // 使用ページ数算出
    int pages = ((size-1)>>8) + 1;

    // 確保状況テーブル検索
    unsigned char *found_p = 0;
    for (unsigned char *p = MEMMAN_SADDR; p < MEMMAN_BADDR; ++ p) {
        int cnt = 0;
        for (; (p[cnt] & USED) == 0 && cnt < pages; ++ cnt);
        if (cnt == pages) {
            found_p = p;
            break;
        }
    }
    if (found_p == 0) {
        return 0;
    }

    // 確保状況テーブル更新
    if (pages == 1) {
        *found_p = USED | SINGLE;
    } else {
        found_p[0] = USED | MULTI_START;
        for (int cnt = 1; cnt < pages-1; ++ cnt) {
            found_p[cnt] = USED | MULTI_INTER;
        }
        found_p[pages-1] = USED | MULTI_END;
    }

    // 物理アドレス算出
    int idx = (found_p - MEMMAN_SADDR) << 8;
    return (void*)(MEMMAN_BADDR + idx);
}

void m_free(void *p) {
    // インデックス計算
    int idx = ((int)p - (int)MEMMAN_BADDR) >> 8;

    // 解放チェック
    if (!MEMUSED(idx)) {
        return;
    }

    // 解放
    if (MEMSTAT(idx) == SINGLE) {
        MEMMAN_SADDR[idx] = 0;
    }
    else if (MEMSTAT(idx) == MULTI_START) {
        for (; MEMSTAT(idx) != MULTI_END; ++ idx) {
            MEMMAN_SADDR[idx] = 0;
        }
        MEMMAN_SADDR[idx] = 0;
    }
    else if (MEMSTAT(idx) == MULTI_INTER || MEMSTAT(idx) == MULTI_END) {
        for (; MEMSTAT(idx) != MULTI_START; -- idx);
        for (; MEMSTAT(idx) != MULTI_END; ++ idx) {
            MEMMAN_SADDR[idx] = 0;
        }
        MEMMAN_SADDR[idx] = 0;
    }
}
