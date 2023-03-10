/*****************************************************************
  TG-Music - WiFi-clock Template for ESP8266

  Based on: NTP TZ DST - bare minimum
  NetWork Time Protocol - Time Zone - Daylight Saving Time
  https://werner.rothschopf.net/202011_arduino_esp8266_ntp_en.htm
  
  Code by http://tg-music.neocities.org
  potatopasty@pm.me
******************************************************************/

/* Necessary Includes */

#include <ESP8266WiFi.h>            // we need wifi to get internet access
#include <WifiUDP.h>
#include <time.h>                   // time() ctime()
#include <WiFiManager.h>            // Use this, do not hard code your wifi name and password
#include <NTPClient.h>

/* Configuration of NTP */
#define MY_NTP_SERVER "europe.pool.ntp.org"      // Europe   https://www.pool.ntp.org
#define MY_TZ "EET-2EEST,M3.5.0/3,M10.5.0/4"     // Helsinki https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv

/* Display update interval 1 second */
unsigned long previousMillis = 0;
const long interval = 1000;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, MY_NTP_SERVER);

/* Globals */
time_t now;                         // this is the epoch
tm tm;                              // the structure tm holds time information in a more convient way

void showTime() {
  time(&now);                       // read the current time
  localtime_r(&now, &tm);           // update the structure tm with the current time
  Serial.print("year:");
  Serial.print(tm.tm_year + 1900);  // years since 1900
  Serial.print("\tmonth:");
  Serial.print(tm.tm_mon + 1);      // January = 0 (!)
  Serial.print("\tday:");
  Serial.print(tm.tm_mday);         // day of month
  Serial.print("\thour:");
  Serial.print(tm.tm_hour);         // hours since midnight  0-23
  Serial.print("\tmin:");
  Serial.print(tm.tm_min);          // minutes after the hour  0-59
  Serial.print("\tsec:");
  Serial.print(tm.tm_sec);          // seconds after the minute  0-61*
  Serial.print("\twday");
  Serial.print(tm.tm_wday);         // days since Sunday 0-6
  if (tm.tm_isdst == 1)             // Daylight Saving Time flag
    Serial.print("\tDST");
  else
    Serial.print("\tstandard");
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial.println("\nWiFi-clock");

  configTime(MY_TZ, MY_NTP_SERVER); // --> Here is the IMPORTANT ONE LINER needed in your sketch!

  // Set your own password and network name. IP-Address: 192.168.4.1 for Wifi setup.
  WiFiManager wifiManager;
  wifiManager.autoConnect("AP-NAME", "AP-PASSWORD");

  // start network
  WiFi.begin();
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print ( "." );
  }
  Serial.println("\nWiFi connected");
  // by default, the NTP will be started after 60 secs
}

void loop() {

  /* Show time on display, and update every second */

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {

    showTime();  // Show time and date in serial monitor (115200 baud)

    // Display hours
    // (tm.tm_hour);

    // Display minutes
    // (tm.tm_min);

    // Display seconds
    // (tm.tm_sec);
    previousMillis = currentMillis;
  }
}
