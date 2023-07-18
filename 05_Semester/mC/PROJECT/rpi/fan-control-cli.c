/*
 * Created: 16.01.2023
 * Author: Gruber Vidmar
 * gcc -o fan-control-cli fan-control-cli.c -lwiringPi
 * ./fan-control-cli
 */
#define RASPBERRY_PI

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "rasp-atmega32-spi-interface.h"

int main(int argc, char *argv[]){
    setupInterface();

    system("clear");
    printf("                   Fan-Control-CLI by ITSBB2020\n");
    printf("---------------------------------------------------------------------\n");
    // Check number of imput parameters
    if (argc < 2 || argc > 3){
        printf("!! Error if (argc < 2 || argc > 3) \n");
        printf("---------------------------------------------------------------------\n");
        return 0;
    }
    // Check the first value for "-"
    if (argv[1][0] != '-'){
        printf("!! Error if (argv[1][0] != '-') \n");
        printf("---------------------------------------------------------------------\n");
        return 0;
    }

    switch (argv[1][1]){
    case 'h': // Print this help
        showOptions();
        break;
        /* End Case */

    case 'p': // Get current PWM duty cycle
        getCurrentPwm();
        break;
        /* End Case */

    case 's': // Set current PWM duty cycle
        /* Check if two parameters have been passed */
        if (argc != 3){
            printf("!! Error if (argc != 3) \n");
            printf("---------------------------------------------------------------------\n");
            return 0;
        }
        int argcInt = atoi(argv[2]);
        // Check the second parameter is between 0 and 255
        if (argcInt < 0 || argcInt > 255){
            printf("!! Error if (argcInt < 0 || argcInt > 255) \n");
            printf("---------------------------------------------------------------------\n");
            return 0;
        }
        setCurrentPwm(argcInt);
        break;
        /* End Case */

    case 'r': // Release PWM duty cycle control
        releasePwmDutyCycle();
        break;
        /* End Case */

    case 't': // Get current fan RPM
        getCurrentFanRpm();
        break;
        /* End Case */

    default: // Show help
        printf("-h | <no option>   Print this help.\n");
        break;
        /* End Case */
    }
    /* End Switch */
    printf("---------------------------------------------------------------------\n");
    return 0;
}
