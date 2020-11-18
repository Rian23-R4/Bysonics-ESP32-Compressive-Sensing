void mqttconnect()
{
  int y = 0;
  while (!client.connected())
  {
    Serial.print("MQTT connecting ...");
    String clientId = "ESP32Client";
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed, status code =");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      y++;
      if (y >= 2)
      {
        ESP.restart();
        y = 0;
      }
      delay(5000);
    }
  }
}

void receivedCallback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message received: ");
  Serial.println(topic);
  Serial.print("payload: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
