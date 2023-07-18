#include <mcp3004.h>
#include <mcp4802.h>
#include <wiringPi.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "characterisitic_curve.h"
#include "linear_interpolate.h"

#define BASE 200
#define SPI_CHAN 0
#define VCC 3.3

int exitLoop = 0;

void invokeExit(int signo)
{
	printf("-> Exit\n");
	exitLoop = 1;
}

FILE *openFile(const char *filename, const char *mode)
{
	FILE *fp = fopen(filename, mode);

	if (fp == NULL)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	return fp;
}

double linearInterpolatePiecewise(const CharacteristicCurve *curve, double r)
{
	if (curve == NULL)
	{
		return 0.0;
	}
	double result = 0.0;
	Point *prev = &(curve->points[0]);

	for (int i = 0; i < curve->nPoint; ++i)
	{
		const Point *p = &(curve->points[i]);
		const double ntcResistance = p->y;
		const double ntcTemperature = p->x;
		if (ntcResistance > r)
		{
			Point pi;
			pi.y = r;
			linearInterpolate(prev, p, &pi);
			result = pi.x;
			break;
		}
		prev = p;
	}

	return result;
}

double readVoltage(const int chan)
{
	return (analogRead(BASE + chan) * VCC) / 1024.0;
}

void checkArgs(const int argc, char *argv[])
{
	if (argc < 2 || argc > 2)
	{
		fprintf(stderr, "Usage:\n %s [FILENAME]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{

	//printf("Self-test: %f == 5.25\n", linearInterpolate(3,4,5,9,3.5));

	checkArgs(argc, argv);
	FILE *fp = openFile(argv[1], "w");
	wiringPiSetup();

	mcp3004Setup(BASE, SPI_CHAN);

	signal(SIGINT, invokeExit);

	CharacteristicCurve curve;
	characteristicCurveLoad(&curve, "ntc_10k_characteristic_curve.txt");
	characteristicCurvePrint(&curve);

	fprintf(fp, "time u_{o} u_{ntc} r_{ntc} T_{ntc}\n");

	double passedTime = millis();
	const int R = 10000;

	while (!exitLoop)
	{
		const double ntcU = readVoltage(0);				   // read adc channel 0
		const double ntcResistance = R / (VCC / ntcU - 1); // ntcResistance via the formula
		const double ntcTemp = linearInterpolatePiecewise(&curve, ntcResistance);
		passedTime = millis();
		fprintf(fp, "%f %f %f %f %f\n", passedTime, VCC, ntcU, ntcResistance, ntcTemp);
		fflush(fp);
		delay(500);
	}
	fclose(fp);
	return 0;
}
