This is the EAGLE schematics and board files for ECOCAR's AUX Power Board. 

Assigned specs:
-a couple of output rj11 ports.
-5V @ 1A out
-12 @ 1A out
-Data log the power usage onto an LCD.
-A way to program and debug the ATmega328p
-Input is going to be a 16V battery that can range 7-18V.

Versions 1,2,3,3.1,3.2,3.3,3.4,4.0 were developed by Koltin Kosik-Harvey. Anyone on the ECOCAR team has
rights to use these version files as they wish.

Notes:
V1   - Build a schematic for the device (roll back point)
V2   - Building the board. 
V3   - Attempt to shrink V2 by about 40%. 
V3.1 - Removed an inefficiency. Effectively doubling current output by shorting the
       5V regulator input to the battery. See README in V3.1 folder. 
V3.2 - Replaced diode reverse current protection with 2 pMOS in parallel.
V3.3 - Added a way to measure the voltage of the battery.
V3.4 - Connected op-amps to a 12V source to make them more linear
V4   - If V4 were to be created, it would use a smaller MCU. The smaller MCU well allow for a 
       smaller board and allow for extras like an real-time OLED power output display with historigram.
       Prospect MCU is the 328p. Prospect display is the Kuman 0.96 Inch Blue IIC 128x64. 
       The MCU will be a surface mount.
     - Another thought is to have stacked RJ11 Ports or to just use 2 ports, however the 
       3 ports is rather handy. Maybe 2 double stacked RJ11s? 
     - For 12V regulation also be looking into SEPTIC regulation so we can use a voltage near Vin. 
       The 12V regulator is host to a lot of resistive loss, this is an issue with 3.4
     - Need the op-amps connected to a +/- 12/15 V supply for linearity in the region 0-5V.

- More Details in the README in the folder of the specific version. 

All parts choosen to be used are in the schematics. 
Their datasheets are a google away online. 

--> Note, I reused packages due to lazyness. Ensure to order the NAMES of the parts. For example
the 12V regulator (MIC2940A-12WT, V3.1) is using the Device, "7805TCV(78*)". This is done 
to get the TO-220 package.

--> In the comming months, this repo is going to be purged with only the necessary files. 
    All that would be left would be the current version board files(V3.4) and eagle libraries. 
