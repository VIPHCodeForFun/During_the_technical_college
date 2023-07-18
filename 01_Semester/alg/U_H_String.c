#include <stdio.h> 
#include <string.h> 

// U_H_String.c

int main()
{
char Wort[100];
int length =0 ;

printf("Gib bitte ein Wort ein");
gets(Wort);             // scan den String();

length = strlen(Wort); //strlen(); Länge des Strings 

printf("Die Länge des Wortes %s ist %d",Wort,length); // %s für String %d für int


return 0;
}