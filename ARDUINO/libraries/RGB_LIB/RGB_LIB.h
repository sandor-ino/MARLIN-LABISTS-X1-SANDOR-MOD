/*
  SANDOR MOD V2 11_2021 - LABISTS X1
  
  RGB_LIB.h - Libreria di esempio per gestire
  l'accensione, lo spegnimento, il lampeggio
  e la dissolvenza incrociata di un LED RGB.

*/


#ifndef RGB_LIB_H
#define RGB_LIB_H

#include "Arduino.h"

class RGB_LIB
{
private:

	int _pinR;
	int _pinG;
	int _pinB;
	int _modo;

	int _CR;
	int _CG;
	int _CB;

	int color = 0;
	bool fadeupR = true;
	bool fadeupG = true;
	bool fadeupB = true;

	unsigned long prevMillisR = 0;
	unsigned long prevMillisG = 0;
	unsigned long prevMillisB = 0;
	unsigned long prevMillisAll = 0;
	bool timingR = false;
	bool timingG = false;
	bool timingB = false;
	bool timingAll = false;

	String _colorname;
	String _colorLED;
	

public:
	RGB_LIB(int pinR, int pinG, int pinB, int modo);
	void setColor(int CR, int CG, int CB);
	void defaultColor(String colorname);
	void fade(String colorRGB);
	void pulse(String colorRGB);
	void fadeRainbow(void);
	void blink(String colorname);
};

#endif