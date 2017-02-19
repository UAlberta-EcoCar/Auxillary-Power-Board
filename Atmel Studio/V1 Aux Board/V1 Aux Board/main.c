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
	double powerout_buffer;
	uint16_t powerout;
	uint16_t i;      //indexing variable
	uint16_t eeprom_address = ; //address of the eeprom (might make constant)
	
	for (i = 0; i < 127 ; i = i + 8){        // We got 1K EEPROM. So for a double thats 8bytes, therefore we have 128 spots. might use ints in the future for double the space.
		powerout_buffer = getPower();   //load the power usage of the device
		if ( powerout_buffer >= pow(2, 16) ){ //if this value is more than 2^16 milliwatts, theres a problem
			return 0;                         //MAX wattage of the device is far less than 65W
		}
		else{
			powerout = (uint16_t) ((int) powerout_buffer); //transfer the double value to a uint16_t type
		}
		writeEEPROM(i, powerout);   // Write this value to the EEPROM to read later PLACEHOLDER
		_delay_ms(100);                      // Delay to get a better range of values.
	}
	
	
	return 0;
}


