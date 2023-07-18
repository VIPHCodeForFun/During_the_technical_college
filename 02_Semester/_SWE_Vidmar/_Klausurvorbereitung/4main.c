#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *p_file = fopen("test.txt", "r");
    FILE *p_dest = fopen("dest.txt", "wt");
    if (p_file == NULL || p_dest == NULL)
    {
        printf("ERROR\n");
        return -1;
    }
    char name[100]; //Funktioniert :D
    int nr = 0;

    while (fscanf(p_file, "%[^,], %d\n", name, &nr) != EOF)
    {
        printf("%s,%d \n", name, nr);
        fprintf(p_dest, "%s,%d \n", name, nr);
    }
    fclose(p_dest);
    fclose(p_file);
    return 0;
}