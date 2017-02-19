Added a way to record battery voltage with the 328p

This involved adding an op-amp current-devider circuit. The ratio is 1/5 
This ment I was able to use the same 10K and 40K resistor from the current
measuring op-amp circuit. 

What the 1/5 ratio means is that the input voltage is devided by 5. So 25V input, which is the max possible for this board, well have an output voltage of 5V. 5V is also the maximum for the 328p's ADC. 

When measuring power output with the 328p, ensure count for the losses in the 2 pMOS, and the shunt. 

To add the power loss; Remember the 2 pMOS have a collective resistance of 2.25ohm when the 
voltage is larger than 10V. The resistance of the shunt is 0.005ohm. 

-> So you must add 2.255ohm * I^2 to the total power usage. 

