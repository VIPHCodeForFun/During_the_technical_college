#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char path[1000];
    char *pointer = NULL;
    pointer = &argv;

    strcpy(path, pointer); //Kopiert den Inhalt von s2 nach s1
    printf("\n%s\n", argv[0]);
    printf("\n%s\n", path[0]);
    return 0;
}
