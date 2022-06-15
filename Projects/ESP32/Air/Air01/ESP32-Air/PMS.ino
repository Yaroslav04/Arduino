void PMS_init()
{
  SerialPMS.begin(9600, SERIAL_8N1, 9, 10);
}

void ReadPMS3003Sensor()
{
  if (PMS3003Switch == true)
  {
    if (pms.read(data))
    {
      pm1 = data.PM_AE_UG_1_0;
      pm2_5 = data.PM_AE_UG_2_5;
      pm10 = data.PM_AE_UG_10_0;
      aqi = (pm1 + pm2_5 + pm10) / 3;
    }
  }

  if (millis() > PMS3003StatusDelay + PMS3003StatusMills)
  {
    if (PMS3003Switch == false)
    {
      PMS3003Switch = true;
    }
    PMS3003StatusMills = millis();
  }
}
