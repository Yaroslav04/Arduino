void MHZinit()
{
  SerialMHZ.begin(9600, SERIAL_8N1, 17, 16);
  delay(500);
  myMHZ19.begin(SerialMHZ);
  delay(500);
  myMHZ19.autoCalibration();
  delay(500);
  myMHZ19.setRange();
}

void ReadMHZSensor()
{
  if (millis() > MHZStatusDelay + MHZStatusMills)
  {

    if (millis() > 300000)
    {
      co = myMHZ19.getCO2();
    }

    MHZStatusMills = millis();
  }
}
