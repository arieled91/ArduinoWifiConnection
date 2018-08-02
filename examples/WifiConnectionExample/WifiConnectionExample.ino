#include <Arduino.h>
#include <WifiConnection.h>

const int rxPin = 6;
const int txPin = 5;

WifiConnection wifi = WifiConnection(rxPin,txPin,"myWifiSsid","myWifiPassword");

void setup() {
  int connStatus = wifi.connect();
}


void loop(){
  if(wifi.getStatus()==0) wifi.connect();
  //do stuff
  delay(2000);
}
