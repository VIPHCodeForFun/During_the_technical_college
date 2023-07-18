#ifndef CHARACTERISTIC_CURVE_H_
#define CHARACTERISTIC_CURVE_H_

#include "point.h"

#define CURVE_MAX_N_POINT 128

typedef struct
{
    int nPoint; // actual number of stored curve points
    Point points[CURVE_MAX_N_POINT];
} CharacteristicCurve;

/** Load a characteristic curve from a given file
 *
 * @param[out] curve
 * @param[in] fileName
*/

static int characteristicCurveLoad(CharacteristicCurve *curve, const char *fileName)
{
    if (fileName == NULL || curve == NULL)
    {
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char buf[256];
    int returnValue = EXIT_SUCCESS;
    int i = 0;
    curve->nPoint = 0;

    fgets(buf, sizeof(buf), fp); // read away header line

    while (i < CURVE_MAX_N_POINT && fgets(buf, sizeof(buf), fp) != NULL)
    {
        const int nRead = sscanf(buf, "%lf %lf %*f %*f\n", // '%*f' ... supressed float value, not used
                                 &(curve->points[i].x), &(curve->points[i].y));

        if (nRead != 2)
        {
            printf("Error: File '%s' has invalid format \n", fileName);
            returnValue = EXIT_FAILURE;
            break;
        }
        ++i;
    }

    fclose(fp);
    curve->nPoint = i;

    if (i >= CURVE_MAX_N_POINT)
    {
        fprintf(stderr, "Error: File '%s' contains further data"
                        " - maximum capacity %d reached\n",
                fileName, CURVE_MAX_N_POINT);
        returnValue = EXIT_FAILURE;
    }
    else
    {
        printf("Info: Loaded %d value pairs from file '%s'\n", i, fileName);
    }

    return returnValue;
}

static void characteristicCurvePrint(const CharacteristicCurve *curve)
{
    if (curve == NULL)
    {
        return;
    }
    for (int i = 0; i < curve->nPoint; ++i)
    {
        const Point *p = &(curve->points[i]);
        printf("%f %f\n", p->x, p->y);
    }
}

#endif
