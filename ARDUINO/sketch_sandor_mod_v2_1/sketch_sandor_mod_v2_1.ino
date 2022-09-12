/// sketch arduino - SANDOR MOD V2.1 9_2022 - LABISTS X1

#ifndef riferimenti
#include <ezOutput.h>
#include <OneButton.h>
#include <RGB_LIB.h> // libreria personalizzata
#include <Wire.h>
#include <avr/wdt.h>

RGB_LIB RGB_LED(3, 5, 6, 0);

ezOutput HOME_LED(14);
ezOutput MINUS_LED(15);
ezOutput PLUS_LED(16);
ezOutput PLAY_LED(17);

OneButton HOME_BUT(7, true);
OneButton MINUS_BUT(8, true);
OneButton PLUS_BUT(9, true);
OneButton PLAY_BUT(10, true);

volatile byte arduino_event = 0;
volatile byte marlin_event = 0;
int stileRGB = 1;

#endif // riferimenti
void setup()
{
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  HOME_BUT.attachClick(homeClick);
  HOME_BUT.attachLongPressStart(homeClick_longPress);
  HOME_BUT.attachDoubleClick(homeClick_DoubleClick);
  MINUS_BUT.attachClick(minusClick);
  PLUS_BUT.attachClick(plusClick);
  PLAY_BUT.attachClick(playClick);
  PLAY_BUT.attachLongPressStart(playClick_longPress);

#ifndef intro
  int intro = 0;
  HOME_LED.high();
  MINUS_LED.high();
  PLUS_LED.high();
  PLAY_LED.high();
  RGB_LED.setColor(0, 0, 0);
  while (intro < 4)
  {
    /// andata
    HOME_LED.low();
    delay(200);
    HOME_LED.high();

    MINUS_LED.low();
    delay(200);
    MINUS_LED.high();

    PLUS_LED.low();
    delay(200);
    PLUS_LED.high();

    PLAY_LED.low();
    delay(200);
    PLAY_LED.high();

    // ritorno
    PLUS_LED.low();
    delay(200);
    PLUS_LED.high();

    MINUS_LED.low();
    delay(200);
    MINUS_LED.high();

    switch (intro)
    {
    case 0:
      RGB_LED.defaultColor("red");
      break;
    case 1:
      RGB_LED.defaultColor("green");
      break;
    case 2:
      RGB_LED.defaultColor("blue");
      break;
    case 3:
      HOME_LED.low();
      delay(200);
      HOME_LED.high();
      RGB_LED.setColor(0, 0, 0);
      break;
    default:
      break;
    }

    intro++;
  }
#endif         // intro
  wdt_reset(); // restart arduino setup()
}

void requestEvent() // risponde a richiesta da marlin
{
  Wire.write(arduino_event);
}

void receiveEvent(int howMany) // riceve stato da marlin
{
  while (Wire.available())
  {
    marlin_event = Wire.read(); /// riceve evento
  }
  if (marlin_event == 0 || marlin_event == 200 || marlin_event == 201 || marlin_event == 202 || marlin_event == 203 || marlin_event == 205 || marlin_event == 210 || marlin_event == 220) // in stampa
  {
    arduino_event = marlin_event;
  }
  else if (marlin_event == 35) // estrude nuovamente
  {
    arduino_event = 30;
  }
  else if (arduino_event == 50 || marlin_event == 42) /// avvia livellamento piatto
  {
    arduino_event = 40;
  }
}

void homeClick() //  comando Z-HOME, annulla comando estrusione (plus)
{
  if (arduino_event != 0 && arduino_event != 20 && arduino_event != 30)
    return;

  if (marlin_event == 20 || marlin_event == 30 || marlin_event == 33 || marlin_event == 103 || marlin_event == 104) // spegne e raffredda
  {
    arduino_event = 0;
  }
  else
  {
    arduino_event = 10;
  }
}

void homeClick_longPress() // annulla tutti comandi da implementare
{
  wdt_enable(WDTO_30MS);
}
void homeClick_DoubleClick() // ??? DA IMPLEMENTARE
{
}

void minusClick() // comando espelle filamento, cambia effetto RGB LED in stampa
{
  if (arduino_event != 0 && arduino_event != 20 && arduino_event != 200 && arduino_event != 201 && arduino_event != 202 && arduino_event != 203)
    return;

  switch (marlin_event) // avvia funzione carica filamento
  {
  case 0: // avvia funzione riscadamento
    arduino_event = 20;
    break;
  case 20: // in riscaldamento sepegne annulla
    arduino_event = 0;
    break;

  default:
    break;
  }
  if (arduino_event == 200 || arduino_event == 201 || arduino_event == 202 || arduino_event == 203) /// cambia effetto RGB in stampa
  {
    if (stileRGB >= 1 && stileRGB <= 8)
    {
      RGB_LED.setColor(0, 0, 0);
      stileRGB -= 1;
    }
    else
    {
      RGB_LED.setColor(0, 0, 0);
      stileRGB = 8;
    }
  }
}

void plusClick() // comando estrudi filamento, cambia effetto RGB LED in stampa
{
  if (arduino_event != 0 && arduino_event != 30 && arduino_event != 200 && arduino_event != 201 && arduino_event != 202 && arduino_event != 203)
    return;

  switch (marlin_event) // avvia funzione carica filamento
  {
  case 0: // avvia funzione riscadamento
    arduino_event = 30;
    break;
  case 30: // in riscaldamento sepegne annulla
    arduino_event = 0;
    break;
  case 33: // riscaldato ripete estrusione
    arduino_event = 35;
    break;

  default:
    break;
  }

  if (arduino_event == 200 || arduino_event == 201 || arduino_event == 202 || arduino_event == 203) /// cambia effetto RGB in stampa
  {
    if (stileRGB >= 1 && stileRGB <= 8)
    {
      RGB_LED.setColor(0, 0, 0);
      stileRGB += 1;
    }
    else
    {
      RGB_LED.setColor(0, 0, 0);
      stileRGB = 1;
    }
  }
}

void playClick() // comando XYZ-HOME, comando Z + 10 mm, punto successiovo in livellamento
{
  if (arduino_event != 0 && arduino_event != 40)
    return;
  if (marlin_event == 42)
  {
    arduino_event = 45; // nuovo punto livellamento piatto
  }
  else
  {
    arduino_event = 40; // comando XYZ-HOME, comando Z + 10 mm
  }
}

void playClick_longPress() /// avvio funzione livellamento piatto, annulla funzione livellamento piatto
{
  if (arduino_event != 0 && arduino_event != 40)
    return;
  arduino_event = 50;
}

void STILERGB() // effetti RGB durante stampa
{
  switch (stileRGB) // cambio effetto RGB durante stampa tasti più e meno
  {
  case 1:
    RGB_LED.fadeRainbow();
    break;
  case 2:
    RGB_LED.fade("RGB");
    break;
  case 3:
    RGB_LED.fade("RG");
    break;
  case 4:
    RGB_LED.fade("RB");
    break;
  case 5:
    RGB_LED.fade("GB");
    break;
  case 6:
    RGB_LED.blink("red");
    break;
  case 7:
    RGB_LED.pulse("R");
    break;
  case 8:
    RGB_LED.blink("blue");
    break;
  default:
    break;
  }
}

void loop()
{
  // verifica pressione tasti
  HOME_BUT.tick();
  MINUS_BUT.tick();
  PLUS_BUT.tick();
  PLAY_BUT.tick();

  if (marlin_event == 0 && arduino_event == 0) // stato spento
  {
    // spegne tutti i led
    HOME_LED.high();
    MINUS_LED.high();
    PLUS_LED.high();
    PLAY_LED.high();
    // stato RGB da fermo
    RGB_LED.defaultColor("white");
  }
  else
  {
    // comandi arduino
    if (arduino_event == 10) // BUTTON HOME
    {
      if (marlin_event == 10)
      {
        HOME_LED.blink(100, 100);
        HOME_LED.loop();
        RGB_LED.blink("green");
      }
      else
      {
        HOME_LED.low();
      }
    }
    else if (arduino_event == 20) // BUTTON MINUS
    {
      if (marlin_event == 0)
      {
        MINUS_LED.low();
      }
      else
      {
        switch (marlin_event)
        {
        case 20: // preriscaldamento
          MINUS_LED.blink(100, 100);
          RGB_LED.blink("red");
          break;
        case 21: // estrusione
          MINUS_LED.blink(200, 200);
          RGB_LED.blink("violet");
          break;
        case 23: // riscaldato
          MINUS_LED.blink(500, 500);
          RGB_LED.pulse("R");
          break;
        default:
          break;
        }
        MINUS_LED.loop();
      }
    }
    else if (arduino_event == 30) // BUTTON PLUS
    {
      if (marlin_event == 0)
      {
        PLUS_LED.low();
      }
      else
      {
        switch (marlin_event)
        {
        case 30: // preriscaldamento
          PLUS_LED.blink(100, 100);
          RGB_LED.blink("red");
          break;
        case 31: // estrusione
          PLUS_LED.blink(200, 200);
          RGB_LED.blink("violet");
          break;
        case 33: // riscaldato
          PLUS_LED.blink(500, 500);
          RGB_LED.pulse("R");
          break;
        default:
          break;
        }
        PLUS_LED.loop();
      }
    }
    else if (arduino_event == 40) // BUTTON PLAY
    {
      switch (marlin_event)
      {
      case 41: // auto home
        PLAY_LED.blink(100, 100);
        RGB_LED.blink("green");
        break;
      case 42: // posizione livellamenro
        PLAY_LED.blink(300, 300);
        RGB_LED.blink("blue");
        break;
      default:
        break;
      }
      PLAY_LED.loop();
    }

    // non in stampa o pausa
    if (marlin_event == 100) // MOVIMENTO ASSI
    {
      RGB_LED.blink("green");
    }
    else if (marlin_event == 101) // LETTO IN RISCALDAMENTO
    {
      RGB_LED.blink("blue");
    }
    else if (marlin_event == 102) // LETTO CALDO
    {
      RGB_LED.pulse("B");
    }
    else if (marlin_event == 103) // UGELLO IN RISCALDAMENTO
    {
      RGB_LED.blink("red");
    }
    else if (marlin_event == 104) // UGELLO CALDO
    {
      RGB_LED.pulse("R");
    }
    else if (marlin_event == 105) // ESPELLE RETRAE FILAMENTO
    {
      RGB_LED.blink("Violet");
    }

    // in stampa o pausa
    else if (marlin_event == 200) // da 100 % a 75 % 4 led accesi
    {

      HOME_LED.low();
      MINUS_LED.low();
      PLUS_LED.low();
      PLAY_LED.blink(200, 200);
      PLAY_LED.loop();
      STILERGB();
    }
    else if (marlin_event == 201) // da 75 % a 50 % 3 led accesi
    {
      HOME_LED.high();
      MINUS_LED.low();
      PLUS_LED.low();
      PLAY_LED.blink(200, 200);
      PLAY_LED.loop();
      STILERGB();
    }
    else if (marlin_event == 202) // da 50 % a 25 % 2 led accesi
    {
      HOME_LED.high();
      MINUS_LED.high();
      PLUS_LED.low();
      PLAY_LED.blink(200, 200);
      PLAY_LED.loop();
      STILERGB();
    }
    else if (marlin_event == 203) // da 25 % a 0 % 1 led acceso
    {
      HOME_LED.high();
      MINUS_LED.high();
      PLUS_LED.high();
      PLAY_LED.blink(200, 200);
      PLAY_LED.loop();
      STILERGB();
    }
    else if (marlin_event == 205) // IN PAUSE
    {
      HOME_LED.blink(500, 500);
      HOME_LED.loop();
      MINUS_LED.blink(500, 500);
      MINUS_LED.loop();
      PLUS_LED.blink(500, 500);
      PLUS_LED.loop();
      PLAY_LED.blink(500, 500);
      PLAY_LED.loop();
      RGB_LED.fade("RGB");
    }
    else if (marlin_event == 210) // letto in riscaldamento
    {
      HOME_LED.low();
      MINUS_LED.low();
      PLUS_LED.low();
      PLAY_LED.blink(200, 200);
      PLAY_LED.loop();
      RGB_LED.blink("blue");
    }
    else if (marlin_event == 220) // hotend in riscaldamento
    {
      HOME_LED.low();
      MINUS_LED.low();
      PLUS_LED.low();
      PLAY_LED.blink(200, 200);
      PLAY_LED.loop();
      RGB_LED.blink("red");
    }
  }
}
