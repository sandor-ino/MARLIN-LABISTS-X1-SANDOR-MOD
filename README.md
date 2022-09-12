# Marlin-2.0.9.2 LABISTS-X1-SANDOR MOD V2
Sandor Mod V2 Modified version of MARLIN 2.0.9.2 for LABISTS X1 mini 3d printer with some changes in Marlin code, is possible to EASYTHREED X1, K1, SONDORI PICO printer with ET4000 V2 card

VIDEO TEST LINK:
https://youtu.be/KjyCzkallvk

SANDOR MOD V2 11_2021
FAN, BED, LCD + ENCODER, ARDUINO, RGB LED

CUSTOM BUTTONS FUNCTIONS

- HOME BUTTON
- Pressed for a short time:
Z axis in Home position and deactivates the Motor Stepper X and Y (manual flat calibration)
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
During printing by pressing + or - change RGB LED effects
There are 8 possibilities of choice including off, modifying RGB.Lib library desired effects are obtained 

![alt text](https://github.com/sandor-ino/MARLIN-2.0.8-LABISTS-X1-SANDOR-MOD/blob/SANDOR-MOD-V2/PINOUT%20sandor%20mod%20v2.jpg)
