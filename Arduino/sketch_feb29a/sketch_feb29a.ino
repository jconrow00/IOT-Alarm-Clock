/****************************************************
*	Made by: Joseph Conrow, Cade Tillema, Andrew Zellner, Louis Marrun
*	for senior capstone project
****************************************************/

#include <Alarm_Req.h>  //Joseph custom library
#include <Display.h>    //Louis modified TFT_eSPI library
#include <DS3231.h>     //RTC library
// DS3231_UnixTime
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my DS3231-library to 
// convert date and time to UnixTime
//
// To use the hardware I2C (TWI) interface of the Arduino you must connect
// the pins as follows:
//
// Arduino Uno/2009:
// ----------------------
// DS3231:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//          SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
//
// Arduino Leonardo:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 2 or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 3 or the dedicated SCL pin
//
// Arduino Mega:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
//
// Arduino Due:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA1 (Digital 70) pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL1 (Digital 71) pin
//
// The internal pull-up resistors will be activated when using the 
// hardware I2C interfaces.
//
// You can connect the DS3231 to any available pin but if you use any
// other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
//

const String WIFI_SSID = "EndyasCurfew";          //USER ENTERED
const String WIFI_PASSWORD = "fivethirty";        //USER ENTERED
const String CLOCK_ID = "48";                     //USER ENTERED



const String HOST_NAME = "54.190.183.82"; 
const String PATH_NAME   = "/alarm_app/requests";
const int BAUD_RATE = 9600;

ServerClass server(CLOCK_ID, WIFI_SSID, WIFI_PASSWORD, HOST_NAME, PATH_NAME, BAUD_RATE);

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

Time t;

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
