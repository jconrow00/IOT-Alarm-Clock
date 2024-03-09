/****************************************************
*	Made by: Joseph Conrow
*	for senior capstone project
****************************************************/
#include "Alarm_Req.h"


using namespace std;
ServerClass::ServerClass(String clock_id, String wifi_ssid, String wifi_pswd, 
						 String server_ip, String handler_folder, int baud_rate)
	: m_clock_id { clock_id }
	, m_wifi_ssid{ wifi_ssid }
	, m_wifi_pswd{ wifi_pswd }
	, m_server_ip{ server_ip }
	, m_handler_folder{ handler_folder }
	, m_baud_rate { baud_rate }
{
  	// Connect to local WiFi
  Serial.begin(m_baud_rate);
  delay(500);
  WiFi.begin(m_wifi_ssid, m_wifi_pswd);
  Serial.println("");
  Serial.println("Connecting");
  int timeout = 0;
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    timeout++;
    if (timeout > 35){
      Serial.println("");
      Serial.println("Connection Timeout, Try Again");
      timeout = 0;
    }
  } 
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

int ServerClass::req_alarm_cnt(){
      // Connect to the server to get alarm count
  HTTPClient http;
  http.begin("http://" + m_server_ip + m_handler_folder + "/alarm_count.php" + "?" + "id=" + m_clock_id); //HTTP
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      http.end();
      return(atoi(payload.c_str()));
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      http.end();
      return (-1);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    http.end();
    return(-1);
  }
}

String ServerClass::req_alarm_time(int alarm_num){
  if (alarm_num > req_alarm_cnt() || alarm_num < 1){
    Serial.printf("ERROR: selected alarm does not exist\n");
    return ("-1");
  }
      // Connect to the server to get alarm count
  HTTPClient http;
  http.begin("http://" + m_server_ip + m_handler_folder + "/alarm_time.php" + "?" + "id=" + m_clock_id + "&alarm=" + alarm_num); //HTTP
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      http.end();
      return(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      http.end();
      return ("-1");
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    http.end();
    return("-1");
  }
}

int ServerClass::req_alarm_toggle(int alarm_num){
 if (alarm_num > req_alarm_cnt() || alarm_num < 1){
    Serial.printf("ERROR: selected alarm does not exist\n");
    return (-1);
  }
      // Connect to the server to get alarm count
  HTTPClient http;
  http.begin("http://" + m_server_ip + m_handler_folder + "/alarm_toggle.php" + "?" + "id=" + m_clock_id + "&alarm=" + alarm_num); //HTTP
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      http.end();
      return(atoi(payload.c_str()));
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      http.end();
      return (-1);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    http.end();
    return(-1);
  }
}

// AlarmClass::AlarmClass()
// {  
// }

