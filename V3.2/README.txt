Did some reading on reverse current protection and found the diode short between
+ and gnd might not be good enough since it takes a bit to blow the fuse. 
Also its annoying that the fuse blows. 

Solution was to place a well selected pMOS in its place. I selected the FDS6681Z,
and placed 2 of them in parallel in place of the diode. 

The Rds on is 4.5mohm so 2 of them would have 2.25mohm. This results in a power loss 
of (2.25A max) about 15mW. But we wont be using 2.25A, a realistic current is about 
1A. so thats around 2.5mW.

-Koltin Kosik-Harvey