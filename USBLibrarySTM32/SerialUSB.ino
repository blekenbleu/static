#include <Arduino.h>
#include "USBCDC.h"

USBCDC USBSerial;
bool toggle = true, unavailable = false;
unsigned long now, then, wait = 0;
// char sname[33];

void LEDb4()
{
  digitalWrite(PC13, toggle ? HIGH : LOW);
  toggle = !toggle;
}

void LED()
{
  if (millis() < then + wait)
    return;
  if (25 > USBSerial.availableForWrite())
    wait = (toggle) ? 500 : 700;
  LEDb4();
  then = millis();
}

void setup()
{
  // according to https://hackaday.com/2021/01/20/blue-pill-vs-black-pill-transitioning-from-stm32f103-to-stm32f411/
  pinMode(PC13, OUTPUT);    // LED
  
  USBSerial.begin(115200);
  USB_Begin();
  LEDb4();   

  while (!USB_Running())
  {
    // wait until usb connected
    delay(80);
    LEDb4();
  }

  while (!USBSerial)
  {
    // wait for Serial port connection
    delay(500);    // syncopated blink
    LEDb4();
    delay(250);
    LEDb4();
    delay(750);
    LEDb4();
  }

/* protected... why?
  uint8_t l = USBSerial.getShortName(sname);
  sname[l] = (char)0;
 */

  USBSerial.print("USBSerial connect\n");
  now = then = millis();
  wait = 250;
}

void loop()
{
  LED();

  if (!USBSerial)
  {
    USBSerial.begin(115200);
    while (!USBSerial)
    {
      delay(150);
      LEDb4();
    }
    if (25 < USBSerial.availableForWrite())
      USBSerial.print("USBSerial restarted\n");
    wait = 250;
  }

  while (USBSerial.available())
  {
    if (unavailable)
    {
      unavailable = false;
      USBSerial.print("\nUSBSerial resumed\n");
    }
    USBSerial.print((char)USBSerial.read());
    wait = 100;
    now = millis();
  }

  if (millis() > 10000 + now)	// suspiciously quiet
  {
    now = millis();
    if (25 < USBSerial.availableForWrite())
    {
      unavailable = true;
      if (wait < 400)	// prevent buffer overflow 
        USBSerial.print("USBSerial waiting...");
    }
    wait = 1250;
  }
}
