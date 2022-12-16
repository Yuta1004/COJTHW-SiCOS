void println(char *s) {
    for (char *p = s; *p != '\0'; ++ p) {
        while(*((volatile unsigned int*)0x80010008) != 4) {}
        *((volatile unsigned int*)0x80010004) = *p;
    }
    *((volatile unsigned int*)0x80010004) = 0x0d;
    *((volatile unsigned int*)0x80010004) = 0x0a;
}

int main() {
    *((volatile unsigned int*)0x8001000C) = 0b00011;

    println("Hello World!! From C Lang Program!!!\0");

    return 0;
}
