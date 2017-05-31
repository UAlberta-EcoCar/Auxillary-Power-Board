#include "ADCRead.h"
#include <util/delay.h>

//Adds a basic low pass filter to the ADC input
#define number_samples 16  //Number of samples the ADC will take

/*
***************************************************************

ADCRead( pin ) takes in a uint8 which is the pin number of the 
ADC pin you want to read from.

***************************************************************
*/

uint16_t ADCRead(uint8_t pin){
	
	//Initialization of required varibles.
	uint16_t input = 0; //We're going to sample and average from "number_sample" readings. 
	uint32_t sum = 0; //The sum of all samples.
	uint16_t average = 0; // the average of all the samples
	uint16_t i; //This variable is going to be used as a counter in the 'for' loop
	
	//ADC Settings
	ADCSRB &= 0x00; //Free Running mode (Triggering Disabled in ADCSRA)
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);// ADC Enable; Interupt Disable; Freq/128
	ADMUX &= ~((1 << REFS0) | (1 << REFS1)); //Set AREF as reference	  	
	ADMUX &= 0b11110000;  //Reset ADC MUX Select
	ADMUX |= pin;  //Set input pin
	
	// This loop is going to sample the ADC 'number_samples' times. Adding each value to 'sum'
	for(i = 0; i < number_samples; i++) {
		
		//Setup Conversation
		ADCSRA |= (1 << ADSC); //Start Conversation
		while( (ADCSRA & (1 << ADSC)) ); //Wait till conversation complete ( ADSC == 0 )
		ADCSRA |= (1 << ADIF);   // Clear ADC Interrupt Flag
		
		//Reading and logging the input for averaging
		input = ADC; //Read the ADC
		sum = sum + input;  // Add this value to the sum of the samples to be averaged later
		
	}
	
	//Find the average of all the samples
	average = (uint16_t) (sum / number_samples);  
		
	return average;
}

