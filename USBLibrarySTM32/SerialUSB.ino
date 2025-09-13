#include <Arduino.h>
#include "USBCDC.h"

USBCDC USBSerial;
// separate USB dongle for serial trace
HardwareSerial HwSerial(PA3, PA2);	// RX2, TX2 https://forum.arduino.cc/t/stm32f411ce-black-pill-serial-port-pin-mapping/907459

bool toggle = true, timeout = false, ok = true, restart = true, once = true;
unsigned long now, then, wait = 0;
// char sname[33];
char buffer[USB_EP_SIZE + 1];

void LEDb4()
{
  digitalWrite(PC13, toggle ? HIGH : LOW);
  toggle = !toggle;
}

void LED()
{
  if (millis() < then + wait)
    return;

  if (!ok)
    wait = 50;
  else if (timeout)
    wait = 1250;
  else if (restart)
    wait = 250;
  else if (25 > USBSerial.availableForWrite())
    wait = (toggle) ? 400 : 800;
  else wait = 100;
  LEDb4();
  then = millis();
}

void CDCwait()
{
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
  restart = true;
}

bool printUSB(const char *string)
{
  int n, m = strlen(string), l = USBSerial.availableForWrite();
  bool rc = false;

  if (m < l) // resist buffer overflow
  {
    HwSerial.print(string); HwSerial.print("\r");
    if ((rc = (m == (n = USBSerial.write(string, m)))))
    {
      if (!once)
        HwSerial.println("printUSB():  recovered!");
      once = true;
    } else {
      HwSerial.print("printUSB():  not ok;  USBSerial.availableForWrite() returned ");
      HwSerial.println(l); HwSerial.print("USBSerial.write() returned "); HwSerial.print(n);
      HwSerial.print(" for USBSerial.write() length "); HwSerial.println(m);

      USBSerial.end();
      HwSerial.println("USBSerial.end()");
      USB_End();
      HwSerial.println("USB_End()");
    }
  } else if (once) {
    HwSerial.print("printUSB(): not enough availableForWrite(): "); HwSerial.println(l);
    once = false;
  }
  return rc;
}

void startUSB()
{
  USBSerial.begin(115200);
  HwSerial.println("USBSerial.begin(115200)");
  USB_Begin();
  HwSerial.println("USB_Begin()");
  LEDb4();   

  while (!USB_Running())
  {
    // wait until usb connected
    delay(80);
    LEDb4();
  }
  HwSerial.println("USB_Running()");
  CDCwait();
  ok = true;
  ok = printUSB("USBSerial restarted\n");
  USBSerial.clearWriteError();	// USBLibrarySTM32/src/USBCDC.cpp:271
  timeout = false;
}

void setup()
{
  // https://hackaday.com/2021/01/20/blue-pill-vs-black-pill-transitioning-from-stm32f103-to-stm32f411/
  pinMode(PC13, OUTPUT);    // LED
  LEDb4();   
  HwSerial.begin(19200);
  HwSerial.print("USBSerial USB_EP_SIZE = ");
  HwSerial.println(USB_EP_SIZE);

/* protected... why?
  uint8_t l = USBSerial.getShortName(sname);
  sname[l] = (char)0;
 */

  now = then = millis();
}

void loop()
{
  int l, m;

  LED();

  if (!USBSerial)		// USBSerial.write() error recovery
    startUSB();

  while (0 < (l = USBSerial.available()))
  {
    int i, a = USBSerial.availableForWrite();

    ok = true;
    wait = 100;
    if (timeout)
    {
      timeout = false;
      ok = printUSB("\nUSBSerial resumed\n");
    }
    if (a > USB_EP_SIZE)
      a = USB_EP_SIZE;
    if (l > a)
      l = a;
    for (i = 0; i < l; i++)
      buffer[i] = USBSerial.read();
    buffer[i] = '\0';
    ok = printUSB(buffer);
    if (!ok)
        while (0 < USBSerial.available())
          USBSerial.read();            // flush 
    now = millis();
  }

  if (millis() > 5000 + now)    // suspiciously quiet
  {
    ok = printUSB("\nUSBSerial waiting...\n");
    timeout = true;
    wait = 1250;
    now = millis();
  }
}
