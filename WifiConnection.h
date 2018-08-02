#include <Arduino.h>
#include <string.h>
#include <SoftwareSerial.h>

SoftwareSerial wifiSerial(0,0);
const String server = "google.com";

class WifiConnection {
private:
String ssid;
String password;
int rx=0;
int tx=0;
int status=0;

public:
WifiConnection();
WifiConnection(int rx, int tx, String ssid, String password);
int connect();
int getStatus();
};

WifiConnection::WifiConnection(){}

WifiConnection::WifiConnection(int rx, int tx, String ssid, String password)
{
        this->ssid = ssid;
        this->password = password;
        this->tx = tx;
        this->rx = rx;
        this->status = 0;
}

int WifiConnection::connect()
{
  SoftwareSerial newWifiSerial = SoftwareSerial(rx,tx);
  Serial.println("Starting WIFI Connection");

  Serial.begin(115200);
  newWifiSerial.begin(115200);
  newWifiSerial.println("AT");
  delay(2000);
  if (newWifiSerial.find("OK"))
    Serial.println("AT response OK");
  else
    Serial.println("Error in ESP8266");

  //-----Network configuration-------//

  //ESP8266 in station mode
  newWifiSerial.println("AT+CWMODE=3");
  if (newWifiSerial.find("OK"))
    Serial.println("ESP8266 in Station and Access-Point mode");

  //Wifi authentication
  newWifiSerial.print("AT+CWJAP=");
  newWifiSerial.println("\""+ssid+"\",\""+password+"\"");

  Serial.println("Connecting to '"+ssid+"'...");
  newWifiSerial.setTimeout(10000); //Increase if connection is slow
  newWifiSerial.println("AT+CIPMUX=0");
  if (newWifiSerial.find("OK")){
    wifiSerial = newWifiSerial;
    Serial.println("Wifi Connected");
    status = 1;
  }else{
    status = 0;
    Serial.println("Connection error :(");
}
  return status;

  //------Ending of wifi configuration-------------------
  newWifiSerial.print("AT+CIPSTART=\"TCP\",\"");
  newWifiSerial.print(server);
  newWifiSerial.println("\",80");

}

int WifiConnection::getStatus(){
  return status;
}
