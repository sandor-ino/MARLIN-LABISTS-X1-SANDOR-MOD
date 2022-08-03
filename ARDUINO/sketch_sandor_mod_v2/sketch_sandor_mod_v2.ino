/// sketch arduino - SANDOR MOD V2 11_2021 - LABISTS X1

#include <ezOutput.h>
#include <OneButton.h>
#include <RGB_LIB.h> // libreria personalizzata
#include <Wire.h>

RGB_LIB RGB_LED(3, 5, 6, 0);

ezOutput HOME_LED(14);
ezOutput MINUS_LED(15);
ezOutput PLUS_LED(16);
ezOutput PLAY_LED(17);

OneButton HOME_BUT(7, true);
OneButton MINUS_BUT(8, true);
OneButton PLUS_BUT(9, true);
OneButton PLAY_BUT(10, true);

volatile int stato = 0;
volatile int key_flag = 0;
int stileRGB = 1;

void setup()
{
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  HOME_BUT.attachClick(homeClick);
  HOME_BUT.attachLongPressStart(homeClick_longPress);

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
#endif //intro
}

void requestEvent() // risponde a richiesta da marlin
{
  Wire.write(key_flag);
}

void receiveEvent(int howMany) // riceve stato da marlin
{
  while (Wire.available())
  {
    stato = Wire.read(); /// riceve evento
  }
  /// spegne tutti i led
  HOME_LED.high();
  MINUS_LED.high();
  PLUS_LED.high();
  PLAY_LED.high();
  RGB_LED.setColor(0, 0, 0);

  if (stato == 0 || stato == 6 || stato == 7) // comandi marlin stop , print, pause
  {
    key_flag = stato;
  }
  else if (key_flag == 8) /// ripeti estrusione
  {
    key_flag = 3;
  }
  else if (key_flag == 9) /// punto successivo livellamento piatto
  {
    key_flag = 4;
  }
  else if (key_flag == 5 && stato == 2) /// avvia livellamento piatto
  {
    key_flag = 4;
  }
}

void homeClick() //  comando Z-HOME, annulla comando estrusione (plus)
{
  if (key_flag != 0 && key_flag != 1 && key_flag != 3)
    return;

  if ((key_flag == 3 && stato == 3)) // spegne e raffredda con comando estruisione attivo
  {
    key_flag = 0;
  }
  else
  {
    key_flag = 1;
  }
}

void homeClick_longPress() // annulla tutti comandi da implementare
{
  if (key_flag == 6 || key_flag == 7)
    return;
  key_flag = 0;
}

void minusClick() // comando espelle filamento, cambia effetto RGB LED in stampa
{
  if (key_flag != 0 && key_flag != 2 && key_flag != 6)
    return;

  if (key_flag == 6) /// cambia effetto RGB in stampa
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

  else
  {
    if (key_flag == 2 && stato == 1) // spegne se sta riscaldando
    {
      key_flag = 0;
    }
    else
    {
      key_flag = 2; // comando espelli
    }
  }
}

void plusClick() // comando estrudi filamento, cambia effetto RGB LED in stampa
{
  if (key_flag != 0 && key_flag != 3 && key_flag != 6)
    return;

  switch (stato)
  {
  case 0: // avvia funzione riscadamento
    key_flag = 3;
    break;
  case 1: // in riscaldamento sepegne annulla
    key_flag = 0;
    break;
  case 3: // riscaldato ripete estrusione
    key_flag = 8;
    break;
  case 6: // in stampa cambia stile rgb
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

    break;
  default:
    break;
  }
}

void playClick() // comando XYZ-HOME, comando Z + 10 mm, punto successiovo in livellamento
{
  if (key_flag != 0 && key_flag != 4)
    return;

  if (key_flag == 0)
  {
    key_flag = 4; // comando XYZ-HOME, comando Z + 10 mm
  }
  else if (key_flag == 4 && stato == 2)
  {
    key_flag = 9; // nuovo punto livellamento piatto
  }
}

void playClick_longPress() /// avvio funzione livellamento piatto, annulla funzione livellamento piatto
{
  if (key_flag != 0 && key_flag != 4)
    return;
  key_flag = 5;
}

void loop()
{
  // verifica pressione tasti
  HOME_BUT.tick();
  MINUS_BUT.tick();
  PLUS_BUT.tick();
  PLAY_BUT.tick();

  if (stato == 0 && key_flag == 0)
  {
    HOME_LED.high();
    MINUS_LED.high();
    PLUS_LED.high();
    PLAY_LED.high();
    // stato RGB da fermo
    RGB_LED.defaultColor("white");
  }
  else
  {
    if (key_flag == 1) // BUTTON HOME
    {
      if (stato == 1)
      {
        HOME_LED.blink(100, 100);
        HOME_LED.loop();
        RGB_LED.blink("green");
      }
    }
    else if (key_flag == 2) // BUTTON MINUS
    {
      switch (stato)
      {
      case 1: // preriscaldamento
        MINUS_LED.blink(100, 100);
        RGB_LED.pulse("B");
        break;
      case 2: // estrusione
        MINUS_LED.blink(200, 200);
        RGB_LED.blink("red");
        break;
      case 3: // caldo
        MINUS_LED.blink(100, 100);
        RGB_LED.pulse("R");
        break;
      default:
        break;
      }
      MINUS_LED.loop();
    }
    else if (key_flag == 3) // BUTTON PLUS
    {
      switch (stato)
      {
      case 1: // preriscaldamento
        PLUS_LED.blink(100, 100);

        RGB_LED.pulse("B");
        break;
      case 2: // estrusione
        PLUS_LED.blink(200, 200);
        RGB_LED.blink("red");
        break;
      case 3: // caldo
        PLUS_LED.blink(150, 150);
        RGB_LED.pulse("R");
        break;

      default:
        break;
      }
      PLUS_LED.loop();
    }
    else if (key_flag == 4) // BUTTON PLAY
    {
      switch (stato)
      {
      case 1: // auto home
        PLAY_LED.blink(100, 100);
        RGB_LED.blink("green");
        break;
      case 2: // posizione livellamenro
        PLAY_LED.blink(300, 300);
        RGB_LED.blink("blue");
        break;
      default:
        break;
      }
      PLAY_LED.loop();
    }
    else if (key_flag == 6) // IN PRINTING
    {
      PLAY_LED.blink(200, 200);
      PLAY_LED.loop();

      switch (stileRGB) // cambio effetto RGB durante stampa
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
        RGB_LED.pulse("G");
        break;
      case 8:
        RGB_LED.blink("blue");
        break;
      default:
        break;
      }
    }
    else if (key_flag == 7) // IN PAUSE
    {
      PLAY_LED.blink(500, 500);
      PLAY_LED.loop();
      RGB_LED.pulse("R");
    }
    /// da sviluppare stato da marlin
    else if (key_flag == 11) // ASSI IN MOVIMENTO
    {
      PLAY_LED.loop();
      RGB_LED.blink("green");
    }
    else if (key_flag == 12) // LETTO IN RISCALDAMENTO
    {
      PLAY_LED.loop();
      RGB_LED.blink("blue");
    }
    else if (key_flag == 13) // UGELLO IN RISCALDAMENTO
    {
      PLAY_LED.loop();
      RGB_LED.blink("red");
    }
    else if (key_flag == 14) // UGELLO CALDO
    {
      PLAY_LED.loop();
      RGB_LED.pulse("R");
    }
  }
}
