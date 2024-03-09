/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-mysql
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <Alarm_Req.h>  //my custom library
// #include <Display.h> 

String WIFI_SSID = "EndyasCurfew";    //USER ENTERED
String WIFI_PASSWORD = "fivethirty";  //USER ENTERED
String CLOCK_ID = "48";                     //USER ENTERED

String HOST_NAME = "54.190.183.82"; 
String PATH_NAME   = "/alarm_app/requests";
// String FINGERPRINT = "96:A1:7D:B8:EE:2D:7C:1D:13:59:4C:F5:AB:3E:69:E8:07:EB:05:FA";
int BAUD_RATE = 9600;

void setup() {
  ServerClass server = ServerClass(CLOCK_ID, WIFI_SSID, WIFI_PASSWORD, HOST_NAME, PATH_NAME, BAUD_RATE);
  int test = server.req_alarm_cnt();
  Serial.printf("(ID:%s) AlarmCnt: %d\n",CLOCK_ID, test);
  for (int i = 1; i <= test; i++){
    String foo = server.req_alarm_time(i);
    int bar = server.req_alarm_toggle(i);
    Serial.printf("(ID:%s) AlarmTime: %s Toggle: %d\n",CLOCK_ID, foo, bar);
  }

}

void loop() {

}
