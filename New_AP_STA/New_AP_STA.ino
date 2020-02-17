/*
 *Code for ESP32, configured in both AP and STA mode, 
 *Upon pressing a button, the Esp32 should be in AP mode 
 *where #Wifi connection can be configured by entering ssid, password
 *#API configuration and it should update in a String variable of a code
 *Entering #Machine Name and it should update to a string variable of the code
 *Entering #device I'D and it should be updated in string variable of code.
 *API format:
 *String SN_node_api="http://192.168.1.207:8090/api/IO/PostIO_NodeData";
 *
 *Author : Asmita Jha
 *Date : 18-04-2019
 */
#include <WiFi.h>
#include <WebServer.h>
#include "FS.h"
#include "SPIFFS.h" 
#include "ConfigInputPage.h"
#include "ConfigureWiFiPage.h"
#include "ConfigureMachineNamePage.h"
#include "ConfigureProject_CodePage.h"
#include "ConfigureAPIPage.h"
#include "dataSavedPage.h"

WebServer server(80);

#define AP_ssid       "SensorNode"        //ssid when esp32 is in AP mode
#define AP_password   "sn@123456"    //password when esp32 is in AP mode


String STA_ssid = "";                      //ssid of router to which esp32 will be connected in STA mode
String STA_password = "";                   //password required to connectect to router when in STA mode
String SN_node_api = "";                    //API Configuration
String MachineName = "";                    //Machine name configuration
String Project_Code = "";                       //Device ID configuration
String Input1="",Input2="",Input3="",Input4="",Input5="",Input6="",Input7="",Input8="";

const int buttonPin = 23;             //Button Pin
volatile uint8_t buttonState = 0;     //Varible to keep track of button state - volatile because it's alo being monitored inside ISR
int allSettingsDone = 0;              //variable to keep in AP mode while user is doing configuration settings

/*=========================================================
   ISR Function
  =========================================================*/
void ISR_Switch()
{
  buttonState = 1;
}

/*=========================================================
   SetUp Function
  =========================================================*/
void setup() 
{ 
  Serial.begin(115200);           //initialize serial communication @ 115200 baudrate
  pinMode(buttonPin, INPUT_PULLUP);      // initialize the pushbutton pin as an input 
  attachInterrupt(digitalPinToInterrupt(buttonPin), ISR_Switch, FALLING); //Attach interrupt to observe button press
 
  if(!SPIFFS.begin(true))    //SPIFFS Initialization
  {
        Serial.println("SPIFFS Mount Failed");
        return;
  }
  //deleteFile(SPIFFS, "/Config.txt"); 
  readConfigFile(SPIFFS, "/Config.txt");  //Read config file to fetch previous configuration settings.
  
  server.on("/",HTTP_GET, handleRoot);
  server.on("/ConfigureWiFi",HTTP_GET, handleWiFiConfig);
  server.on("/ConfigureAPI",HTTP_GET, handleAPIConfig);
  server.on("/ConfigureMachineName",HTTP_GET, handleMachineNameConfig);
  server.on("/ConfigureProject_Code",HTTP_GET, handleProject_CodeConfig);
  server.on("/SaveConfig",HTTP_POST, handleSaveConfig);
  server.on("/close",HTTP_GET, handleClose);
  server.on("/ConfigureInputs",HTTP_GET, handleInputdConfig);
  server.onNotFound(handleNotFound);
  
}

/*=========================================================
   Loop Function
  =========================================================*/
void loop() 
{
  if (buttonState == 1) 
  { 
    Serial.println("Switch_pressed");
     AP_ModeOperation();
    while(allSettingsDone == 0)
    {
      //AP_ModeOperation();
       server.handleClient();
    }
    
    allSettingsDone = 0;
    buttonState = 0;
  } 
  else 
  {
    STA_ModeOperation();
  }

}


/*=========================================================
   STA_ModeOperation for Controller,for STA mode operation.
  =========================================================*/
void STA_ModeOperation()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    if(STA_ssid != "")
    {
      Serial.println((String)"\nIn STA Mode. \nConnecting previous ssid " + STA_ssid + (String)"\nPress button to configure" );
    }
    else
    {
      Serial.println("\nIn STA Mode. \nPress button to configure settings");
    }
    WiFi.mode(WIFI_STA);
    WiFi.begin(STA_ssid.c_str(), STA_password.c_str());    
    
    while (buttonState == 0 && WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    if(buttonState == 1)
    {
       return;
    }
    else
    {
      Serial.print((String)"\nIn STA Mode.\nWiFi connected to." +STA_ssid + "\nIP address: ");
      Serial.println(WiFi.localIP());
    }
  }
}

/*=========================================================
   AP_ModeOperation for Controller,for AT mode operation.
  =========================================================*/
void AP_ModeOperation()
{
  Serial.println("In AP Mode");
  WiFi.disconnect();
  delay(1);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_ssid, AP_password);                      
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
 
}
/*=========================================================
   webpagesPath for Controller,to route the web page path as
   per client request.
  =========================================================*/
/*=========================================================
   Root Request - Display Configuration Menu
  =========================================================*/
void handleRoot() 
{
   server.send(200, "text/html", first_page());
}

/*=========================================================
   WiFi Configuration Request - Display WiFi Configuration Page
  =========================================================*/
void handleWiFiConfig() 
{
  server.send(200, "text/html", Wificonfig_page);
}

/*=========================================================
   MachineNameConfiguration Request - Display MachineName Configuration Page
  =========================================================*/
void handleMachineNameConfig() 
{
  server.send(200, "text/html", machineNameconfig_page);
}
/*=========================================================
   DeviceIdConfiguration Request - Display DeviceId Configuration Page
  =========================================================*/
void handleProject_CodeConfig() 
{
  server.send(200, "text/html",Project_Codeconfig_page);
}
/*=========================================================
   API Configuration Request - Display API Configuration Page
  =========================================================*/
void handleAPIConfig() 
{
  server.send(200, "text/html",APIconfig_page);
}
/*=========================================================
   Configuration saved Request - Display Configuration saved Page
  =========================================================*/
void handleSaveConfig() 
{
  if(server.hasArg("ssid") && server.hasArg("password") )
  {
    STA_ssid = server.arg("ssid");
    STA_password = server.arg("password");
    server.send(200, "text/html",dataSaved_page);
  }
  else if(server.hasArg("machineName"))
  {
    MachineName = server.arg("machineName");
    server.send(200, "text/html",dataSaved_page);
  }
  else if(server.hasArg("Project_Code"))
  {
    Project_Code = server.arg("Project_Code");
    server.send(200, "text/html",dataSaved_page);
  }
  else if(server.hasArg("api"))
  {
    SN_node_api = server.arg("api");
    server.send(200, "text/html",dataSaved_page);
  }
  else if(server.hasArg("Input1"))
  {
    Input1 = server.arg("Input1");
    Input2 = server.arg("Input2");
    Input3 = server.arg("Input3");
    Input4 = server.arg("Input4");
    Input5 = server.arg("Input5");
    Input6 = server.arg("Input6");
    Input7 = server.arg("Input7");
    Input8 = server.arg("Input8");
    server.send(200, "text/html",dataSaved_page);
  }
  else
  {
    server.send(400, "text/plain", "Invalid Request");
  }
  
}

/*=========================================================
   close the setting pages
  =========================================================*/

void handleClose()
{
  String message = (String)"[CONFIG_SETTINGS]\nSSID=" + STA_ssid + (String)"\nPASSWORD=" + STA_password + (String)"\nProject_Code=" + Project_Code + (String)"\nMACHINE_NAME=" + MachineName + (String)"\nAPI=" + SN_node_api\
                    +(String)"\nInput1=" + Input1+(String)"\nInput2=" + Input2 +(String)"\nInput3=" + Input3 + (String)"\nInput4=" + Input4 + (String)"\nInput5=" + Input5 + (String)"\nInput6=" + Input6 + (String)"\nInput7=" + Input7 + \
                    (String)"\nInput8=" + Input8 + (String)"\n" ;
  writeFile(SPIFFS, "/hello.txt", message);             // write config data to new file hello.txt
  deleteFile(SPIFFS, "/Config.txt");                    //delete previous file
  renameFile(SPIFFS, "/hello.txt", "/Config.txt");      //rename hello.txt to Config.txt
  server.send(200, "text/plain","Thank you");
  delay(1000);
  allSettingsDone = 1;
  Serial.println("\nAll settings Done");
  readConfigFile(SPIFFS, "/Config.txt");                //Option to read updated data.
 // ESP.restart();                                     //Or option to restart ESP after doing all the settings
}
/*=========================================================
   Handle not found
  =========================================================*/
void handleNotFound() 
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

/*=========================================================
   Input Config page handler
  =========================================================*/
void handleInputdConfig() {

  //String WaterLevelValue = String(water_level);
 server.send(200, "text/html",InputConfig_page);
}
