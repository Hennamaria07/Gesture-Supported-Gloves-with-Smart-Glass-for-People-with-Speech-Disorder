
#include <Arduino.h>
#include <WiFi.h>

#include <HTTPClient.h>

// #define USE_SERIAL Serial
// DOIT ESP32 DEVKIT V1

// from thumb

const int RingPin = 34;
const int MiddlePin = 35;
const int IndexPin = 32;
const int ThumbPin = 33;
const int PinkyPin = 39;
// const int ThumbPin = 34;
// const int IndexPin = 35;
// const int MiddlePin = 32;
// const int RingPin = 33;
// const int PinkyPin = 39;

int ThumbReading  = 0;
int IndexReading  = 0;
int MiddleReading = 0;
int RingReading   = 0;
int PinkyReading  = 0;

String baseUrl = "https://script.google.com/macros/s/AKfycbw2MBuNDkzXNLkRK0zF2HY5Y51DLEU5Qm-XNWSFCXzX4O2sJ_5qvwP4I3lDbxv5OWe_/exec";

const char *ssid = "TheProgrammer";
const char *password = "09292503ssss";

void setup()
{
  Serial.begin(9600);
  // WiFi.enableInsecureWEP(true)
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  // Serial.println("\nConnected to the WiFi network");
  // Serial.print("Local ESP32 IP: ");
  // Serial.println(WiFi.localIP());
  
}

void loop()
{
  ReadSensors();
  
  String Thumb = String(ThumbReading);
  String Index = String(IndexReading);
  String Middle = String(MiddleReading);
  String Ring = String(RingReading);
  String Pinky = String(PinkyReading);

  dataSender(Thumb, Index, Middle, Ring, Pinky, "A");
  // delay(500);
}

void dataSender(String Thumb, String Index, String Middle, String Ring, String Pinky, String Letter)
{
  // sends data to google sheet
  String Url = baseUrl + "?Thumb=" + Thumb + "&";
  Url += "&Index=" + Index + "&";
  Url += "&Middle=" + Middle + "&";
  Url += "&Ring=" + Ring + "&";
  Url += "&Pinky=" + Pinky + "&";
  Url += "&Letter=" + Letter;

  HTTPClient http;
  // configure traged server and url
  // http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
  http.begin(Url); // HTTP
  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... success : %d\n", httpCode);
    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      Serial.println(payload);
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void ReadSensors()
{
  ThumbReading = analogRead(ThumbPin);
  IndexReading = analogRead(IndexPin);
  MiddleReading = analogRead(MiddlePin);
  RingReading = analogRead(RingPin);
  PinkyReading = analogRead(PinkyPin);
  Serial.println();
  Serial.print("Thumb : ");
  Serial.print(ThumbReading);
  Serial.print(", Index : ");
  Serial.print(IndexReading);
  Serial.print(", Middle : ");
  Serial.print(MiddleReading);
  Serial.print(", Ring : ");
  Serial.print(RingReading);
  Serial.print(", Pinky : ");
  Serial.print(PinkyReading);
}

// https://script.google.com/macros/s/AKfycbw2MBuNDkzXNLkRK0zF2HY5Y51DLEU5Qm-XNWSFCXzX4O2sJ_5qvwP4I3lDbxv5OWe_/exec