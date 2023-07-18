![](https://media.giphy.com/media/NTur7XlVDUdqM/giphy.gif)

# Microcontroller 

Gruber & Vidmar

## Assignment 6:

	pwm auslesen  OK
	rpm auslesen  OK
	pwm setzen OK
	realese SPI OK
	
Frame:
transmit:
	MOSI: 	[key][key][key][key]
	or	   	[key][key][value][value]
response:
	MISO: 	[key][key][value][value][key][key]


INFO:------------------------------------------------------
## Hardware LED-Test on Raspberry Pi 4
	
- `sudo gpio mode 4 output`
- `sudo gpio write 4 0`
- `sudo gpio write 4 1`

## Compile and start Program on Raspberry Pi 4

- `make` hello-led-bar.rpi
- ./hello-led-bar.rpi



