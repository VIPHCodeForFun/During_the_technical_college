#include <stdio.h>

int main(int argc, char *argv[])
{
    char x = '\n';

    printf("%c  %d \n", x, x);
    printf("%d \n", sizeof(int));  // int = 4 Byte
    printf("%d \n", sizeof(char)); // int = 4 Byte

    x = 255; //0xFF //ascii -1
    printf("[%c]", x);
    printf("[%d]", x);

    return 0;
}
