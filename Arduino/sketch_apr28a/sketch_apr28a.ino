/****************************************************
*	Made by: Joseph Conrow, Cade Tillema, Andrew Zellner, Louis Marrun
*	for senior capstone project
****************************************************/

#include <Alarm_Req.h>  //Joseph custom library
#include <RTClib.h>     //RTC library
#include <TFT_eSPI.h>   // Screen library
#include <SPI.h>      

const String WIFI_SSID = "EndyasCurfew";          //USER ENTERED
const String WIFI_PASSWORD = "fivethirty";        //USER ENTERED
const String CLOCK_ID = "48";                     //USER ENTERED


const String HOST_NAME = "54.190.183.82"; 
const String PATH_NAME = "/alarm_app/requests";
const int BAUD_RATE = 115200;

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
RTC_DS3231 rtc;

char days[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int xcolon = 0, xsecs = 0;

// This establishment also starts a serial.begin()
ServerClass server(CLOCK_ID, WIFI_SSID, WIFI_PASSWORD, HOST_NAME, PATH_NAME, BAUD_RATE);



void setup() {
  
  // Initialize server communication
  server.init();  


  // Initialize screen
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_RED, TFT_BLACK);


  // Initialize the rtc object
  rtc.begin();
  if (! rtc.begin()) {
    Serial.println("Could not find RTC! Check circuit.");
    while (1);
  }

  // Requests initial time from Server
  char *MyS = const_cast<char *>(server.req_clock_time().c_str());
  char *MyD = ":";
  char *hours = strtok(MyS, MyD);
  char *minutes = strtok(NULL, MyD);
  char *seconds = strtok(NULL, MyD);

  // Hard coding Jan 30, 2000
  rtc.adjust(DateTime(2000, 1, 30, int(hours), int(minutes), int(seconds)));
}

void loop() {
  
  // Pulls RTC time
  DateTime now = rtc.now();
  int hh = now.hour();
  int mm = now.minute();
  int ss = now.second();

  // Update Screen
  int xpos = 0;
  int ypos = 85; // Top left corner ot clock text, about half way down
  int ysecs = ypos + 24; 
  // Draw hours and minutes
  if (hh < 10) xpos += tft.drawChar('0', xpos, ypos, 8); // Add hours leading zero for 24 hr clock
  xpos += tft.drawNumber(hh, xpos, ypos, 8);             // Draw hours
  xcolon = xpos; // Save colon coord for later to flash on/off later
  xpos += tft.drawChar(':', xpos, ypos - 8, 8);
  if (mm < 10) xpos += tft.drawChar('0', xpos, ypos, 8); // Add minutes leading zero
  xpos += tft.drawNumber(mm, xpos, ypos, 8);             // Draw minutes
  xsecs = xpos; // Save seconds 'x' position for later display updates
  if (ss % 2) { // Flash the colons on/off
    tft.setTextColor(0x39C4, TFT_BLACK);        // Set colour to grey to dim colon
    tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
    xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
    tft.setTextColor(TFT_RED, TFT_BLACK);    // Set colour back to yellow
  }
  else {
    tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
    xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
  }
  //Draw seconds
  if (ss < 10) xpos += tft.drawChar('0', xpos, ysecs, 6); // Add leading zero
  tft.drawNumber(ss, xpos, ysecs, 6);                     // Draw seconds

  

  // TEMP testing
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
