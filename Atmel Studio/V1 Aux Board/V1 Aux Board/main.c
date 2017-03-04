/* 
 * V1
 * Aux Board ATmega328p
 *
 * Created: 2017-02-02 6:13:22 PM
 * Author : Koltin Kosik-Harvey
 */ 

//These are functions I developed all in one place
//Also includes various headers like io, power, delay, and math
#include "functions.h"
//All functions and headers to be moved to functions.h
//this is to clean up the main.c 

/************************************************************
	This program is designed to poll 2 ADC pins
	carrying the voltage and current information of 
	the aux power board. Storing the POWER usage into double 
	sized values into the EEPROM. Future revisions may 
	include support for a LED display. (maybe next year!)
*************************************************************/

// V1 is in Alpha. Code is incomplete.


int main(void)
{
	SREG |= 10000000; //Enable global interrupts. 

	double powerout_buffer;
	uint16_t powerout = 0x0;
	uint16_t * i = 0x0;      //indexing variable
	
	for (i = 0; i < ( (uint16_t*) 1024 ) ; i = i + 2){ // We got 1K EEPROM. So for a double thats 4bytes, therefore we have 128 spots. 
													  // But we going to store as uint16 to get 512 spots. 16bits is good for mW value.
		powerout_buffer = getPower();   //load the power usage of the device in mW
		if ( powerout_buffer >= TWOE16 ){ //if this value is more than 2^16 milliwatts, theres a problem
			return 0;                         //MAX wattage of the device is far less than 65W
		}
		else{

			powerout = (uint16_t) round(powerout_buffer); //transfer the double value to a uint16_t type
		
		}

		writeEEPROM( i, powerout);   // Write this value to the EEPROM to read later.
		_delay_ms(100);				 // Delay to get a better range of values.
									 // Delay * 512 gives us the approximate sampling time in ms
	}
	
	
	return 0;
}


