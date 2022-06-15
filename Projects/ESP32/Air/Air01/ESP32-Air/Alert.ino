void Alert()
{
  if (AlertFirstSignsal)
  {
    AlertFirstSignsal = false;
    AlertStatusMills = millis();
  }
  if (millis() > AlertStatusDelay + AlertStatusMills)
  {
    AlertFirstSignsal = true;
    AlertStatusMills = millis();
  }
}

void AlertRing()
{
  if (millis() > AlertRingStatusDelay + AlertRingStatusMills)
  {

    AlertRingStatusMills = millis();
  }
}

void AlertHook()
{
  if (aqi > 50)
  {
  }

  if (temperature > 40)
  {
  }
}

void AlertSwitch()
{
  if (alert)
  {
    alert = false;
  }
  else
  {
    alert = true;
  }
}
