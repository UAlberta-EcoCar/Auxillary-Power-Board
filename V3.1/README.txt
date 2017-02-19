Small but significant change.

Shorting the 5V regulator's input to the output of the fuse. 

Since the 12V regulator is linear, its not effcient to drop those 4-5v resistively.
5Vx1A = 5W peak waste heat dissipation. Yes thats 5W of heat.

Instead the switching regulator well handle the full 10-12v drop. This is ideal for a 5V reg.
Being that the PWM well be at ~50% pulse width. When dropping from 12V to 5V (7V) thats a ratio of 
5/7. 

The PWM ratio of 5/7 is cutting close to edge of PWM efficiency. 

With this change we'll also see an increase in output power capabilities. This is because it's 
easy to increase the size of the input trace to account for a 2A load. This means we can get a
max of 1A from the 12V and 1A from the 5V. This is 17W continuous in total. Capacitors inside
well be able to push out a tad more current to effectively have a temporary "boost" current of
around 0.5A. This means we'll get a temporary (very temporary) power output of 25W. 


TL:DR 
An inefficient combination of 5/7 PWM ratio and a 5W linear resistive loss requires attention.
In version 3.1 we're shorting the 5V regulator input directly to the output of the fuze. This change
also potentially raises output wattage capabilites if the 5V and 12V are used to their potential.

-Koltin Kosik-Harvey
