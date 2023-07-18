/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #matrizen.c            #20.11.2020    
#README:                                                                     
Ein zweidimensionales Feld kann eine Matrix beschreiben. Erstellen Sie ein
Programm, welches zwei 3×3 Matrizen anlegt und die Werte nacheinander vom Benutzer
abfragt. Nach der Eingabe beider Matrizen soll das Matrixprodukt C = A·B ausgegeben
werden. Für die Multiplikation von n × n Matrizen ergibt sich das (i,j)-te Element
aus dem Skalarprodukt des i-ten Zeilenvektors von A und dem j-ten Spaltenvektor von
B.
Legen Sie die Dimensionen der Matrix dabei per #define fest und benutzen Sie trotz
der kleinen Dimension ein Schleifenkonstrukt sowohl zum einlesen, also auch zum
Berechnen des Matrixprodukts.
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> // I O
#include <stdlib.h>
#include <string.h> // strlen

#define Dim 3

int scanmatrix(int matrix[Dim][Dim]);
void printmatrix(int matrix[Dim][Dim]);
void mat_mult(int matrix_a[Dim][Dim], int matrix_b[Dim][Dim], int matrix_e[Dim][Dim]);
void pstop();

int main()
{
    int matrix_a[Dim][Dim];
    int matrix_b[Dim][Dim];
    int matrix_e[Dim][Dim];

    printf("Geben sie eine Matrix A ein\n");
    matrix_a[Dim][Dim] = scanmatrix(matrix_a);
    printf("Matrix A [%dx%d]:\n", Dim, Dim);
    printmatrix(matrix_a);
    printf("Geben sie eine Matrix B ein\n");
    matrix_b[Dim][Dim] = scanmatrix(matrix_b);
    printf("Matrix B [%dx%d]:\n", Dim, Dim);
    printmatrix(matrix_b);

    printf("Matrix A * B [%dx%d]:\n", Dim, Dim);
    mat_mult(matrix_a, matrix_b, matrix_e);
    printmatrix(matrix_e);

    pstop();

    return 0;
}
void pstop()
{
    printf("\n####################\n#|End|  push ENTER #\n####################");
    fflush(stdin);
    getchar();
}
// Matrix einlesen
// scanmatrix(int matrix[down][right])
int scanmatrix(int matrix[Dim][Dim])
{
    for (int y = 0; y < Dim; y++) //down
    {
        for (int x = 0; x < Dim; x++) //right
        {
            scanf("%d", &matrix[y][x]);
        }
    }
    return matrix[Dim][Dim];
}
// Matrix ausgeben
// scanmatrix(int matrix[down][right])
void printmatrix(int matrix[Dim][Dim])
{
    for (int y = 0; y < Dim; y++)
    {
        for (int x = 0; x < Dim; x++)
        {
            printf("%4d", matrix[y][x]);
        }
        printf("\n");
    }
    return;
}
// Matrix Multip(Matrix_A, Matrix_B,Matrix_Erg.)
void mat_mult(int matrix_a[Dim][Dim], int matrix_b[Dim][Dim], int matrix_e[Dim][Dim])
{
    int i = 0;
    int y = 0;
    int x = 0;
    for (y = 0; y < Dim; y++)
    {
        for (x = 0; x < Dim; x++)
        {
            matrix_e[y][x] = matrix_a[y][i] * matrix_b[i][x];
            for (i = 1; i < Dim; i++)
            {
                matrix_e[y][x] = matrix_e[y][x] + matrix_a[y][i] * matrix_b[i][x];
            }
            i = 0;
        }
    }
}
