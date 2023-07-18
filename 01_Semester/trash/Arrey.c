// EINFACHES "HASHFUNKTION" BEISPIEL
#include <stdio.h>
#include <string.h>

int main (){
unsigned char eingabe[10]= "" ; 
int arreyzahl = 0;
// EINGABE
scanf("%s",&eingabe);
// HASHFUNKTION
int strl =0; strl = strlen(eingabe);  
for(int i=0;i<strlen(eingabe)+1;i++)            
    {
    arreyzahl = arreyzahl +*(eingabe+strl); //ASCII Summe
    strl--;                                
    } 
arreyzahl = arreyzahl%100;               
printf("Arrey ZAHL\t= [%d]\n",arreyzahl);        
return 0;
}