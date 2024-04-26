/****************************************************
*	Made by: Joseph Conrow, Cade Tillema, Andrew Zellner, Louis Marrun
*	for senior capstone project
****************************************************/

// #include <TFT_eSPI.h>
// #include <SPI.h>
#include <Alarm_Req.h>  //my custom library
#include <Display.h> 

const String WIFI_SSID = "EndyasCurfew";          //USER ENTERED
const String WIFI_PASSWORD = "fivethirty";        //USER ENTERED
const String CLOCK_ID = "48";                     //USER ENTERED



const String HOST_NAME = "54.190.183.82"; 
const String PATH_NAME   = "/alarm_app/requests";
const int BAUD_RATE = 9600;

ServerClass server(CLOCK_ID, WIFI_SSID, WIFI_PASSWORD, HOST_NAME, PATH_NAME, BAUD_RATE);

void setup() {
  server.init();  
  initialize_screen();

}

void loop() {
  update_screen(12, 12, 12);
  String clockid = server.getID();
  Serial.printf("GetID: %s\n",clockid);

  String Temp = server.req_clock_time();
  Serial.printf("Time: %s\n",Temp);

  int test = server.req_alarm_cnt();
  Serial.printf("(ID:%s) AlarmCnt: %d\n",CLOCK_ID, test);
  
  for (int i = 1; i <= test; i++){
    String foo = server.req_alarm_time(i);
    int bar = server.req_alarm_toggle(i);
    Serial.printf("(ID:%s) AlarmTime: %s Toggle: %d\n",CLOCK_ID, foo, bar);
  }
  sleep(5);
}
