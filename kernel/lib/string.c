#include "string.h"
#include "muldiv.h"

int strcmp(char *a, char *b) {
    char *ap = a, *bp = b;
    while (*ap != '\0' && *bp != '\0') {
        if (*ap != *bp) {
            return *ap > *bp ? 1 : -1;
        }
        ap ++;
        bp ++;
    }
    if (*ap == '\0' && *bp == '\0') {
        return 0;
    }
    return *ap == '\0' ? -1 : 1;
}

long strtol(char *nptr, char **endp, int base) {
    char minus_flag = (char)(*nptr == '-');
    if (minus_flag) {
        ++ nptr;
    }

    // base自動判断
    if (base == 0) {
        if (nptr[0] == '0' && nptr[1] == 'x') {
            base = 16;
            nptr += 2;
        } else if (nptr[0] == '0') {
            base = 8;
            ++ nptr;
        } else {
            base = 10;
        }
    }

    // 変換
    long value = 0L;
    for (; *nptr != '\0'; ++ nptr) {
        switch (base) {
            case 16:
                if ('0' <= *nptr && *nptr <= '9') {
                    value = (value << 4) + (long)(*nptr - '0');
                } else if ('a' <= *nptr && *nptr <= 'f') {
                    value = (value << 4) + (long)(*nptr - 'a' + 10);
                } else {
                    return -1;
                }
                break;

            case 8:
                if ('0' <= *nptr && *nptr <= '7') {
                    value = (value << 3) + (long)(*nptr - '0');
                } else {
                    return -1;
                }
                break;

            default:
                if ('0' <= *nptr && *nptr <= '9') {
                    value = mul(value, base) + (long)(*nptr - '0');
                } else {
                    return -1;
                }
        }
    }

    return minus_flag ? -value : value;
}
