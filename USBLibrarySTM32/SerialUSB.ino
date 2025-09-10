#include <Arduino.h>
#include "USBCDC.h"

USBCDC USBSerial;
// separate USB dongle for serial trace
HardwareSerial Serial2(PA3, PA2);	// RX2, TX2 https://forum.arduino.cc/t/stm32f411ce-black-pill-serial-port-pin-mapping/907459

bool toggle = true, timeout = false, ok = true, restart = true;
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
  else if (25 > USBSerial.availableForWrite())
    wait = (toggle) ? 400 : 800;
  else if (restart)
    wait = 250;
  else wait = 100;
  LEDb4();
  then = millis();
}

void wait4CDC()
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

void setup()
{
  // according to https://hackaday.com/2021/01/20/blue-pill-vs-black-pill-transitioning-from-stm32f103-to-stm32f411/
  pinMode(PC13, OUTPUT);    // LED
  
  Serial2.begin(9600);
  USBSerial.begin(115200);
  USB_Begin();
  LEDb4();   

  while (!USB_Running())
  {
    // wait until usb connected
    delay(80);
    LEDb4();
  }
  Serial2.print("USBSerial USB_EP_SIZE = ");
  Serial2.println(USB_EP_SIZE);

  wait4CDC();

/* protected... why?
  uint8_t l = USBSerial.getShortName(sname);
  sname[l] = (char)0;
 */

  USBSerial.print("USBSerial connect\n");
  Serial2.println("USBSerial connect");
  now = then = millis();
  wait = 250;
}

bool printUSB(const char *string)
{
  int n, m = strlen(string), l = USBSerial.availableForWrite();
  bool rc = false;

  if (ok && m < l) // resist buffer overflow
  {
//  if (wait >= 400) return true;
    Serial2.print(string); Serial2.print("\r");
    if (!(rc = (m == (n = USBSerial.write(string, m)))))
    {
      Serial2.print("printUSB():  not ok;  USBSerial.availableForWrite() returned ");
      Serial2.println(l); Serial2.print("USBSerial.write() returned "); Serial2.print(n);
      Serial2.print(" for USBSerial.write() length "); Serial2.println(m);
    }
  }
  return rc;
}

void loop()
{
  int l, m;

  LED();

  if (!USBSerial)
  {
    USBSerial.begin(115200);
    wait4CDC();
    ok = printUSB("USBSerial restarted\n");
  }

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

  if (millis() > 10000 + now)    // suspiciously quiet
  {
    ok = printUSB("\nUSBSerial waiting...\n");
    timeout = true;
    wait = 1250;
    now = millis();
  }
}
