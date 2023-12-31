//The code for resizing the console window is given below

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

void pstop();

HANDLE wHnd; // Handle to write to the console.
HANDLE rHnd; // Handle to read from the console.
int main()   //int argc, char *argv[]
{
    // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    // Change the window title:
    SetConsoleTitle("Advanced C tutorial - programming-technique.blogspot.com");
    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 20, 20};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    // Change the console window size:
    // Create a COORD to hold the buffer size:
    //COORD bufferSize = {10, 10};
    //SetConsoleScreenBufferSize(wHnd, bufferSize);
    // Exit
    for (int i = 0; i < 20; i++)
    {
        printf("%d", i);
    }
    pstop();
    return 0;
}
void pstop()
{
    printf("\n####################\n#|End|  push ENTER #\n####################");
    fflush(stdin);
    getchar();
}