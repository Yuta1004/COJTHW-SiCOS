#ifndef MEM_H
#define MEM_H

#define USED            0b1000
#define SINGLE          0b0000
#define MULTI_START     0b0001
#define MULTI_INTER     0b0010
#define MULTI_END       0b0100

#define MEMMAN_SIZE     (175 * 1024 * 1024)
#define MEMMAN_SADDR    ((unsigned char*)0x35000000)
#define MEMMAN_BADDR    (MEMMAN_SADDR + 0x100000)

#define MEMUSED(idx)    ((MEMMAN_SADDR[(idx)] & USED) == USED)
#define MEMSTAT(idx)    (MEMMAN_SADDR[(idx)] & 0b111)

void mem_alloc_table_init();

void *m_alloc(unsigned int size);
void m_free(void *p);

#endif
