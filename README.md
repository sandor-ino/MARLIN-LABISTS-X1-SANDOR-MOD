# MARLIN-2.0.8-LABISTS-X1-SANDOR-MOD V1.1
# Functions test - https://www.youtube.com/watch?v=PBdJpTGQPfE

NEW VERSION V1.1: Update notes in code and more

Sandor Mod V1.1 Modified version of MARLIN 2.0.8 for LABISTS X1 mini 3d printer 
with some changes in Marlin code, is possible to EASYTHREED X1, K1, SONDORI PICO printer 
with ET4000 V2 card

SANDOR MOD 5_2021 FAN, BED, LCD + ENCODER, CUSTOM BUTTON FUNCTION

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

note:

    A minimum 60 w power supply is required if the hot bed is installed

![alt text](https://github.com/sandor-ino/MARLIN-2.0.8-LABISTS-X1-SANDOR-MOD/blob/SANDOR-MOD-V1.1/w_PINOUT%20sandor%20mod%20V1.jpg)
