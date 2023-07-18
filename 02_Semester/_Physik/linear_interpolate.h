#ifndef LINEAR_INTERPOLATE_H_
#define LINEAR_INTERPOLATE_H_

#include "point.h"

/** Given the two points p0 and p1, the x-value of point p2 used to
 * calculate the corresponding y-value by linear interpolation.
 *
 * @param[in] p0 point 0
 * @param[in] p1 point 1
 * @param[in,out] p2 point 2, the x-value is used as input, the result is written to the y-value
*/

static inline void linearInterpolate(Point *p0, Point *p1, Point *p2)
{
    //printf("x1: %f y1: %f x2: %f y2: %f x3: %f\n", x1 , y1, x2, y2, x3);
    const double xDif = (p1->x - p0->x);
    const double scaling = (p1->x - p2->x) / xDif;
    const double yDif = (p1->y - p0->y);
    p2->y = p1->y - scaling * yDif;
    // k*x+d
    //k=delta Y/delta x
    double k = yDif / xDif;
    //2.4 = k * 3.6 + d / -k*3.6
    //2.4 - k * 3.6 = d
    double d = p0->y - k * p0->x;

    p2->y = k * p2->x + d;
    //(P0 = [x=3.6,y=2.4] und P1=[x=15.25,y=18.055],    P2 x-Wert = 10, Ergebnis: y=11.000172) .
}

#endif
