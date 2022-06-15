void appendFile(fs::FS &fs, String path, String message)
{
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file)
  {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message))
  {
    Serial.println("Message appended");
  }
  else
  {
    Serial.println("Append failed");
  }
  file.close();
}

void readFile(fs::FS &fs, const char *path)
{
  Serial.printf("Reading file:\n %s\n", path);

  File file = fs.open(path);
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available())
  {
    Serial.write(file.read());
  }
  file.close();
}

void deleteFile(fs::FS &fs, String path)
{
  Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path))
  {
    Serial.println("File deleted");
  }
  else
  {
    Serial.println("Delete failed");
  }
}

void createDir(fs::FS &fs, String path)
{
  Serial.printf("Creating Dir: %s\n", path);
  if (fs.mkdir(path))
  {
    Serial.println("Dir created");
  }
  else
  {
    Serial.println("mkdir failed");
  }
}

void Save()
{
  if (millis() > SaveStatusDelay + SaveStatusMills)
  {
    if (tExist)
    {
      if (co != 0)
      {
        String month = "/" + GetMonth();
        if (!SD.exists(month))
        {
          createDir(SD, month);
        }

        String day = "/" + GetMonth() + "/" + GetDay() + ".txt";
        if (!SD.exists(day))
        {
          appendFile(SD, day, "");
        }

        String w = GetValuesWithDateJson(GetDateTime()) + "\n";
        Serial.println(w);
        appendFile(SD, day, w);
      }
    }
    SaveStatusMills = millis();
  }
}

void SDinit()
{
  if (!SD.begin(5))
  {
    Serial.println("Card Mount Failed");
    return;
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}
