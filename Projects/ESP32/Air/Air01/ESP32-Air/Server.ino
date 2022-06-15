void SendSensorsJson()
{
  server.send(200, "application/json", GetValuesJson());
}

void SendSensorsValue()
{
  String _values = "sensor_1," + String(temperature, 0) + ";sensor_2," + String(humidity, 0) + ";sensor_3," + "AQI: " + String(aqi) + "| (" + String(pm1) + "|) (" + String(pm2_5) + "|) (" + String(pm10) + ")" + ";sensor_4," + String(co);
  Serial.println(GetValuesJson());
  server.send(200, "text/plain", _values);
}

void SendGraphsValue()
{
  String _values = GraphFormat("graph_1", String(temperature30), String(temperature25), String(temperature20), String(temperature15), String(temperature10), String(temperature5), String(temperature)) + ";";
  _values = _values + GraphFormat("graph_2", String(humidity30), String(humidity25), String(humidity20), String(humidity15), String(humidity10), String(humidity5), String(humidity)) + ";";
  _values = _values + GraphFormat("graph_3", String(aqi30), String(aqi25), String(aqi20), String(aqi15), String(aqi10), String(aqi5), String(aqi)) + ";";
  _values = _values + GraphFormat("graph_4", String(co30), String(co25), String(co20), String(co15), String(co10), String(co5), String(co));
  server.send(200, "text/plain", _values);
}

void SendGraphsJson()
{
  server.send(200, "application/json", GetGraphsJson());
}

String getContentType(String filename)
{
  if (server.hasArg("download"))
    return "application/octet-stream";
  else if (filename.endsWith(".htm"))
    return "text/html";
  else if (filename.endsWith(".html"))
    return "text/html";
  else if (filename.endsWith(".json"))
    return "application/json";
  else if (filename.endsWith(".css"))
    return "text/css";
  else if (filename.endsWith(".js"))
    return "application/javascript";
  else if (filename.endsWith(".png"))
    return "image/png";
  else if (filename.endsWith(".gif"))
    return "image/gif";
  else if (filename.endsWith(".jpg"))
    return "image/jpeg";
  else if (filename.endsWith(".ico"))
    return "image/x-icon";
  else if (filename.endsWith(".xml"))
    return "text/xml";
  else if (filename.endsWith(".pdf"))
    return "application/x-pdf";
  else if (filename.endsWith(".zip"))
    return "application/x-zip";
  else if (filename.endsWith(".gz"))
    return "application/x-gzip";
  return "text/plain";
}

bool handleFileRead(String path)
{
  if (path.endsWith("/"))
    path += "index.html";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path))
  {
    if (SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void ServerInit()
{
  server.on("/getSensorsValue", SendSensorsJson);
  server.on("/getGraphsValue", SendGraphsJson);

  server.onNotFound([]()
                    {
    if (!handleFileRead(server.uri()))
    server.send(404, "text/plain", "FileNotFound"); });

  server.begin();
}
