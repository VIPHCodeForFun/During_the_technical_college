//.\a.exe "(3.6,2.4) (15.25,18.055) (10)"

#include "linear_interpolate.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error arg\n");
        return -1;
    }
    Point p0, p1, p2;
    const int nExpectedParsedValue = 5;
    const int res = sscanf(argv[1], "(%lf,%lf) (%lf,%lf) (%lf,y)", &p0.x, &p0.y, &p1.x, &p1.y, &p2.x);
    if (res != nExpectedParsedValue)
    {
        printf("Error\n");
        return -1;
    }
    linearInterpolate(&p0, &p1, &p2);
    printf("p0 = (%f,%f)\np1 = (%f,%f)\nlinear interpolation for y (@ x = %f) is %f", p0.x, p0.y, p1.x, p1.y, p2.x, p2.y);
    return 0;
}
