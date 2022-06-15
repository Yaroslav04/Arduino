#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include <HardwareSerial.h>
#include <PMS.h>
#include <DFRobot_SHT20.h>
#include <SimpleFTPServer.h>
#include "SPIFFS.h"
#include "ArduinoJson.h"
#include "MHZ19.h"
#include <time.h>
#include "SD.h"
#include "SPI.h"

// WiFi Config
const char *ssid = "Hata2";            // Enter SSID here
const char *password = "XA07006958";   // Enter Password here
const char *ssidAP = "HataAP";         // Enter SSID here
const char *passwordAP = "XA07006958"; // Enter Password here
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);

// Time
tm timeinfo;
bool tExist = false;

// FTPServer
FtpServer ftpSrv;

// SD
int SaveStatusDelay = 10000;
unsigned long SaveStatusMills;

// PMS
HardwareSerial SerialPMS(1);
PMS pms(SerialPMS);
PMS::DATA data;
int PMS3003StatusDelay = 10000;
unsigned long PMS3003StatusMills;
unsigned int pm1 = 0;
unsigned int pm2_5 = 0;
unsigned int pm10 = 0;
unsigned int aqi = 0;
bool PMS3003Switch = true;

// SHT20
DFRobot_SHT20 sht20;
int SHT20StatusDelay = 10000;
unsigned long SHTStatusMills;
int humidity = 0;
int temperature = 0;

// MZH
HardwareSerial SerialMHZ(2);
int MHZStatusDelay = 10000;
unsigned long MHZStatusMills;
unsigned int co = 0;
MHZ19 myMHZ19;

// ALERT
bool alert = true;
bool ring = false;
bool AlertFirstSignsal = true;
int AlertStatusDelay = 1000;
unsigned long AlertStatusMills;
int AlertRingStatusDelay = 1000;
unsigned long AlertRingStatusMills;

// Graph
int GStatusDelay = 300000;
unsigned long GStatusMills;
float temperature30 = 0;
float temperature25 = 0;
float temperature20 = 0;
float temperature15 = 0;
float temperature10 = 0;
float temperature5 = 0;
float humidity30 = 0;
float humidity25 = 0;
float humidity20 = 0;
float humidity15 = 0;
float humidity10 = 0;
float humidity5 = 0;
unsigned int aqi30 = 0;
unsigned int aqi25 = 0;
unsigned int aqi20 = 0;
unsigned int aqi15 = 0;
unsigned int aqi10 = 0;
unsigned int aqi5 = 0;
unsigned int co30 = 0;
unsigned int co25 = 0;
unsigned int co20 = 0;
unsigned int co15 = 0;
unsigned int co10 = 0;
unsigned int co5 = 0;

void setup()
{
  Serial.begin(115200);
  SHT20_init();
  Serial.println("sh20");
  PMS_init();
  Serial.println("pms");
  MHZinit();
  Serial.println("mhz");
  WiFiInit();
  Serial.println("wifi");
  tExist = TimeSynch();
  Serial.println("time");
  SPIFFS.begin();
  delay(1000);
  ftpSrv.begin("esp32", "esp32");
  Serial.println("ftp");
  SDinit();
  Serial.println("sd");
  ServerInit();
  Serial.println("server");
  delay(5000);
  Serial.println("start");
  Serial.println(GetValuesWithDateJson(GetDateTime()));
}

void loop()
{
  server.handleClient();
  ftpSrv.handleFTP();
  ReadSHT20Sensor();
  ReadPMS3003Sensor();
  ReadMHZSensor();
  AlertHook();
  GetGraph();
  Save();
  WatchDog();
}
