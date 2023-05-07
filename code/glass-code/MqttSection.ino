void MqttInit()
{
    client.setServer("raspberrypi.local", 1883);
    client.setCallback(MqttCallBack);
}

void ReConnectMqttServer()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("glassClient"))
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            // client.publish("message","hello world");
            // ... and resubscribe
            client.subscribe("glassData");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            Serial.println("Check port access in laptop");
            Serial.println("Try to open the port in firewall ");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void SendDataToMqtt(char *data)
{
    client.publish("message", data);
}

void MqttCallBack(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    message="";

    for (int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }
    Serial.print(message);
    Serial.println();
}