// gcc 02_dac.c -lwiringPi
//gnuplot -c gnuplot/02_led_ui.gnuplot "Messung_33_Ohm red Messung_75_Ohm green Messung_105_Ohm blue Messung_1000_Ohm yellow"
//gnuplot -c gnuplot/02_led_ui.gnuplot "Messung_LED_rot red Messung_LED_gruen green Messung_LED_gelb yellow"
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
@param value the value as it ivs passed to analogWrite() (range: 0-255)
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

    fprintf(fp, "u_{p} u_{0} u_{r} ad_{0} ad_{1} da_{0}\n");
    fprintf(stdout, "u_{p} u_{0} u_{r} ad_{0} ad_{1} da_{0}\n");
    const int max_dac_value = 255;
    const int n_read_per_value = 50;
    const int dac_out_channel = 0;
    const int u_0_canel = 0;
    const int u_r_canel = 1;

    for (int dac_value = 0; dac_value <= max_dac_value; ++dac_value)
    {
        analogWrite(BASE2 + dac_out_channel, dac_value);
        delay(20);
        // Continue here :-)

        const int ad_value0 = analogRead(BASE + u_0_canel); // CH0 analog read(200)
        const double U_0 = convertToVoltage(ad_value0);
        const int ad_value1 = analogRead(BASE + u_r_canel); // CH1 analog read(200)
        const double U_R = convertToVoltage(ad_value1);
        const double U_D = U_0 - U_R;
        const double I = (U_R / 33) * 1000; // R = 33 Ohm

        //"u_{p} u_{0} u_{r} ad_{0} ad_{1} da_{0}\n
        fprintf(fp, " %f %f %f %f %d %d %d\n", U_D, U_0, U_R, I, ad_value0, ad_value1, dac_value);
        fprintf(stdout, " %f %f %f %f %d %d %d\n", U_D, U_0, U_R, I, ad_value0, ad_value1, dac_value);

        // Read the voltage  50 times with 1 ms delay each and write to output file
    }

    analogWrite(BASE2 + dac_out_channel, 0);

    fclose(fp);
    return 0;
}
