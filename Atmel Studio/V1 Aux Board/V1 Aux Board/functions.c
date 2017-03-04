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
void writeEEPROM(uint16_t * addr, double power){
	
	if ( power > TWOE16 )    //if power is larger than 2^16
	{						 //just make it 0xFFFF
		power = TWOE16;
	}
	uint16_t power_word;
	power = round(power);
	power_word = (uint16_t) power;
		
	eeprom_write_word(addr, power_word);

}

//This function reads the ADC at the desired pin.
//This is how we get the current and the voltage from the 
//328p. The range is 0-1024 and the output is the ADCOut
//structure that contains 2, 8-bit numbers.
uint16_t ADCRead(uint8_t pin){

	struct ADCOut input[16]; //We're going to sample and average from 16 readings. 

	PRR &= 0b11111110; //Enable ADC Power
	ADCSRB &= 0x00; //Auto Trigger = Free Running mode
	ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE) | ( 1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // ADC Enable; Auto Trigger;
	ADMUX |= (1 << REFS0); //Set reference, AVcc														  // Interupt Enable; Freq/128 
	ADMUX |= pin; //Set ADC pin

	uint8_t i;
	for (i = 0x0; i < 16 ; i++){
	
		ADCSRA |= (1 << ADSC); //Start Conversation, 

		while( ~(ADCSRA & (1 << ADIF)) ); //Wait till conversation complete

		input[i].leftbyte = ADCL;  //Read output
		input[i].rightbyte = ADCH; //Once we read the output ADCL/ADCH
						    	//Resets
	}

	uint32_t sum = 0x0;
	for (i = 0x0; i < 15; i++)
	{
		sum = ((uint32_t) byteCombine(input[i])) + ( (uint32_t) byteCombine(input[i+1]) );  // add up all the readings
	}

	uint16_t average_reading = (uint16_t) (sum / 16);  //Find the average of the readings and return the value
	return average_reading;
}

//gets the output voltage in milliVolts
double getVoltage(void){
	
	double voltage; //initialize
												
	voltage = (double) ADCRead((uint8_t) 0x1); // Voltage input is on ADC1
											 
	voltage = voltage * 24.4141;  // Convert 0-1024 to an input voltage 0-5 then multiply by 5 since
							        //OPAMP multiplies Battery input voltage by 0.2 or 1/5
						            //This result is the Voltage in mV of the supply      (5/1024)*(5)*1000 = 24.4140625
	return voltage;
}

//gets the output current in milliAmps (same idea as getVoltage)
double getCurrent(void){
	
	double current;

	current = (double) ADCRead((uint8_t) 0x0);  //Current reading is on ADC0

	current = current * 2.4414;      // Convert 0-1024 to an input voltage 0-5
							         // Convert voltage 0-5, to the input current 
							         // across shunt to 0-2.25A, then multiply by 1000 (5/1024)*(2.25/5)*1000 = 2.44140625
	return current;
}

//Returns the power usage of the AUX Board in milliwatts
//Currently doesn't include losses in pMOSs and battery
double getPower(void){
	
	double power;
	
	power = getVoltage() * getCurrent(); //outputs in milliwatts. 
	power = power / 1000000;

	return power;
}