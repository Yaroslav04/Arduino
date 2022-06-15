String GetValuesJson()
{
  const int capacity = JSON_ARRAY_SIZE(4) + JSON_OBJECT_SIZE(20);
  StaticJsonDocument<capacity> doc;

  JsonObject obj1 = doc.createNestedObject();
  obj1["name"] = "temperature";
  obj1["value"] = int(temperature);

  JsonObject obj2 = doc.createNestedObject();
  obj2["name"] = "humidity";
  obj2["value"] = int(humidity);

  JsonObject obj3 = doc.createNestedObject();
  obj3["name"] = "co";
  obj3["value"] = co;

  const int aqi_capacity = JSON_ARRAY_SIZE(4) + JSON_OBJECT_SIZE(10);
  StaticJsonDocument<capacity> aqi_doc;
  aqi_doc.add(aqi);
  aqi_doc.add(pm1);
  aqi_doc.add(pm2_5);
  aqi_doc.add(pm10);

  JsonObject obj4 = doc.createNestedObject();
  obj4["name"] = "aqi";
  obj4["value"] = aqi_doc;

  String json;
  serializeJson(doc, json);
  return json;
}

String GetValuesWithDateJson(String _date)
{
  const int capacity = JSON_ARRAY_SIZE(4) + JSON_OBJECT_SIZE(20);
  StaticJsonDocument<capacity> doc;

  JsonObject obj1 = doc.createNestedObject();
  obj1["name"] = "temperature";
  obj1["value"] = int(temperature);

  JsonObject obj2 = doc.createNestedObject();
  obj2["name"] = "humidity";
  obj2["value"] = int(humidity);

  JsonObject obj3 = doc.createNestedObject();
  obj3["name"] = "co";
  obj3["value"] = co;

  const int aqi_capacity = JSON_ARRAY_SIZE(4) + JSON_OBJECT_SIZE(10);
  StaticJsonDocument<capacity> aqi_doc;
  aqi_doc.add(aqi);
  aqi_doc.add(pm1);
  aqi_doc.add(pm2_5);
  aqi_doc.add(pm10);

  JsonObject obj4 = doc.createNestedObject();
  obj4["name"] = "aqi";
  obj4["value"] = aqi_doc;

  StaticJsonDocument<capacity> doc_result;
  JsonObject obj5 = doc_result.createNestedObject();
  obj5["date"] = _date;
  obj5["data"] = doc;

  String json;
  serializeJson(doc_result, json);
  return json;
}

String GetGraphsJson()
{
  const int arr_capacity = JSON_ARRAY_SIZE(10) + JSON_OBJECT_SIZE(30);
  StaticJsonDocument<arr_capacity> doc;

  const int sub_arr_capasity = JSON_ARRAY_SIZE(6) + JSON_OBJECT_SIZE(10);

  StaticJsonDocument<sub_arr_capasity> sub_arr_temperature;
  sub_arr_temperature.add(temperature30);
  sub_arr_temperature.add(temperature25);
  sub_arr_temperature.add(temperature20);
  sub_arr_temperature.add(temperature15);
  sub_arr_temperature.add(temperature10);
  sub_arr_temperature.add(temperature5);
  sub_arr_temperature.add(temperature);
  JsonObject obj_temperature = doc.createNestedObject();
  obj_temperature["name"] = "graph_temperature";
  obj_temperature["value"] = sub_arr_temperature;

  StaticJsonDocument<sub_arr_capasity> sub_arr_humidity;
  sub_arr_humidity.add(humidity30);
  sub_arr_humidity.add(humidity25);
  sub_arr_humidity.add(humidity20);
  sub_arr_humidity.add(humidity15);
  sub_arr_humidity.add(humidity10);
  sub_arr_humidity.add(humidity5);
  sub_arr_humidity.add(humidity);
  JsonObject obj_humidity = doc.createNestedObject();
  obj_humidity["name"] = "graph_humidity";
  obj_humidity["value"] = sub_arr_humidity;

  StaticJsonDocument<sub_arr_capasity> sub_arr_co;
  sub_arr_co.add(co30);
  sub_arr_co.add(co25);
  sub_arr_co.add(co20);
  sub_arr_co.add(co15);
  sub_arr_co.add(co10);
  sub_arr_co.add(co5);
  sub_arr_co.add(co);
  JsonObject obj_co = doc.createNestedObject();
  obj_co["name"] = "graph_co";
  obj_co["value"] = sub_arr_co;

  StaticJsonDocument<sub_arr_capasity> sub_arr_aqi;
  sub_arr_aqi.add(aqi30);
  sub_arr_aqi.add(aqi25);
  sub_arr_aqi.add(aqi20);
  sub_arr_aqi.add(aqi15);
  sub_arr_aqi.add(aqi10);
  sub_arr_aqi.add(aqi5);
  sub_arr_aqi.add(aqi);
  JsonObject obj_aqi = doc.createNestedObject();
  obj_aqi["name"] = "graph_aqi";
  obj_aqi["value"] = sub_arr_aqi;

  String json;
  serializeJson(doc, json);
  return json;
}

String GetDateTime()
{
  String result = "";
  getLocalTime(&timeinfo);
  result = result + String(timeinfo.tm_mday) + ".";
  result = result + String(timeinfo.tm_mon + 1) + ".";
  result = result + "2022";
  result = result + " ";
  result = result + String(timeinfo.tm_hour) + ":";
  result = result + String(timeinfo.tm_min) + ":";
  result = result + String(timeinfo.tm_sec);
  return result;
}

String GetDay()
{
  String result = "";
  getLocalTime(&timeinfo);
  result = String(timeinfo.tm_mday);
  return result;
}

String GetMonth()
{
  String result = "";
  getLocalTime(&timeinfo);
  result = String(timeinfo.tm_mon + 1);
  return result;
}

String GetSensorsValue()
{
  String _values = "sensor_1," + String(temperature, 2) + ";sensor_2," + String(humidity, 2) + ";sensor_3," + "AQI: " + String(aqi) + "| (" + String(pm1) + "|) (" + String(pm2_5) + "|) (" + String(pm10) + ")" + ";sensor_4," + String(co);
  return _values;
}

String GetSensorsValueSD()
{
  String _values = String(temperature, 2) + ";" + String(humidity, 2) + ";" + String(pm1) + ";" + String(pm2_5) + ";" + String(pm10) + ";" + String(co);
  return _values;
}

String GraphFormat(String id, String s30, String s25, String s20, String s15, String s10, String s5, String s0)
{
  String _value = id + "," + s30 + "|" + s25 + "|" + s20 + "|" + s15 + "|" + s10 + "|" + s5 + "|" + s0;
  return _value;
}

void GetGraph()
{
  if (millis() > GStatusDelay + GStatusMills)
  {
    temperature30 = temperature25;
    temperature25 = temperature20;
    temperature20 = temperature15;
    temperature15 = temperature10;
    temperature10 = temperature5;
    temperature5 = temperature;

    humidity30 = humidity25;
    humidity25 = humidity20;
    humidity20 = humidity15;
    humidity15 = humidity10;
    humidity10 = humidity5;
    humidity5 = humidity;

    aqi30 = aqi25;
    aqi25 = aqi20;
    aqi20 = aqi15;
    aqi15 = aqi10;
    aqi10 = aqi5;
    aqi5 = aqi;

    co30 = co25;
    co25 = co20;
    co20 = co15;
    co15 = co10;
    co10 = co5;
    co5 = co;

    GStatusMills = millis();
  }
}
