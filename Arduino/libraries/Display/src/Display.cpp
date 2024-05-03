/*
 An example digital clock using a TFT LCD screen to show the time.
 Demonstrates use of the font printing routines. (Time updates but date does not.)

 It uses the time of compile/upload to set the time
 For a more accurate clock, it would be better to use the RTClib library.
 But this is just a demo...

 Make sure all the display driver and pin connections are correct by
 editing the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################

 Based on clock sketch by Gilchrist 6/2/2014 1.0

A few colour codes:

code	color
0x0000	Black
0xFFFF	White
0xBDF7	Light Gray
0x7BEF	Dark Gray
0xF800	Red
0xFFE0	Yellow
0xFBE0	Orange
0x79E0	Brown
0x7E0	Green
0x7FF	Cyan
0x1F	Blue
0xF81F	Pink

 */

#include "Display.h"
#define TFT_GREY 0x5AEB

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

uint32_t targetTime = 0;                    // for next 1 second timeout

//uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3), ss = conv2d(__TIME__ + 6); // Get H, M, S from compile time

int omm = 99, oss = 99;
int xcolon = 0, xsecs = 0;
unsigned int colour = 0;

void initialize_screen(void) {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
}


void update_screen(int hh, int mm, int ss){
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
  // if (ss % 2) { // Flash the colons on/off
  //   tft.setTextColor(0x39C4, TFT_BLACK);        // Set colour to grey to dim colon
  //   tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
  //   xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
  //   tft.setTextColor(TFT_RED, TFT_BLACK);    // Set colour back to yellow
  // }
  // else {
    tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
    xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
  // }
  //Draw seconds
  if (ss < 10) xpos += tft.drawChar('0', xpos, ysecs, 6); // Add leading zero
  tft.drawNumber(ss, xpos, ysecs, 6);                     // Draw seconds
}
