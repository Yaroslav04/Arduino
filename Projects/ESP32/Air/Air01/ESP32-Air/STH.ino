void SHT20_init()
{
  sht20.initSHT20();
  delay(500);
  sht20.checkSHT20();
}

void ReadSHT20Sensor()
{
  if (millis() > SHT20StatusDelay + SHTStatusMills)
  {
    float _humidity = sht20.readHumidity();
    float _temperature = sht20.readTemperature();
    if (_humidity != 998)
    {
      if (_temperature != 998)
      {
        humidity = int(_humidity);
        temperature = int(_temperature);
      }
    }
    SHTStatusMills = millis();
  }
}
