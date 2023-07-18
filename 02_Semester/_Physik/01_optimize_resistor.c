// gcc 01_optimize_resistor.c -Wall -Wextra

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "characteristic_curve.h"

double simulateCircuitOverTemperature(const int r, const int minT, const int maxT, const CharacteristicCurve *curve)
{
    if (curve == NULL)
    {
        return 0.0;
    }

    double minU = 1e10;
    double maxU = 0.0;
    const double uSource = 5; //3.3;

    double U_res = 0; //ToDo

    for (int i = 0; i < curve->nPoint; ++i)
    {
        const Point *p = &(curve->points[i]);
        const double ntcResistance = p->y;
        const double ntcTemperature = p->x;
        // TODO
        // Wenn die Temperatur außerhalb des Bereichs tMin bis tMax liegt, überspringen.
        if (minT > ntcTemperature || maxT < ntcTemperature)
        {
            continue;
        }
        // Berechnen des Spannungsabfalls am Widerstand R
        U_res = (r * uSource) / (ntcResistance + r);
        // Falls es ein neuer Minimalwert ist, auf uMin kopieren
        if (U_res < minU)
        {
            minU = U_res;
        }
        // Falls es ein neuer Maximalwert ist, auf uMax kopieren
        if (U_res > maxU)
        {
            maxU = U_res;
        }
    }
    return maxU - minU;
}

int main()
{

    CharacteristicCurve curve;
    characteristicCurveLoad(&curve, "ntc_10k_characteristic_curve.txt");
    characteristicCurvePrint(&curve);
    const int minT = 15;
    const int maxT = 40;

    const int minR = 100;
    const int maxR = 15000;
    const int incrR = 100;

    for (int r = minR; r <= maxR; r += incrR)
    {
        // find resistor for largest voltage change
        double uRange = simulateCircuitOverTemperature(r, minT, maxT, &curve);
        printf("%d,   %f\n", r, uRange);
    }

    return 0;
}
