/// sketch arduino - SANDOR MOD V3 06_2022 - LABISTS X1

#include <ezOutput.h>
#include <OneButton.h>
#include <RGB_LIB.h> // libreria personalizzata
#include <Wire.h>

RGB_LIB RGB_LED(3, 5, 6, 0);

ezOutput HOME_LED(17);  // PIN A3
ezOutput MINUS_LED(16); // PIN A2
ezOutput PLUS_LED(15);  // PIN A1
ezOutput PLAY_LED(14);  // PIN A0

OneButton HOME_BUT(7, true);
OneButton MINUS_BUT(8, true);
OneButton PLUS_BUT(12, true);
OneButton PLAY_BUT(4, true);

volatile byte arduino_event = 0;
volatile byte marlin_event = 0;
int stileRGB = 1;
byte a = 0;

// Output pin to transistor base
int ESP_Pin = 2; //
int FAN_Pin = 9;
int LED1_Pin = 10;
int LED2_Pin = 11;

bool LED1_ON = false;
bool LED2_ON = false;
bool ESP01_ON = true;
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
  PLAY_BUT.attachLongPressStop(playClick_longPress);
  PLAY_BUT.attachDoubleClick(playClick_DoubleClick);

  pinMode(ESP_Pin, OUTPUT);
  pinMode(FAN_Pin, OUTPUT);
  pinMode(LED1_Pin, OUTPUT);
  pinMode(LED2_Pin, OUTPUT);

  // Make sure transistor is off
  //  digitalWrite(ESP_Pin, LOW);
  //  digitalWrite(FAN_Pin, LOW);
  //  digitalWrite(LED1_Pin, LOW);
  //  digitalWrite(LED2_Pin, LOW);

  digitalWrite(ESP_Pin, HIGH);
  digitalWrite(FAN_Pin, LOW);
 //digitalWrite(LED1_Pin, HIGH);
 //digitalWrite(LED2_Pin, HIGH);

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
#endif // intro
}

void requestEvent() // risponde a richiesta da marlin
{
  Wire.write(arduino_event);
}

void receiveEvent(int howMany) // riceve marlin_event da marlin
{
  while (Wire.available())
  {
    marlin_event = Wire.read();
  }

  /// spegne tutti i led
  HOME_LED.high();
  MINUS_LED.high();
  PLUS_LED.high();
  PLAY_LED.high();
  RGB_LED.setColor(0, 0, 0);

  if (marlin_event == 0 || marlin_event == 20 || marlin_event == 21) // comandi marlin ready, print, pause
  {
    arduino_event = marlin_event;
  }
  else if (marlin_event == 8) /// punto successivo livellamento piatto
  {
    arduino_event = 13;
  }
  else if (marlin_event == 9) /// punto successivo livellamento piatto
  {
    arduino_event = 14;
  }
  else if (arduino_event == 15 && marlin_event == 2) /// avvia livellamento piatto
  {
    arduino_event = 14;
  }
  else if (marlin_event == 26) // TEMPERATURA > 50 GRADI ACCENDE VENTOLA
  {
    digitalWrite(FAN_Pin, HIGH);
  }
  else if (marlin_event == 27) // TEMPERATURA < 50 GRADI SPEGNE VENTOLA
  {
    digitalWrite(FAN_Pin, LOW);
  }
}

void homeClick() //  comando Z-HOME, annulla comando estrusione (plus)
{
  if (arduino_event != 0 && arduino_event != 12 && arduino_event != 13)
    return;


  if (arduino_event == 13 && marlin_event == 28 || marlin_event == 25) // spegne e raffredda
  {
    arduino_event = 0;
  }

  else
  {
    arduino_event = 11;
  }
}

void homeClick_longPress() // annulla tutti comandi da implementare
{
  if (arduino_event == 20 || arduino_event == 21)
    return;
  arduino_event = 0;
}

void homeClick_DoubleClick() // da fermo accende e spegne ESP01
{
  if (arduino_event == 0 && marlin_event == 0)
  {
    if (ESP01_ON == true)
    {
      digitalWrite(ESP_Pin, LOW);
      ESP01_ON = false;
    }
    else
      digitalWrite(ESP_Pin, HIGH);
    ESP01_ON = true;
  }
}

void minusClick() // comando espelle filamento, cambia effetto RGB LED in stampa
{
  if (arduino_event != 0 && arduino_event != 12 && arduino_event != 20)
    return;

  if (arduino_event == 20) /// cambia effetto RGB in stampa
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
    if (arduino_event == 12 && marlin_event == 25) // spegne se sta riscaldando
    {
      arduino_event = 0;
    }
    else
    {
      arduino_event = 12; // comando espelli
    }
  }
}

void plusClick() // comando estrudi filamento, cambia effetto RGB LED in stampa
{
  if (arduino_event != 0 && arduino_event != 13 && arduino_event != 20 && arduino_event != 25 && arduino_event != 28)
    return;

  switch (marlin_event)
  {
    case 0: // avvia funzione riscadamento
      arduino_event = 13;
      break;
    case 25: // in riscaldamento sepegne annulla
      arduino_event = 0;
      break;
    case 28: // riscaldato ripete estrusione
      arduino_event = 8;
      break;

    default:
      break;
     }  
      if (arduino_event == 20) /// cambia effetto RGB in stampa
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
  if (arduino_event != 0 && arduino_event != 14)
    return;

  if (arduino_event == 0)
  {
    arduino_event = 14; // comando XYZ-HOME, comando Z + 10 mm
  }
  else if (arduino_event == 14 && marlin_event == 2)
  {
    arduino_event = 9; // 9 nuovo punto livellamento piatto
  }
}

void playClick_longPress() /// avvio funzione livellamento piatto, annulla funzione livellamento piatto
{
  if (arduino_event != 0 && arduino_event != 14)
    return;
  arduino_event = 15;
}

void playClick_DoubleClick() /// accendi e spegni luci due modalità
{

  if (LED1_ON == true && LED2_ON == true)
  {
    RGB_LED.blink("red");
    digitalWrite(LED1_Pin, LOW);
    digitalWrite(LED2_Pin, LOW);
    LED1_ON = false;
    LED2_ON = false;
    return;
  }

  if (LED1_ON == false)
  {
    digitalWrite(LED1_Pin, HIGH);
    LED1_ON = true;
  }
  else
  {
    digitalWrite(LED2_Pin, HIGH);
    LED2_ON = true;
  }
}

void loop()
{
  // verifica pressione tasti
  HOME_BUT.tick();
  MINUS_BUT.tick();
  PLUS_BUT.tick();
  PLAY_BUT.tick();

  if (arduino_event == 0 && marlin_event == 0)
  {
    // stato button LED da fermo
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
    if (arduino_event == 11) // BUTTON HOME
    {
      if (marlin_event == 1)
      {
        HOME_LED.blink(100, 100);
        HOME_LED.loop();
        RGB_LED.blink("green");
      }
    }
    else if (arduino_event == 12) // BUTTON MINUS
    {
      MINUS_LED.blink(100, 100);
      MINUS_LED.loop();
    }
    else if (arduino_event == 13) // BUTTON PLUS
    {
      PLUS_LED.blink(100, 100);
      PLUS_LED.loop();
    }
    else if (arduino_event == 14) // BUTTON PLAY
    {
      switch (marlin_event)
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
    // comandi marlin
    if (marlin_event == 20 || marlin_event == 201 || marlin_event == 202 || marlin_event == 203) // IN PRINTING
    {
      switch (marlin_event) // cambio effetto RGB durante stampa
      {
        case 201:
          HOME_LED.low();
          MINUS_LED.low();
          PLUS_LED.low();
          PLAY_LED.blink(200, 200);
          PLAY_LED.loop();
          break;
        case 202:
          HOME_LED.high();
          MINUS_LED.low();
          PLUS_LED.low();
          PLAY_LED.blink(200, 200);
          PLAY_LED.loop();
          break;
        case 203:
          HOME_LED.high();
          MINUS_LED.high();
          PLUS_LED.low();

          PLAY_LED.blink(200, 200);
          PLAY_LED.loop();
          break;
        case 20:
          HOME_LED.high();
          MINUS_LED.high();
          PLUS_LED.high();
          PLAY_LED.blink(200, 200);
          PLAY_LED.loop();
          break;
        default:
          break;
      }


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
    else if (marlin_event == 21) // IN PAUSE
    {
      PLAY_LED.blink(500, 500);
      PLAY_LED.loop();
      RGB_LED.pulse("R");
    }
    else if (marlin_event == 22) // LETTO IN RISCALDAMENTO
    {
      RGB_LED.blink("blue");
    }
    else if (marlin_event == 23) // LETTO CALDO
    {
      RGB_LED.pulse("B");
    }
    else if (marlin_event == 24) // MOVIMENTO ASSI
    {
      RGB_LED.blink("green");
    }
    else if (marlin_event == 25) // UGELLO IN RISCALDAMENTO
    {
      RGB_LED.blink("red");
    }
    else if (marlin_event == 28) // UGELLO CALDO
    {
      RGB_LED.pulse("R");
    }
    else if (marlin_event == 29) // ESPELLE RETRAE FILAMENTO
    {
      RGB_LED.blink("yellow");
    }
  }
}
