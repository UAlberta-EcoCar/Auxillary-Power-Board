#include "historigram.h"

Adafruit_SSD1306 display(OLED_RESET);
volatile uint16_t ADC_OUT = 0;
volatile uint8_t horizontal_display_location[127];
volatile float current_value;
volatile double voltage;
volatile int i;
volatile double sum;

void historigram_initialize(void){
	
	Serial.begin(9600);

	// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
	// init done
	display.clearDisplay();
	sum = 0;
	i = 0;
		
	for( i = 0;  i < 127 ; i++ ){
			
		horizontal_display_location[i] = 63;
			
	}
		
	current_value = 63;
	
}

void run_historigram(void){
	
		ADC_OUT = ADCRead(0);
		voltage = ADC_OUT*5;
		voltage = voltage/1023;
		current_value = (1023 - ADC_OUT) * 0.061584;
		
		//Shifts the graph over to make it real time
		//The black line clears the old value in that position
		for(i = 0; i < 126 ; i++){
			
			if ( horizontal_display_location[i] != horizontal_display_location[i+1] ){
				horizontal_display_location[i] = horizontal_display_location[i+1];
				display.drawLine(i, 0, i, 63, BLACK);
			}
			
		}
		if ( horizontal_display_location[126] != ((uint8_t) round(current_value)) ){
			horizontal_display_location[126] = (uint8_t) round(current_value);
			display.drawLine(126, 0, 126, 63, BLACK);
		}
		
		//display the output values onto the graph
		for(i=126; i >= 0 ; i--){
			
			display.drawPixel(i, horizontal_display_location[i], WHITE);
			
		}
		display.drawLine(127, 0, 127, 63, BLACK);
		display.drawPixel(127, (uint8_t) round(current_value) , WHITE);
		
		//Print output voltage
		display.setTextColor(BLACK, WHITE);
		display.setTextSize(1);
		display.setCursor(0,0);
		display.println("VOLTAGE");
		display.println(voltage);
		
		//Averaging the values of the graph
		sum = 0;
		for(i=0; i <= 126; i++){
			
			sum += horizontal_display_location[i];
			
		}
		sum += (uint8_t) round(current_value);
		sum = sum/128;
		sum = 63 - sum;
		sum = sum * 5;
		sum = sum / 63;
		
		//Print Average Values
		display.println("AVERAGE");
		display.println(sum);
		
		//Draws a Scale
		display.drawLine(100, 0, 100, 63, WHITE);
		//5V tick
		display.drawLine(99, 0, 101, 0, WHITE);
		display.drawChar(91, 0, '5', WHITE, BLACK, 1);
		//4V tick
		display.drawLine(99, 13, 101, 13, WHITE);
		display.drawChar(91, 13, '4', WHITE, BLACK, 1);		
		//3V tick
		display.drawLine(99, 25, 101, 25, WHITE);
		display.drawChar(91, 25, '3', WHITE, BLACK, 1);
		//2V tick
		display.drawLine(99, 38, 101, 38, WHITE);
		display.drawChar(91, 38, '2', WHITE, BLACK, 1);
		//1V tick
		display.drawLine(99, 50, 101, 50, WHITE);
		display.drawChar(91, 50, '1', WHITE, BLACK, 1);
		//0V tick
		display.drawLine(99, 63, 101, 63, WHITE);
		
		display.display();
	
}