#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <windows.h>

int main()
{
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
                printf("LINKS gedrueckt!\n");
            }
            if (right_pressed)
            {
                printf("RECHTS gedrueckt!\n");
            }
            if (up_pressed)
            {
                printf("OBEN gedrueckt!\n");
            }
            if (down_pressed)
            {
                printf("UNTEN gedrueckt!\n");
            }
        }
        else
        {
            printf("Escape nicht gedrueckt!\n");
        }
        Sleep(500); //Zeit zum warten 1000 = 1sek
    }
    return 0;
}