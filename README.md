# Headwaters Details
## Theory of Operation
This exhibit teaches about the isotope levels in water as it travels from the mountains to a low elevation.

The user can use the physical dial between normal climate, drought climate, and high snowpack climates. The colors of the streams and river sections (LEDs) change based on the amount of water that flows during that climate. Each button represents a specific "testing site" in a stream or river, including the elevation details and the isotope count for that climate at that area. When the button is pushed, the information is printed on a sheet of receipt paper.

When first turned on, the dial needs to be moved to callibrate the settings. Otherwise the data that is printed and the colors of the LED streams / rivers will not be accurate. It doesn't matter where it is moved to, it just needs to be changed from the initial posiiton that it is at when first turned on.

## Updating software

The software is built using platform.io in Visual Studio Code. By cloning the GitHub locally, you can open the project in Visual Studio Code with platform.io. Then you can edit the header files and main file as needed.

## Project File Organization

	src : source code
	fusion : pdf of schematic
	readme.md : basic project info (this file that you are reading)
	
	other directories are used by platformio and vscode

#### Hardware

[A detailed list of all of the hardware used and the quantity of each. Go through each Phoenix connector first, specified by pin, then create a list of the rest of the hardware components.]

** NEEDS TO BE UPDATED **

EXAMPLE:
**Phoenix connectors:**

2-pin: (4 qty)

	1. 24V
	2. Safety Switch
	3. Accel Sensor (1 pair)
	
3-pin: (3 qty)

	1. IR In
	2. Reed In
	3. 12v In
	
4-pin: (2 qty)
  1. Buttons
	
6-pin: (1 qty)

	1.Lock Light
	2.Unlock Light

Various Components:

	3 mosfets (SMD 7460AAW44K)
	3 10K SMS Resistors
	32U4 - 5v itsyBitsy
	Stepper Motor
	Stepper Driver
	IR Sensor (CPB765WZ)
	Happ Switch
	Reed Switch
	Maglock
	24V PSU
	12V PSU
	5V across USB

The photo below of the exhibit is not of the final exhibit. In the final exhibit, the buttons are labeled for what section of the streams / river they represent, and there are labels to identify the elevations.

[Photo of exhibit.](https://github.com/user-attachments/assets/25026b6d-b528-4883-bf35-7eef0286bde2)
