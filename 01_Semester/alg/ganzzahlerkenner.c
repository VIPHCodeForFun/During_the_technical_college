#include <stdio.h>

int comparator();
int main ()
{
int zahl =0;
int i=0;
printf("Geben sie eine Zahl ein  ");
scanf("%d",&zahl);

    
    for(i=0;i<10;i++)
    {
        
        zahl*=3;
        if(zahl>=1000)
        {
        return 0;
        } 
    printf("%d). ",i);
    comparator(zahl,0); 
    }
return 0;
}
///////////////////////////////////////////////////
int comparator(int Zahl,int Modolo)
{
Modolo= Zahl%2;
if(Modolo==0)
{
    printf("Die Zahl %d ist gerade\n",Zahl);
}
else
{
    printf("\nDie Zahl %d ist ungerade\n",Zahl);
}
return 0;
}