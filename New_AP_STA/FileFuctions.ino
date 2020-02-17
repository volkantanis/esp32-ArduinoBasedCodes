/*=========================================================
   writeFile for Controller,to write file to SPIFFS.
  =========================================================*/
uint8_t writeFile(fs::FS & fs, const char * path, String message)
{
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("- failed to open file for writing");
    return 0;
  }
  if (file.print(message))
  {
    Serial.println("- file written");
    file.close();
    return 1;
  }
  else
  {
    Serial.println("- fwrite failed");
    return 0;
  }
}

/*=========================================================
   deleteFile for Controller,to delete file from SPIFFS.
  =========================================================*/
uint8_t deleteFile(fs::FS & fs, const char * path)
{
  Serial.printf("Deleting file: %s\r\n", path);
  if (fs.remove(path))
  {
    Serial.println("- file deleted");
    return 1;
  }
  else
  {
    Serial.println("- delete failed");
    return 0;
  }
}
/*=========================================================
  renameFile for Controller,to rename file in SPIFFS.
  =========================================================*/
uint8_t renameFile(fs::FS & fs, const char * path1, const char * path2)
{
  Serial.printf("Renaming file %s to %s\r\n", path1, path2);
  if (fs.rename(path1, path2))
  {
    Serial.println("- file renamed");
    return 1;
  }
  else
  {
    Serial.println("- rename failed");
    return 0;
  }
}
/*=========================================================
     readConfigFile for Controller,to read file from SPIFFS.
  =========================================================*/
void readConfigFile(fs::FS &fs, const char *path)
{
  String tag, tagVal, message = "";
  Serial.printf("Reading file: %s\r\n",path);

  File file = fs.open(path);

  if ((file == 0) || file.isDirectory())
  {
    Serial.println("- failed to open file for reading");
    return;
  }

  Serial.println("- read from file:");

  while (file.available() > 0)
  {
    //Reading section name and ignoring.
    tag = file.readStringUntil('\n');
    //Reading tokens.
    while (file.available() > 0)
    {
      tag = file.readStringUntil('=');
      tagVal = file.readStringUntil('\n');
      tagVal.trim();
      if (tag == "SSID")
      {
        STA_ssid = tagVal;   //ssid
      }
      else if (tag == "PASSWORD")
      {
        STA_password = tagVal;   //password
      }
      else if (tag == "Project_Code")
      {
        Project_Code = tagVal;   //device ID
      }
      else if (tag == "MACHINE_NAME")
      {
        MachineName = tagVal;   //Machine Name
      }
      else if (tag == "API")
      {
        SN_node_api = tagVal;  //API
      }
       else if (tag == "Input1")
      {
        Input1 = tagVal;  //Input1
      }
       else if (tag == "Input2")
      {
        Input2 = tagVal;  //Input2
      }
       else if (tag == "Input3")
      {
        Input3 = tagVal;  //Input3
      }
       else if (tag == "Input4")
      {
        Input4 = tagVal;  //Input4
      }
       else if (tag == "Input5")
      {
        Input5 = tagVal;  //Input5
      }
       else if (tag == "Input6")
      {
        Input6 = tagVal;  //Input6
      }
       else if (tag == "Input7")
      {
        Input7 = tagVal;  //Input7
      }
       else if (tag == "Input8")
      {
        Input8 = tagVal;  //Input8
      }
    }
  }

  message = (String)"[CONFIG_SETTINGS]\nSSID=" + STA_ssid + (String)"\nPASSWORD=" + STA_password + (String)"\nProject_Code=" + Project_Code + (String)"\nMACHINE_NAME=" + MachineName + (String)"\nAPI=" + SN_node_api\
                    +(String)"\nInput1=" + Input1+(String)"\nInput2=" + Input2 +(String)"\nInput3=" + Input3 + (String)"\nInput4=" + Input4 + (String)"\nInput5=" + Input5 + (String)"\nInput6=" + Input6 + (String)"\nInput7=" + Input7 + \
                    (String)"\nInput8=" + Input8 + (String)"\n" ;
   Serial.println(message);
  file.close();
}
