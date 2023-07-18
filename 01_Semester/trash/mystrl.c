#include <stdio.h>
#include <stdlib.h>

int mystrlen(char str[])
{
    int cnt = 0;
    while (str[cnt++] != '\0')
        ;
    return cnt - 1;
}

int main(int argc, char *argv[])
{

    printf("argc Nr.:%d\n", argc);
    if (argc < 2)
    {
        printf("USAGE: %s String1 [String2] [String3] ... [StringN]!\n", argv[0]);
        return 0;
    }

    int i;
    for (i = 1; i < argc; i += 1)
    {
        printf("%4d: \"%15s\" -> %2d\n", i, argv[i], mystrlen(argv[i]));
    }
    return 0;
}
