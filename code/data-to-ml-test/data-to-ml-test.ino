
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// #########################
// allow port permission in laptop if is not enabled
// #########################

int ThumbReading  = 0;
int IndexReading  = 0;
int MiddleReading = 0;
int RingReading   = 0;
int PinkyReading  = 0;

int16_t accelerometer_x, accelerometer_y, accelerometer_z; 
// used to store accelero meter values

const char *ssid = "TheProgrammer";
const char *password = "09292503ssss";


WiFiClient espClient;
PubSubClient client(espClient);
// IPAddress server(192,168,1,103);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  client.setServer("raspberrypi.local", 1883);
  client.setCallback(MqttCallBack);

  InitializeAccleroMeter();
}

void loop()
{
  if (!client.connected()) {
    ReConnectMqttServer();
  }

  ReadFlexSensors();
  ReadAcceleroMeter();
  char* char_array = ProcessDataToSend();
  SendDataToMqtt(char_array);
  delay(100);
  client.loop();
}

char* ProcessDataToSend () 
{
  String Thumb = String(ThumbReading);
  String Index = String(IndexReading);
  String Middle = String(MiddleReading);
  String Ring = String(RingReading);
  String Pinky = String(PinkyReading);

  String Ax = String(accelerometer_x);
  String Ay = String(accelerometer_y);

  String dataToSend = Thumb+':';
  dataToSend= dataToSend+Index+":";
  dataToSend= dataToSend+Middle + ":";
  dataToSend= dataToSend+Ring + ":";
  dataToSend= dataToSend+Pinky + ":";
  dataToSend= dataToSend+Ax + ":";
  dataToSend= dataToSend+Ay ;

  int length = dataToSend.length();
  
  char* char_array = new char[length + 1];
  
  strcpy(char_array, dataToSend.c_str());
  return char_array;
}
