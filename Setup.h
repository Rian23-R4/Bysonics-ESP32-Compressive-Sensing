void Wifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    y++;
    delay(500);
    Serial.print(" ");
    if (y >= 11)
    {
      ESP.restart();
      y = 0;
    }
    Serial.print(y);
  }
  Serial.println("Connection established!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void mqtt()
{
  client.setServer(mqtt_server, 1883);
  client.setCallback(receivedCallback);
  if (!client.connected())
  {
    mqttconnect();
  }
}

void config_I2C_Accelerometer()
{
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B);                 // PWR_MGMT_1 register
  Wire.write(0);                    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
void config_I2C_Oximeter()
{
  Wire.beginTransmission(MPU_ADDR_Oximeter); // Begins a transmission to the I2C slave (GY-521 board)
  if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false)
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1)
      ;
  }
  byte ledBrightness = 70; //Options: 0=Off to 255=50mA
  byte sampleAverage = 1;  //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 3;        //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  int sampleRate = 400;    //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 69;     //Options: 69, 118, 215, 411
  int adcRange = 16384;    //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
//  particleSensor.setup();
  Wire.endTransmission(true);
}
