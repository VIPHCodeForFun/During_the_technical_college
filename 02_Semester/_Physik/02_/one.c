// gcc 01_dac.c -lwiringPi
//gnuplot -c gnuplot/01_dac.gnuplot dat
#include <mcp3004.h>
#include <mcp4802.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wiringPi.h>

#define BASE 200
#define SPI_CHAN 0
#define SPI_CHAN 0
#define BASE2 300
#define SPI_CHAN2 1
#define VCC 3.3

double convertToVoltage(const int value)
{
    return (value * VCC) / 1024.0;
}

/** Converts the MCP4802 digital value to a corresponding output voltage.
@param value the value as it is passed to analogWrite() (range: 0-255)
@return The corresponding voltage
*/
double mcp4802ValueToVoltage(const int value)
{
    // Add your code here
    double rev_voltage = 2.048;
    double gain = 1;
    double voltage = gain * value * rev_voltage / 256;
    return voltage;
}

void checkArgs(const int argc, char *argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("Usage:\n %s [FILENAME]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

FILE *openFile(const char *filename)
{
    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return fp;
}

int main(int argc, char *argv[])
{
    checkArgs(argc, argv);
    FILE *fp = openFile(argv[1]);
    wiringPiSetup();

    mcp3004Setup(BASE, SPI_CHAN);
    mcp4802Setup(BASE2, SPI_CHAN2);

    fprintf(fp, "t u_{dac} u_{target}\n");
    const int max_dac_value = 255;
    const int n_read_per_value = 50;
    const int dac_out_channel = 0;
    const int adc_in_chanel = 0;

    for (int dac_value = 0; dac_value <= max_dac_value; ++dac_value)
    {
        analogWrite(BASE2 + dac_out_channel, dac_value);
        delay(1);
        // Continue here :-)
        for (int i = 0; i < n_read_per_value; ++i)
        {
            const int value = analogRead(BASE + adc_in_chanel); // analog read(200)
            const double u_dac = convertToVoltage(value);
            const int index = dac_value * n_read_per_value + i;
            fprintf(fp, " %d %f %f\n", index, u_dac, mcp4802ValueToVoltage(dac_value));
            fprintf(stdout, " %d %f %f\n", index, u_dac, mcp4802ValueToVoltage(dac_value));
        }
        // Read the voltage  50 times with 1 ms delay each and write to output file
    }
    analogWrite(BASE2 + dac_out_channel, 0);
    fclose(fp);
    return 0;
}
