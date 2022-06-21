/**************************************************************

   For this example, you need to install Blynk library:
     https://github.com/blynkkk/blynk-library/releases/latest

   TinyGSM Getting Started guide:
     https://tiny.cc/tinygsm-readme

 **************************************************************

   Blynk is a platform with iOS and Android apps to control
   Arduino, Raspberry Pi and the likes over the Internet.
   You can easily build graphic interfaces for all your
   projects by simply dragging and dropping widgets.

   Blynk supports many development boards with WiFi, Ethernet,
   GSM, Bluetooth, BLE, USB/Serial connection methods.
   See more in Blynk library examples and community forum.

                  http://www.blynk.io/

   Change GPRS apm, user, pass, and Blynk auth token to run :)
 **************************************************************/
#include "SPIFFS.h"

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

// Select your modem:
#define TINY_GSM_MODEM_SIM800

#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Hardware Serial on Mega, Leonardo, Micro
#ifndef __AVR_ATmega328P__
#define SerialAT Serial1

// or Software Serial on Uno, Nano
#else
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(9, 10);  // RX, TX
#endif


// Your GPRS credentials, if any
const char apn[]  = "internet";
const char user[] = "";
const char pass[] = "";

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
const char auth[] = "CHR-19WsPXYDYXWUs2GXgV2c63PgQ20A";

TinyGsm modem(SerialAT);

WidgetTerminal terminal(V0);

WidgetMap myMap(V1);

BLYNK_WRITE(V0)
{

  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("Marco") == param.asStr()) {
    terminal.println("You said: 'Marco'") ;
    terminal.println("I said: 'Polo'") ;
  } else {

    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}

int StatusDelay = 2000;
unsigned long StatusMills;
int count = 0;
double lat = 55.5075;
double lon = 35.1287;

void setup()
{
  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);
  // Set GSM module baud rate
  SerialAT.begin(115200);
  delay(500);
  SerialMon.println("Initializing modem...");
  modem.restart();
  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);
  SerialMon.print("end modem: ");
  Blynk.begin(auth, modem, apn, user, pass);
  SerialMon.print("end blynk: ");
  myMap.clear();
  myMap.location(count, lat + random(1,5) , lon, "value");
  delay(1000);
  ESP.restart();
}

void loop()
{
  /*Blynk.run();
  if (millis() > StatusDelay + StatusMills)
  {
    lat = lat + 0.001;
    lon = lon + 0.001;
    myMap.location(count, lat , lon, "value");
    count++;
    StatusMills = millis();
    terminal.println(count);
    delay(500);
  }*/
}
