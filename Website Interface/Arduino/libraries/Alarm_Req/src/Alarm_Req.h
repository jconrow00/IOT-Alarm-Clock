/****************************************************
*	Made by: Joseph Conrow
*	for senior capstone project
****************************************************/

#ifndef ALARM_REQ_H
#define ALARM_REQ_H

#include <WiFi.h>
#include <HTTPClient.h>


using namespace std;
 
class ServerClass {
 private:
  String m_clock_id;           //factory set clock id
  String m_wifi_ssid;		    //the local wifi ssid
  String m_wifi_pswd;		    //the local wifi password
  String m_server_ip;		    //the base ip address of server
  String m_handler_folder;	//the path for the folder the handlers will be in
  int m_baud_rate;          //the functioning rate for the ESP32

 public:
  ServerClass( String clock_id, String wifi_ssid, String wifi_pswd, 
              String server_ip, String handler_folder, int baud_rate);

  int req_alarm_cnt();                  //returns number of alarms on clock
  String req_alarm_time(int alarm_num); //returns alarm time of index, alarm_num
  int req_alarm_toggle(int alarm_num);	//returns alarm toggle of index, alarm_num
  
  // returns members
  String getID() { return m_clock_id; } 
  String getSSID() { return m_wifi_ssid; }
  String getPswd() { return m_wifi_pswd; }
  String getIP()  { return m_server_ip; }
  String getHandler() { return m_handler_folder; }
  int getBaud() { return m_baud_rate; }
};

extern ServerClass Server;
// class AlarmClass {
//  private:
  
// };

#endif

