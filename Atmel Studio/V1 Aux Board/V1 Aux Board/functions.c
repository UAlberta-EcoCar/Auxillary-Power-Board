#include "functions.h"

//Since ADC is 10 bit, it stores its data into 2, 8-bit Registers
//Therefore we must combine these 2, 8bit numbers into a 16bit number
uint16_t byteCombine(struct ADCOut input){ //The ADCOut struct holds these 2 8bit numbers
	
	uint8_t a = 0x00;    //Move struct values into variables we can easily work with
	uint8_t b = 0x00;

	a = input.leftbyte;
	b = input.rightbyte;

	uint16_t output = 0x00;  //initialize the output
	output = output + b; // Add the high byte
	a &= 0b00000011; //only need the last 2 bits, wipe bits7-2
	
	output = output + (256 * (a & 0b00000001)); //if bit0 = 1, add 256
	output = output + (256 * (a & 0b00000010)); //if bit1 = 1, add 512

	return output;
}


//This function is used to store the power output into the 
//EEPROM of the 328p for later inspection. 
void writeEEPROM(uint16_t address, uint16_t power){
	
	eeprom_write_word( address, power);

}

//This function reads the ADC at the desired pin.
//This is how we get the current and the voltage from the 
//328p. The range is 0-1024 and the output is the ADCOut
//structure that contains 2, 8-bit numbers.
struct ADCOut ADCRead(uint8_t pin){

	struct ADCOut input;
	PRR &= 0b11111110; //Enable ADC Power
	ADCSRB &= 0x00; //Auto Trigger = Free Running mode
	ADCSRA |= 0b10100111; // ADC Enable; Auto Trigger; Freq/128
	ADMUX &= 0b01000000; //Set reference, AVcc
	ADMUX |= pin; //Set ADC pin
	ADCSRA |= 0b01000000; //Start Conversation

	while( ~(ADCSRA & 0b00010000) ); //Wait till conversation complete

	input.leftbyte = ADCL;  //Read output
	input.rightbyte = ADCH; //Once read the output ADCL/ADCH
							//Resets

	return input;
}

//gets the output voltage in milliVolts
double getVoltage(void){
	
	double voltage; //initialize
	struct ADCOut reading;  // a structure with 2, 8bit numbers 
	reading = ADCRead(0x01);  // Voltage input is on ADC1

	voltage = (double) byteCombine(reading); //Combine the 2, 8bit numbers
											 //then cast to a double
	voltage = voltage * 24.4141063  // Convert 0-1024 to an input voltage 0-5 then multiply by 5 since
							        //OPAMP multiplies Battery input voltage by 0.2 or 1/5
						            //This result is the Voltage in mV of the supply      (5/1024)*(5)*1000 = 24.4140625
	return voltage;
}

//gets the output current in milliAmps (same idea as getVoltage)
double getCurrent(void){
	
	double current;
	struct ADCOut reading;
	reading = ADCRead(0x00);  //Current reading is on ADC0

	current = (double) byteCombine(reading);
	current = current * 2.441406;    // Convert 0-1024 to an input voltage 0-5
							         // Convert voltage 0-5, to the input current 
							         // across shunt to 0-2.25A, then multiply by 1000 (5/1024)*(2.25/5)*1000 = 2.44140625
	return current;
}

//Returns the power usage of the AUX Board in milliwatts
//Currently doesn't include losses in pMOSs and battery
double getPower(void){
	
	double power;
	
	power = ( getVoltage() * getCurrent() ) / 1000000; //outputs in milliwatts. 
	
	return power;
}