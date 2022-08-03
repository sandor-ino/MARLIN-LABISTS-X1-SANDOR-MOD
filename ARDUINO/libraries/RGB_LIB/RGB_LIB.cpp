/*
  SANDOR MOD V2 11_2021 - LABISTS X1
  
  RGB_LIB.cpp - Libreria di esempio per gestire
  l'accensione, lo spegnimento, il lampeggio
  e la dissolvenza incrociata di un LED RGB.

*/

#include "RGB_LIB.h" // dichiarazione della classe

RGB_LIB::RGB_LIB(int pinR, int pinG, int pinB, int mode)
{
	_pinR = pinR;
	_pinG = pinG;
	_pinB = pinB;
	pinMode(_pinR, OUTPUT);
	pinMode(_pinG, OUTPUT);
	pinMode(_pinB, OUTPUT);
	_modo = mode;
}

void RGB_LIB::setColor(int CR, int CG, int CB)
{
	_CR = CR;
	_CG = CG;
	_CB = CB;
	if (_modo == 0)
	{
		analogWrite(_pinR, 255 - _CR);
		analogWrite(_pinG, 255 - _CG);
		analogWrite(_pinB, 255 - _CB);
	}
	else if (_modo == 1)
	{
		analogWrite(_pinR, _CR);
		analogWrite(_pinG, _CG);
		analogWrite(_pinB, _CB);
	}
}

void RGB_LIB::defaultColor(String colorname)
{
	_colorname = colorname;
	if (_colorname == "white")
	{
		setColor(255, 255, 255);
	}
	else if (_colorname == "red")
	{
		setColor(255, 0, 0);
	}
	else if (_colorname == "green")
	{
		setColor(0, 255, 0);
	}
	else if (_colorname == "blue")
	{
		setColor(0, 0, 255);
	}
	else if (_colorname == "yellow")
	{
		setColor(255, 255, 0);
	}
	else if (_colorname == "orange")
	{
		setColor(255, 150, 0);
	}
	else if (_colorname == "violet")
	{
		setColor(150, 0, 255);
	}
	else if (_colorname == "turquoise")
	{
		setColor(0, 255, 220);
	}
	else if (_colorname == "grey")
	{
		setColor(70, 70, 70);
	}
	else if (_colorname == "maroon")
	{
		setColor(176, 54, 72);
	}
	else if (_colorname == "fuchsia")
	{
		setColor(255, 0, 255);
	}
	else
	{
		setColor(0, 0, 0);
	}
}

void RGB_LIB::fadeRainbow(void)
{

	setColor(_CR, _CG, _CB);
	delay(random(20));

	if (color == 0)
	{
		if (_CR >= 0 && _CR < 255)
		{
			_CR += 1;
		}
		else
		{
			delay(25); //ROSSO
			color += 1;
		}
	}
	if (color == 1)
	{
		if (_CG >= 0 && _CG < 128)
		{
			_CG += 1;
		}
		else
		{
			delay(50); //arancio
			color += 1;
		}
	}
	else if (color == 2)
	{
		if (_CG >= 128 && _CG < 255)
		{
			_CG += 1;
		}
		else
		{
			delay(50); //giallo
			color += 1;
		}
	}
	else if (color == 3)
	{
		if (_CR > 128 && _CR <= 255)
		{
			_CR -= 1;
		}
		else
		{
			delay(5); //verde 1
			color += 1;
		}
	}
	else if (color == 4)
	{
		if (_CR > 0 && _CR <= 128)
		{
			_CR -= 1;
		}
		else
		{
			delay(25); //verde
			color += 1;
		}
	}
	else if (color == 5)
	{
		if (_CB >= 0 && _CB < 128)
		{
			_CB += 1;
		}
		else
		{
			delay(5); //verde 2
			color += 1;
		}
	}
	else if (color == 6)
	{
		if (_CB >= 128 && _CB < 255)
		{
			_CB += 1;
		}
		else
		{
			delay(5); //azzurro 1
			color += 1;
		}
	}
	else if (color == 7)
	{
		if (_CG > 128 && _CG <= 255)
		{
			_CG -= 1;
		}
		else
		{
			delay(5); //azzurro 2
			color += 1;
		}
	}
	else if (color == 8)
	{
		if (_CG > 0 && _CG <= 128)
		{
			_CG -= 1;
		}
		else
		{
			delay(50); //blu
			color += 1;
		}
	}
	else if (color == 9)
	{
		if (_CR >= 0 && _CR < 128)
		{
			_CR += 1;
		}
		else
		{
			delay(25); //indaco
			color += 1;
		}
	}
	else if (color == 10)
	{
		if (_CR >= 128 && _CR < 255)
		{
			_CR += 1;
		}
		else
		{
			delay(25); //viola
			color += 1;
		}
	}
	else if (color == 11)
	{
		if (_CB > 128 && _CB <= 255)
		{
			_CB -= 1;
		}
		else
		{
			delay(5); //viola 1
			color += 1;
		}
	}
	else if (color == 12)
	{
		if (_CB > 0 && _CB <= 128)
		{
			_CB -= 1;
		}
		else
		{
			delay(25); //rosso
			color += 1;
		}
	}
	else if (color == 13)
	{
		color = 0;
	}
}

void RGB_LIB::fade(String colorRGB)
{
	_colorLED = colorRGB;
	if (timingAll == false)
	{
		prevMillisAll = millis() + random(10, 20);
		timingAll = true;
	}
	if (prevMillisAll <= millis())
	{
		setColor(_CR, _CG, _CB);
		timingAll = false;

		if (_colorLED == "R" || _colorLED == "RG" || _colorLED == "RB" || _colorLED == "RGB")
		{

			/// random fade red
			if (_CR > 0 && _CR < 255)
			{
				if (fadeupR == true)
				{
					_CR += 1;
				}
				else
				{
					_CR -= 1;
				}
			}
			else if (_CR == 0)
			{
				if (timingR == false)
				{
					prevMillisR = millis() + random(500, 2000);
					timingR = true;
				}

				if (prevMillisR <= millis())
				{
					_CR += 1;
					fadeupR = true;
					timingR = false;
				}
			}
			else if (_CR == 255)
			{
				if (timingR == false)
				{
					prevMillisR = millis() + random(500, 2000);
					timingR = true;
				}
				if (prevMillisR <= millis())
				{
					_CR -= 1;
					fadeupR = false;
					timingR = false;
				}
			}
		}
		if (_colorLED == "G" || _colorLED == "RG" || _colorLED == "GB" || _colorLED == "RGB")
		{

			/// random fade green
			if (_CG > 0 && _CG < 255)
			{
				if (fadeupG == true)
				{
					_CG += 1;
				}
				else
				{

					_CG -= 1;
				}
			}
			else if (_CG == 0)
			{

				if (timingG == false)
				{
					prevMillisG = millis() + random(500, 2000);
					timingG = true;
				}

				if (prevMillisG <= millis())
				{
					_CG += 1;
					fadeupG = true;
					timingG = false;
				}
			}
			else if (_CG == 255)
			{
				if (timingG == false)
				{
					prevMillisG = millis() + random(500, 2000);
					timingG = true;
				}
				if (prevMillisG <= millis())
				{
					_CG -= 1;
					fadeupG = false;
					timingG = false;
				}
			}
		}
		if (_colorLED == "B" || _colorLED == "GB" || _colorLED == "RB" || _colorLED == "RGB")
		{
			/// random fade blue
			if (_CB > 0 && _CB < 255)
			{
				if (fadeupB == true)
				{
					_CB += 1;
				}
				else
				{

					_CB -= 1;
				}
			}
			else if (_CB == 0)
			{
				if (timingB == false)
				{
					prevMillisB = millis() + random(500, 2000);
					timingB = true;
				}

				if (prevMillisB <= millis())
				{
					_CB += 1;
					fadeupB = true;
					timingB = false;
				}
			}
			else if (_CB == 255)
			{
				if (timingB == false)
				{
					prevMillisB = millis() + random(500, 2000);
					timingB = true;
				}
				if (prevMillisB <= millis())
				{
					_CB -= 1;
					fadeupB = false;
					timingB = false;
				}
			}
		}
	}
}

void RGB_LIB::pulse(String colorRGB)
{
	_colorLED = colorRGB;
	if (timingAll == false)
	{
		prevMillisAll = millis() + 10;
		timingAll = true;
	}
	if (prevMillisAll <= millis())
	{
		setColor(_CR, _CG, _CB);
		timingAll = false;

		if (_colorLED == "R" )
		{

			/// Pulse red
			if (_CR > 20 && _CR < 255)
			{
				if (fadeupR == true)
				{
					_CR += 1;
				}
				else
				{
					_CR -= 1;
				}
			}
			else if (_CR <= 20)
			{
				if (timingR == false)
				{
					prevMillisR = millis() + 250;
					timingR = true;
					
				}

				if (prevMillisR <= millis())
				{
					_CR = 21;
					fadeupR = true;
					timingR = false;
				}
			}
			else if (_CR == 255)
			{
				if (timingR == false)
				{
					prevMillisR = millis() + 150;
					timingR = true;
				
				}
				if (prevMillisR <= millis())
				{
					_CR -= 1;
					fadeupR = false;
					timingR = false;
				}
			}
		}
		else if (_colorLED == "G" )
		{

			/// Pulse green
			if (_CG > 20 && _CG < 255)
			{
				if (fadeupG == true)
				{
					_CG += 1;
				}
				else
				{

					_CG -= 1;
				}
			}
			else if (_CG <= 20)
			{

				if (timingG == false)
				{
					prevMillisG = millis() + 250;
					timingG = true;
				}

				if (prevMillisG <= millis())
				{
					_CG = 21;
					fadeupG = true;
					timingG = false;
				}
			}
			else if (_CG == 255)
			{
				if (timingG == false)
				{
					prevMillisG = millis() + 150;
					timingG = true;
				}
				if (prevMillisG <= millis())
				{
					_CG -= 1;
					fadeupG = false;
					timingG = false;
				}
			}
		}
		else if (_colorLED == "B")
		{
			/// Pulse blue
			if (_CB > 20 && _CB < 255)
			{
				if (fadeupB == true)
				{
					_CB += 1;
				}
				else
				{
					_CB -= 1;
				}
			}
			else if (_CB <= 20)
			{
				if (timingB == false)
				{
					prevMillisB = millis() + 250;
					timingB = true;
				}

				if (prevMillisB <= millis())
				{
					_CB = 21;
					fadeupB = true;
					timingB = false;
				}
			}
			else if (_CB == 255)
			{
				if (timingB == false)
				{
					prevMillisB = millis() + 150;
					timingB = true;
				}
				if (prevMillisB <= millis())
				{
					_CB -= 1;
					fadeupB = false;
					timingB = false;
				}
			}
		}
	}
}

void RGB_LIB::blink(String colorname)
{
	_colorname = colorname;
	if (timingAll == false)
	{
		prevMillisAll = millis();
		
		
		timingAll = true;
	}
	if (prevMillisAll + 150 <= millis())
	{
		defaultColor(_colorname);
			
	}
   if (prevMillisAll + 300 <= millis())
	{
		setColor(0, 0, 0);
		timingAll = false;
	
	}
}

