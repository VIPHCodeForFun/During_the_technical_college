#include <stdio.h>

#include <windows.h>
#include <mmsystem.h>

// gcc playsound.c -lWinmm

int main()
{
    char path[] = {"Kevin MacLeod.wav"};

    //PlaySound(TEXT("Kevin MacLeod.wav"), NULL, SND_LOOP);
    PlaySound(path, NULL, SND_LOOP);

    PlaySound(TEXT("SystemStart"), NULL, SND_ALIAS);

    return 0;
}