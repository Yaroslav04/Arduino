void WiFiInit()
{
  byte tries = 20;
  WiFi.begin(ssid, password);
  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.disconnect();
    WiFi.softAP(ssidAP, passwordAP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    Serial.println("AP mode start");

  }
  else
  {
    Serial.println("WIFI mode start");
    Serial.println(WiFi.localIP());
  }
}

bool TimeSynch()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    configTime(3 * 3600, 0, "pool.ntp.org");
    int i = 0;
    while (!time(nullptr) && i < 10)
    {
      Serial.print(".");
      i++;
      delay(1000);
    }
  }
  return time(nullptr);
}
