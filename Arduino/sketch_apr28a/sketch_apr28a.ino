/****************************************************
*	Made by: Joseph Conrow, Cade Tillema, Andrew Zellner, Louis Marrun
*	for senior capstone project
****************************************************/

#include <Alarm_Req.h>  //Joseph custom library
#include <RTClib.h>     //RTC library
#include <TFT_eSPI.h>   // Screen library
#include <SPI.h>   
#include <Arduino.h>
#include "Audio.h"
#include <Display.h>

// const String WIFI_SSID = "EndyasCurfew";          //USER ENTERED
// const String WIFI_PASSWORD = "fivethirty";        //USER ENTERED
const String WIFI_SSID = "joseph";          //USER ENTERED
const String WIFI_PASSWORD = "greenball";        //USER ENTERED
// const String WIFI_SSID = "DESKTOP";          //USER ENTERED
// const String WIFI_PASSWORD = "spot1234";        //USER ENTERED
const String CLOCK_ID = "48";                     //USER ENTERED
// Set thevolume (0-100)
#define VOLUME 12


const String HOST_NAME = "54.190.183.82"; 
const String PATH_NAME = "/alarm_app/requests";
const int BAUD_RATE = 115200;

// Define I2S connections
#define I2S_DOUT  19
#define I2S_BCLK  27
#define I2S_LRC   25
 
// Define button connections
#define BUTTON_SNOOZE_READ 34
#define BUTTON_SNOOZE_WRITE 32
#define BUTTON_RESET_READ 12
#define BUTTON_RESET_WRITE 14


// Create audio object
Audio audio;

// Create RTC time object
DateTime now;

int counter = 0;
String alarm_arr[100];
int toggle_arr[100];
String nearest_alarm = "-1:-1:-1";  // these "-1" values will keep the alarm from alarming if no alarms are set
int nearest_toggle;
int hh;
int mm;
int ss;

static TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
static RTC_DS3231 rtc;


// This establishment also starts a serial.begin()
static ServerClass server(CLOCK_ID, WIFI_SSID, WIFI_PASSWORD, HOST_NAME, PATH_NAME, BAUD_RATE);
String clock_id;



void setup() {
  // Initialize server communication
  server.init();  
  clock_id = server.getID();

  // Initialize screen
  initialize_screen();

  // // Initialize the button read/write pins
  pinMode(BUTTON_SNOOZE_WRITE, OUTPUT);
  pinMode(BUTTON_RESET_WRITE, OUTPUT);
  pinMode(BUTTON_SNOOZE_READ, INPUT);
  pinMode(BUTTON_RESET_READ, INPUT);
  digitalWrite(BUTTON_SNOOZE_WRITE, HIGH);
  digitalWrite(BUTTON_RESET_WRITE, HIGH);


  // Requests initial time from Server
  char currentBuffer[20];
  strcpy(currentBuffer, server.req_clock_time().c_str());
  const char *myD = ":";
  const char *currentHour = strtok(currentBuffer, myD);
  const char *currentMinute = strtok(NULL, myD);
  const char *currentSecond = strtok(NULL, myD);

  // Initialize the rtc object
  rtc.begin();
  if (! rtc.begin()) {
    Serial.println("Could not find RTC! Check circuit.");
    while (1);
  }
  now = rtc.now();
  hh = now.hour();
  mm = now.minute();
  ss = now.second();
  // Hard coding RTC time as Jan 30, 2000
  rtc.adjust(DateTime(2000, 1, 30, atoi(currentHour), atoi(currentMinute), atoi(currentSecond)));

  // Initializes the nearest alarm time
  int alarm_cnt = server.req_alarm_cnt();
    for (int i = 1; i <= alarm_cnt; i++){
      // Enters the database's alarms to local global array
      toggle_arr[i] = server.req_alarm_toggle(i);
      alarm_arr[i] = server.req_alarm_time(i);
      char alarmBuffer[20];
      strcpy(alarmBuffer, alarm_arr[i].c_str());
      const char *myD = ":";
      const char *alarmHour = strtok(alarmBuffer, myD);
      const char *alarmMinute = strtok(NULL, myD);
      const char *alarmSecond = "00";

      if (i == 1) {
        nearest_alarm = server.req_alarm_time(alarm_cnt);
        nearest_toggle = server.req_alarm_toggle(alarm_cnt);
      }
    char nearestBuffer[20];
    strcpy(nearestBuffer, nearest_alarm.c_str());
    const char *nearestHour = strtok(nearestBuffer, myD);
    const char *nearestMinute = strtok(NULL, myD);
    const char *nearestSecond = "00";
  
    // Compare with current time
    int currentHourInt = atoi(currentHour);
    int currentMinuteInt = atoi(currentMinute);
    int alarmHourInt = atoi(alarmHour);
    int alarmMinuteInt = atoi(alarmMinute);
    int nearestHourInt = atoi(nearestHour);
    int nearestMinuteInt = atoi(nearestMinute);

    if ((alarmHourInt > currentHourInt) || 
        (alarmHourInt == currentHourInt && alarmMinuteInt > currentMinuteInt)) {
        // Update nearest_alarm if this alarm is closer
        if (nearest_alarm == "" || 
            (alarmHourInt < nearestHourInt || 
            (alarmHourInt == nearestHourInt && alarmMinuteInt < nearestMinuteInt))) {
            nearest_alarm = alarm_arr[i];
            nearest_toggle = toggle_arr[i];
        }
    }
    // TODO Add nearest roll over


    Serial.printf("Current - %d:%d:%d\n", currentHourInt, currentMinuteInt, atoi(currentSecond));   //TEMP
    Serial.printf("\tAlarm - %d:%d:%d\n", alarmHourInt, alarmMinuteInt, atoi(alarmSecond));   //TEMP
    Serial.printf("\t\tNearest - %d:%d:%d\n", nearestHourInt, nearestMinuteInt, atoi(nearestSecond));   //TEMP
  }



  //Radio setup
  // Connect MAX98357 I2S Amplifier Module
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
 
  // Set thevolume (0-100)
  audio.setVolume(VOLUME);
 
  // Connect to an Internet radio station (select one as desired)
  //audio.connecttohost("http://vis.media-ice.musicradio.com/CapitalMP3");
  //audio.connecttohost("mediaserv30.live-nect MAX98357 I2S Amplifier Module
  //audio.connecttohost("www.surfmusic.de/m3u/100-5-das-hitradio,4529.m3u");
  // audio.connecttohost("stream.1a-webradio.de/deutsch/mp3-128/vtuner-1a");
  // audio.connecttohost("www.antenne.de/webradio/antenne.m3u");
  audio.connecttohost("0n-80s.radionetz.de:8000/0n-70s.mp3");
  Serial.printf("\tIF YOU DO NOT HEAR MUSIC: Reboot the Board By Pressing the \"EN\" button\n");
}

void loop() {
  // while(true){
  //   audio.loop();
  // }
  // Test the radio music connection before normal operation
  while (counter < 70000){
    audio.loop();
    counter++;
  }

  // update visible time only if it differs from current time
  now = rtc.now();
  if (ss != now.second()){
    // Pulls RTC values
    hh = now.hour();
    mm = now.minute();
    ss = now.second();
    update_screen(hh, mm, ss);
  }

  // Only updates alarm times and nearest alarm every ~5 minutes
  // TEMP: *every 1 minute
  if (mm % 1 == 0 && ss > 5 && ss < 10){
    // Requests alarms from database via http GET
    int alarm_cnt = server.req_alarm_cnt();
    // Initializes the nearest alarm time
    for (int i = 1; i <= alarm_cnt; i++){
      now = rtc.now();
      if (ss != now.second()){
        hh = now.hour();
        mm = now.minute();
        ss = now.second();
        update_screen(hh, mm, ss);
      }

      // Enters the database's alarms to local global array
      toggle_arr[i] = server.req_alarm_toggle(i);
      alarm_arr[i] = server.req_alarm_time(i);
      char alarmBuffer[20];
      strcpy(alarmBuffer, alarm_arr[i].c_str());
      const char *myD = ":";
      const char *alarmHour = strtok(alarmBuffer, myD);
      const char *alarmMinute = strtok(NULL, myD);
      const char *alarmSecond = "00";

      if (i == 1) {
        nearest_alarm = server.req_alarm_time(alarm_cnt);
        nearest_toggle = server.req_alarm_toggle(alarm_cnt);
      }
      char nearestBuffer[20];
      strcpy(nearestBuffer, nearest_alarm.c_str());
      const char *nearestHour = strtok(nearestBuffer, myD);
      const char *nearestMinute = strtok(NULL, myD);
      const char *nearestSecond = "00";
    
      // Compare with current time
      int alarmHourInt = atoi(alarmHour);
      int alarmMinuteInt = atoi(alarmMinute);

      if ((alarmHourInt > hh) || 
          (alarmHourInt == hh && alarmMinuteInt > mm)) {
          // Update nearest_alarm if this alarm is closer
          if (nearest_alarm == "" || 
              (alarmHourInt < atoi(nearestHour) || 
              (alarmHourInt == atoi(nearestHour) && alarmMinuteInt < atoi(nearestMinute)))) {
              nearest_alarm = alarm_arr[i];
              nearest_toggle = toggle_arr[i];
          }
      }
      // TODO Add nearest roll over
      Serial.printf("Current - %d:%d:%d\n", hh, mm, ss);   //TEMP
      Serial.printf("\tAlarm - %d:%d:%d\n", alarmHourInt, alarmMinuteInt, atoi(alarmSecond));                 //TEMP
      Serial.printf("\t\tNearest - %d:%d:%d\n", atoi(nearestHour), atoi(nearestMinute), atoi(nearestSecond));   //TEMP
    }
  }
  // now = rtc.now();     //TEMP
  // Serial.printf("Current - %d:%d:%d\n", hh,mm,ss);   //TEMP
  // Serial.printf("CURRENT - %d:%d:%d", now.hour(), now.minute(), now.second());    //TEMP

  char buffer[20];
  strcpy(buffer, nearest_alarm.c_str());
  const char *myD = ":";
  const char *hour = strtok(buffer, myD);
  const char *minute = strtok(NULL, myD);
  const char *second = "00";

  if (hh == atoi(hour) && mm == atoi(minute) && ss == atoi(second)){
    // while (!digitalRead(BUTTON_RESET_READ)){
    while(true){
      Serial.print("ALARMing");     //TEMP
      // only updates if the second changes
      now = rtc.now();
      if (ss != now.second()){
        hh = now.hour();
        mm = now.minute();
        ss = now.second();
        update_screen(hh, mm, ss);
      }
      audio.loop();
      // if snooze enabled and snooze button is pressed
      if (nearest_toggle && digitalRead(BUTTON_SNOOZE_READ)){
        // (Testing purposes snooze = 10sec) Real product shall be 5 minutes
        for (int i = 0; i < 10; i++){
          now = rtc.now();
          hh = now.hour();
          mm = now.minute();
          ss = now.second();
          update_screen(hh, mm, ss);
          delay(1000);
        }
      }
      // if reset button is pressed
      if (digitalRead(BUTTON_RESET_READ)){
        // if reset, find next nearest alarm
        // Requests alarms from database via http GET
        int alarm_cnt = server.req_alarm_cnt();
        // Initializes the nearest alarm time
        for (int i = 1; i <= alarm_cnt; i++){
          // Enters the database's alarms to local global array
          toggle_arr[i] = server.req_alarm_toggle(i);
          alarm_arr[i] = server.req_alarm_time(i);
          char alarmBuffer[20];
          strcpy(alarmBuffer, alarm_arr[i].c_str());
          const char *myD = ":";
          const char *alarmHour = strtok(alarmBuffer, myD);
          const char *alarmMinute = strtok(NULL, myD);
          const char *alarmSecond = "00";

          if (i == 1) {
            nearest_alarm = server.req_alarm_time(alarm_cnt);
            nearest_toggle = server.req_alarm_toggle(alarm_cnt);
          }
          char nearestBuffer[20];
          strcpy(nearestBuffer, nearest_alarm.c_str());
          const char *nearestHour = strtok(nearestBuffer, myD);
          const char *nearestMinute = strtok(NULL, myD);
          const char *nearestSecond = "00";
        
          // Compare with current time
          int alarmHourInt = atoi(alarmHour);
          int alarmMinuteInt = atoi(alarmMinute);

          if ((alarmHourInt > hh) || 
              (alarmHourInt == hh && alarmMinuteInt > mm)) {
              // Update nearest_alarm if this alarm is closer
              if (nearest_alarm == "" || 
                  (alarmHourInt < atoi(nearestHour) || 
                  (alarmHourInt == atoi(nearestHour) && alarmMinuteInt < atoi(nearestMinute)))) {
                  nearest_alarm = alarm_arr[i];
                  nearest_toggle = toggle_arr[i];
              }
          }
          // TODO Add nearest roll over
        }

        break;
      }
    }
  }
}


// Audio status functions
void audio_info(const char *info) {
  Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info) { //id3 metadata
  Serial.print("id3data     "); Serial.println(info);
}
void audio_eof_mp3(const char *info) { //end of file
  Serial.print("eof_mp3     "); Serial.println(info);
}
void audio_showstation(const char *info) {
  Serial.print("station     "); Serial.println(info);
}
void audio_showstreaminfo(const char *info) {
  Serial.print("streaminfo  "); Serial.println(info);
}
void audio_showstreamtitle(const char *info) {
  Serial.print("streamtitle "); Serial.println(info);
}
void audio_bitrate(const char *info) {
  Serial.print("bitrate     "); Serial.println(info);
}
void audio_commercial(const char *info) { //duration in sec
  Serial.print("commercial  "); Serial.println(info);
}
void audio_icyurl(const char *info) { //homepage
  Serial.print("icyurl      "); Serial.println(info);
}
void audio_lasthost(const char *info) { //stream URL played
  Serial.print("lasthost    "); Serial.println(info);
}
void audio_eof_speech(const char *info) {
  Serial.print("eof_speech  "); Serial.println(info);
}
