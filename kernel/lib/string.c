#include "string.h"

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
