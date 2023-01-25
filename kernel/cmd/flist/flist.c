#include "flist.h"
#include "../../fs.h"
#include "../../lib/uart.h"

int cmd_flist(int argc, char **argv) {
    int used_entries = 0;
    for (FS_Entry *fp = fs_head(); fp != 0; fp = fs_next(fp)) {
        used_entries += ((fp->size + 0x18) >> 12) + 1;
        uart_prints(fp->name);
        uart_printc('\t');
        uart_printc((fp->permission & 0b100) ? 'r' : ' ');
        uart_printc((fp->permission & 0b010) ? 'w' : ' ');
        uart_printc((fp->permission & 0b001) ? 'x' : ' ');
        uart_printc('\t');
        uart_printhln(fp->size);
    }

    uart_prints("\nUSED: ");
    uart_printh(used_entries);
    uart_printc('/');
    uart_printhln(FS_SIZE >> 12);

    return 0;
}
