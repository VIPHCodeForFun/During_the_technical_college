/*
snake_v0.0.c
Philipp Vidmar
Step1 Move a Point  = ASCII 129
*/
#include <stdio.h>
//#include <stdlib.h> // für  system("cls");
int main ()
{
int x=5, y=5;                    // Startwert
int length=10,wide=10;           // Matrix begrenzung
int point=0,pointx=5,pointy=5;   // Points sammeln x und y werden per zufall generiert
system("cls"); // löscht die console
while(x>0 && x<wide && y>0 && y<length)
{
    int i=0;
    char eingabe;
    int move=0;
    if(x==pointx && y==pointy){point++;}
    scanf("%c",&eingabe);
    printf("%c",eingabe);
    move = eingabe;
    if(move== 97){ x--;} //a
    if(move==100){ x++;} //d
    if(move==115){ y++;} //s
    if(move==119){ y--;} //w
    system("cls"); // löscht die console
    printf("x=%d y=%d  M=%dx%d Points:%d \n",x,y,length,wide,point);
    printf(" 1 2 3 4 5 6 7 8 9\n");
    for(i=1;i<y;i++)
        {
        printf("%d\n",i);
        }
    for(i=0;i<x;i++)
        {
        printf("  ");
        }
    printf("X\n");
    
    
}
    printf("    GAME OVER   \a\n");
    system("pause"); // Pausiert das System
    return 0 ;
}