#include "muldiv.h"

int mul(int a, int b) {
    int result = 0;
    for (int cnt = 0; cnt < b; ++ cnt)
        result += a;
    return result;
}

int div(int a, int b) {
    int result = 0;
    while (a >= b) {
        result += 1;
        a -= b;
    }
    return result;
}

int mod(int a, int b) {
    while (a >= b)
        a -= b;
    return a;
}
