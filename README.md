# Marlin-bugfix-2.1.X LABISTS-X1-SANDOR MOD V3

Custom firmware Mod V3 MARLIN bugfix-2.1.X for LABISTS X1 mini 3d printer  with some changes in Malin code,  is possible to  EASYTHREED X1, K1 and SONDORI PICO printer with  ET4000 V2 card

VIDEO TEST LINK: https://youtu.be/csIqN8K5dlU
---------------

NEW VERSION V3: WiFi works with ESP01S and ESP3D Firmware, Led Lighting Object in Print, Automatic ON/OFF fan hotend box (normally always on)

NOTE:
- !!! Adjust 3.3V converter DCDC before connecting ESP01S !!!
- first time connect to ESP01 network and configure the GUI, the multilingual files are in folder .../Languages/.../ (Index.html) - https://github.com/luc-github/ESP3D/blob/2.1.x/README.md
- The Repetier-Host + Prusaslicer pairing works well

SANDOR MOD V3 9_2022
FAN, BED, LCD + ENCODER, ARDUINO, RGB LED, 4 Darlington transistor, dcdc converter, ESP01S_1M

CUSTOM BUTTON FUNCTION

- HOME BUTTON
(1)- Pressed for a short time:
Z axis in Home position and deactivates the Motor Stepper X and Y (manual flat calibration)
(2)- Long pressed:
Reset Arduino controls (to optimize) 
- MINUS BUTTON
After heating extracts filament and automatically turn off extruder
- PLUS BUTTON
After heating extrudation 20 mm of filament, pressing again repeats the thing. Press Home button to turn off extruder
Note: extruder turns off automatically after 3 minutes of inactivity.
- PLAY BUTTON
(1)- Pressed for a short time:
All X Y Z axles in Home position
If all axes are in Home moves the Z axis of 10 mm
Note: The program does not allow to exceed 90 mm, if it moves down for 10 mm
(2)- Long pressed:
Start Calibration procedure with placement of bed automatic with 5 points X - Y.
Press normally by next step 1 - 80 x 80, 2 - 80 x 20, 3 - 20 x 80, 4 - 20 x 20, 5 - 50 x 50
Complete procedure with all axes in Home
During procedure if you press long, you stop sequence, and axes go to home, 
use function only to rectify manual calibration to avoid of ruining bed

special function:
- During printing by pressing + or - change RGB LED effect
There are 8 possibilities of choice including off, You can change RGB.Lib library for different effects
- button play double click to turn on/off LED hotend
- button home long press restart arduino (experimental)
- During printing LED buttons turn off in sequence 4321
- RGB LED responds to axes movement with green color, red for Hotend, blue for bed
- Files transfer works but it is slow only type 8.3 files can be used, during the process all LEDs flash


![alt text](https://github.com/sandor-ino/MARLIN-2.0.8-LABISTS-X1-SANDOR-MOD/blob/SANDOR-MOD-V3/PINOUT%20sandor%20mod%20v3.jpg)
![alt text](https://github.com/sandor-ino/MARLIN-2.0.8-LABISTS-X1-SANDOR-MOD/blob/SANDOR-MOD-V3/ESP01S%20SETUP%20PINOUT.jpg)

