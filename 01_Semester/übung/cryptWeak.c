#include <stdio.h>
#include <string.h>
// verschlüsselung mittels XOR = ^
// char	 = 1 byte = 8 bit
void cryptWeak(char stringsurce[], char stringdest[], char code);

int main()
{
    char stringsorce[100] = {"Team B YEEEAAAAAAAA"};
    char stringdest[100] = "";
    char stringtest[100] = "";
    char code = 0x33;

    printf("%s\n", stringsorce);
    cryptWeak(stringsorce, stringdest, code);
    printf("%s\n", stringdest);
    cryptWeak(stringdest, stringtest, code);
    printf("%s\n", stringtest);
    if (strcmp(stringtest, stringsorce) == 0)
    {
        printf(" [cryptWeak] war erfolgreich :)");
    }
    return 0;
}

void cryptWeak(char stringsource[], char stringdest[], char code)
{
    int i = 0;

    for (i = 0; stringsource[i] != '\0'; i++)
    {
        if (stringsource[i] == code)
        {
            stringdest[i] = code;
        }
        else
        {
            stringdest[i] = stringsource[i] ^ code;
        }
    }
}
