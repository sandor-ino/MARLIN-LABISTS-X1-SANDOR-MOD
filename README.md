# Marlin-2.0.9.2 LABISTS-X1-SANDOR MOD V2
 Custom firmware Mod V2 MARLIN 2.0.9.2 for LABISTS X1 mini 3d printer  with some changes in Malin code,  is possible to  EASYTHREED X1, K1 and SONDORI PICO printer with  ET4000 V2 card
VIDEO TEST LINK:
https://youtu.be/KjyCzkallvk

SANDOR MOD V2 11_2021
FAN, BED, LCD + ENCODER, ARDUINO, RGB LED
CUSTOM BUTTON FUNCTION

- HOME BUTTON
1-Pressed for a short time:
Z axis in the Home position and deactivates the Motor Stepper X and Y (manual flat calibration)
2-Long pressed:
Reset Arduino controls (to optimize) 
- MINUS BUTTON
After heating extracts the filament and automatically turn off the extruder
- PLUS BUTTON
After heating extrudation 20 mm of filament, pressing again repeats the thing. Press the Home button to turn off the extruder
Note: the extruder turns off automatically after 3 minutes of inactivity.
- PLAY BUTTON
1-Pressed for a short time:
All X Y Z axles in Home position
If all the axes are in Home moves the Z axis of 10 mm
Note: The program does not allow to exceed 90 mm, if it moves down for 10 mm
2-Long pressed:
Start Calibration procedure with placement of the bed automatic with 5 points X - Y.
Press normally by next step 1 - 80 x 80, 2 - 80 x 20, 3 - 20 x 80, 4 - 20 x 20, 5 - 50 x 50
Complete the procedure with all the axes in Home
During the procedure if you press long, you stop the sequence, and the axes go to the home, 
use the function only to rectify manual calibration to avoid of ruining the bed

special function:
During printing by pressing the + or - change the RGB LED effect
There are 8 possibilities of choice including off, modifying the RGB.Lib library the desired effects are obtained 
