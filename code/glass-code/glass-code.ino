#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

WiFiClient wifiClient;
// Wifi library initialization
PubSubClient client(wifiClient);
// Mqtt library initialization

String message="";
String lines[3];

void setup()
{
  Serial.begin(9600);
  delay(10);
  DisplayInit();
  WifiInit();
  // connects to wifi
  MqttInit(); 
  // connects to mqtt server

// display start
    // if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
    // {
    //   Serial.println(F("SSD1306 allocation failed"));
    //   for(;;);
    // }
  delay(2000);
    
  //   display.ssd1306_command(0xA0);
  // display.clearDisplay();
  // display end
}

void loop()
{
  if (!client.connected()) {
    // if mqtt client is not connected calls the reconnect function
    ReConnectMqttServer();
  }  
  DataProcessing(message);
  ShowOnDisplay(lines[0], lines[1], lines[2]);
  client.loop();
  // delay(100);
}