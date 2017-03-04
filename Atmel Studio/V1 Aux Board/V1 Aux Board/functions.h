#ifndef FUNCTIONS_H_  //Guard
#define FUNCTIONS_H_

#define F_CPU 2000000UL //Frequency for delay.h
#define TWOE16 65535

#include <avr/io.h>     // I/O functions for AVR CPU
#include <util/delay.h> // Enables delay functions
#include <avr/power.h>  // Provides functions to reduce power usage
#include <math.h>		// Provides general math functions. May or may not actually be used
#include <avr/eeprom.h> // Provides functions that write data to the eeprom 

struct ADCOut{    //ADC output is in 2 bytes, so we're going to use a structure of 2, 8bit numbers to store
	uint8_t leftbyte;    //This is going to hold the information in ADCL
	uint8_t rightbyte;	 //This "                                 " ADCH  (ADCL and ADCH are registers that hold ADC data)
};

double getPower(void); //Calls getCurrent and getVoltage and outputs the power usage

double getCurrent(void); //calls ADCRead and generates current out utilization of aux board

double getVoltage(void); //calls ADCRead and generates voltage of the battery input

uint16_t ADCRead(uint8_t pin);  //Read the ADC outputing 0-1024, where 1024 is 5V
						        //Note this is using the ADCOut structure that holds 2, 8bit numbers.

void writeEEPROM(uint16_t * addr, double data); //Store power output to read later.

uint16_t byteCombine(struct ADCOut input);  //Combines 2, 8-bit numbers into a 10-bit (For ADC Out)


#endif // FUNCTIONS_H_