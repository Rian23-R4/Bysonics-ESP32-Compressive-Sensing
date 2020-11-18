void functionCS(double vRealF[DATA_SIZE], double HvRealF[DATA_SIZE], double HvImagF[DATA_SIZE])
{
  memset(vImagF, 0, sizeof(vImagF));
  FFT.Compute(vRealF, vImagF, samples, FFT_FORWARD);
  int temp = 0;
  for (int j = 0; j < DATA_Y; j++)
  {
    for (int t = 0; t < DATA_X; t++)
    {
      HvRealF[j] = HvRealF[j] + (dgaussian[temp] * vRealF[t]);
      HvImagF[j] = HvImagF[j] + (dgaussian[temp] * vImagF[t]);
      temp += 1;
    }
  }
}
void functionSend(double HvRealF[DATA_SIZE], double HvImagF[DATA_SIZE], char topic[100])
{
  client.publish(TOPIC, topic);
  for (int j = 0; j < DATA_Y; j++)
  {
    if (!client.connected())
    {
      mqttconnect();
    }
    client.loop();
    if (!isnan(HvRealF[j]))
    {
      snprintf(Send, 100, "%.0f,%.0f", HvRealF[j], HvImagF[j]);
      client.publish(TOPIC, Send);
    }
  }
}

void SendAndCS() {
  functionCS(vRealOximeter, HvReal, HvImag);
  functionSend(HvReal, HvImag, "Start,PPG");
  memset(HvReal, 0, sizeof(HvReal));
  memset(HvImag, 0, sizeof(HvImag));
  functionCS(vRealEKG, HvReal, HvImag);
  functionSend(HvReal, HvImag, "Start,EKG");
  memset(HvReal, 0, sizeof(HvReal));
  memset(HvImag, 0, sizeof(HvImag));
  functionCS(vRealAccelerometerx, HvReal, HvImag);
  functionSend(HvReal, HvImag, "Start,AcX");
  memset(HvReal, 0, sizeof(HvReal));
  memset(HvImag, 0, sizeof(HvImag));
  functionCS(vRealAccelerometery, HvReal, HvImag);
  functionSend(HvReal, HvImag, "Start,AcY");
  memset(HvReal, 0, sizeof(HvReal));
  memset(HvImag, 0, sizeof(HvImag));
  functionCS(vRealAccelerometerz, HvReal, HvImag);
  functionSend(HvReal, HvImag, "Start,AcZ");
  memset(HvReal, 0, sizeof(HvReal));
  memset(HvImag, 0, sizeof(HvImag));
  functionCS(vRealMyoware, HvReal, HvImag);
  functionSend(HvReal, HvImag, "Start,Myo");
  memset(HvReal, 0, sizeof(HvReal));
  memset(HvImag, 0, sizeof(HvImag));
  functionCS(vRealTemperature, HvReal, HvImag);
  functionSend(HvReal, HvImag, "Start,Tmp");
  memset(HvReal, 0, sizeof(HvReal));
  memset(HvImag, 0, sizeof(HvImag));
  client.publish(TOPIC, "END");
}
