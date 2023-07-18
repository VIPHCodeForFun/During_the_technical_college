/*
    Juergen Brescher
    ITS-B Gruppe B
    
    Implementierung type/cat in C

    2021-03-12
*/

#include <stdio.h>
#include <stdlib.h>

// 1. neues File anlegen (static oder von argv)
// 2. File lesen
// 3. zeilenweise lesen
// 2. in File schreiben
// 3. Files schliessen

void main(int argc, char *argv[])
{
    // fopen()      // file open
    // fprintf()    // formatiertes schreiben in einen Stream
    // fgets()      // liest Zeile vom stream
    // fclose()     // schliesst file

    if (argc == 1)
    {
        printf("USAGE: %s sourcefile\n", argv[0]);
        return 0;
    }

    FILE *srcfile;
    FILE *dstfile;

    srcfile = fopen(argv[1], "rt"); // open file in textmode for readonly
    dstfile = fopen(argv[2], "w");  // open file in textmode for writing

    if (!srcfile)
    {
        printf("ERROR: could not open %s\n", argv[1]);
        return 0;
    }

    char buffer[32000];
    // bis fgets NULL returned
    while (NULL != (fgets(buffer, 32000, srcfile)))
    {
        //printf("%s", buffer);
        fputs(buffer, dstfile);
    }

    printf("Datei %s wurde nach %s kopiert", argv[1], argv[2]);
    fclose(srcfile);
    fclose(dstfile);

    return 0;
}
