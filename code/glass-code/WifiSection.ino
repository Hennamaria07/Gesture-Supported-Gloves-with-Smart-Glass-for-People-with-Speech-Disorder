const char *ssid = "TheProgrammer"; // replace with your wifi ssid and wpa2 key
const char *pass = "09292503ssss";

void WifiInit()
{
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}