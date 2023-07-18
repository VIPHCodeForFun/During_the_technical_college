
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <windows.h>

int main()
{

    int x = 5, y = 5;
    int direction = 2; //start Right
    uint16_t left_pressed;
    uint16_t right_pressed;
    uint16_t up_pressed;
    uint16_t down_pressed;

    printf("Beenden mit DELETE!\n");
    while (!GetAsyncKeyState(VK_DELETE))
    {
        left_pressed = GetAsyncKeyState(VK_LEFT);
        right_pressed = GetAsyncKeyState(VK_RIGHT);
        up_pressed = GetAsyncKeyState(VK_UP);
        down_pressed = GetAsyncKeyState(VK_DOWN);

        if (left_pressed || right_pressed || up_pressed || down_pressed)
        {
            if (left_pressed)
            {
                x--;
                direction = 1;
            }
            if (right_pressed)
            {
                x++;
                direction = 2;
            }
            if (up_pressed)
            {
                y--;
                direction = 3;
            }
            if (down_pressed)
            {
                y++;
                direction = 4;
            }
        }
        else
        {
            printf("Escape nicht gedrueckt!\n");
            if (direction == 1)
            {
                x--; // go left
            }
            if (direction == 2)
            {
                x++; // go right
            }
            if (direction == 3)
            {
                y--; // go up
            }
            if (direction == 4)
            {
                y++; //go down
            }
        }
        printf("x=%d y=%d\n", x, y);
        Sleep(500); //Zeit zum warten 1000 = 1sek
    }
    return 0;
}

/*
//input.c
#include <stdio.h>
#include <conio.h>  // Library where getch() is stored 
//multithreads

int main ()
{

char eingabe;
int move=0;
scanf("%c",&eingabe);
printf("%c",eingabe);
move = eingabe;
if(move== 97){ x--;} //a
if(move==100){ x++;} //d
if(move==115){ y--;} //s
if(move==119){ y++;} //w
    return 0;
}*/