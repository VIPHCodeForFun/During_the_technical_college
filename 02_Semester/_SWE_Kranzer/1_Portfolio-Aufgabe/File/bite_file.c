
/*////////////////////////////////////////////////////////////////////////////
*Author:    Philipp Vidmar            
*Semester:  1/2021                                      
*Programm:  C  
*README:                                                                    
FILE lesen und schreiben im Binärmodus 
///////////////////////////////////////////////////////////////////////////*/
#include <stdio.h>

void input_bin_file(char path[], double input[], int size_of_input);
void output_bin_file(char path[], double output[], int size_of_output);

int main()
{
    int i = 0;
    double wert[10] = {3.500, 12.66, 1.027, 220.0, 88.93, 100, 330.005, 27.55};
    double file_data[10] = {0};
    //INFO
    printf("double =%d Bytes\n", sizeof(double));
    printf("wert   =%d Bytes\n", sizeof(wert));
    printf("wert/double= : %d\n", sizeof(wert) / sizeof(double));

    //Einlesen in ein Neues FILE.bin
    input_bin_file("test.bin", wert, 10);

    //Auslesen aus dem  FILE.bin
    output_bin_file("test.bin", file_data, 10);

    //Ausgabe
    printf("===wert===\n");
    for (i = 0; i < 10; i++)
    {
        printf("file_data[%d]=  %lf\n", i, wert[i]);
    }

    printf("===File_Data===\n");
    for (i = 0; i < 10; i++)
    {
        printf("file_data[%d]=  %lf\n", i, file_data[i]);
    }

    return 0;
}
//Einlesen in ein Neues FILE.bin
void input_bin_file(char path[], double input[], int size_of_input)
{
    FILE *p_file = NULL;
    //Erstellt das neue File und im Schreibmodus
    p_file = fopen(path, "wb");

    //Schreibt das Array "input[]" in das FILE.bin
    fwrite(input, sizeof(double), size_of_input, p_file);

    fclose(p_file);
    p_file = NULL;
    return;
}
void output_bin_file(char path[], double output[], int size_of_output)
{
    FILE *p_file = NULL;
    //Öffnet das neue File und im Lesemodus
    p_file = fopen(path, "rb");
    if (p_file == NULL)
    {
        printf("File \"%c\" not found ! ", path);
    }
    fread(output, sizeof(double), size_of_output, p_file);
    fclose(p_file);
    p_file = NULL;
    return;
}
