/*
 * pulse_counter.h
 *
 * Created: 17.11.2022 22:02:21
 *  Author: Matthias Gruber, Philipp Vidmar
 */ 

#include "time.h" 
#include "pin.h"
#include "usart.h"
#include "usart-string.h"

/** Setup and enables external Interrupts for Pin PD2 on falling egde. 
 ** Also activates timer and inits timestamp + pulsecounter
 */
void pulseCounterSetup();


/** Resets pulsecounter and timestamp
 * 
 */
void pulseCounterReset();

/** Gives the Measurement-result and resets . 
 * @param pulses Pulses recorded since last pulseCounterResult(),-Reset() or -Setup()
 * @param time  Elaspsed time since last pulseCounterResult(),-Reset() or -Setup()
 * 
 */
void pulseCounterResult(uint32_t* pulses,uint32_t* time);


