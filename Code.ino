#include "arduinoFFT.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "MAX30105.h"
#include "Gaussian52x129.h"
#define DATA_SIZE 256
#define DATA_X 129
#define DATA_Y 52
#define TOPIC "ESP1"
const uint16_t samples = DATA_SIZE;

arduinoFFT FFT = arduinoFFT();
WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid = "AP-Bysonics";
const char* password = "1234567890";
const char* mqtt_server = "10.3.141.1";

#include "Pin.h"
#include "Variable.h"
#include "MQTT.h"
#include "Send.h"
#include "Setup.h"
void setup()
{
  Serial.begin(115200);

  Wifi();
  mqtt();
  Wire.begin(sdaPin, sclPin);
  config_I2C_Accelerometer();
  config_I2C_Oximeter();

  xTaskCreatePinnedToCore(
    coreTaskOne,
    "coreTaskOne",
    10000,
    NULL,
    1,
    NULL,
    taskCoreOne);
  delay(500);
}

void loop()
{
  long times1 = millis();
  Serial.println(timedelay);
  for (int t = 0 ; t < DATA_SIZE; t++) {
//    long times2 = millis();
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
    Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
    Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers
    accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
    accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
    accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
    particleSensor.check(); //Check the sensor
    vRealOximeter[t] = particleSensor.getRed();
    vRealEKG[t] = analogRead(SENSOR_EKG);
    vRealMyoware[t] = analogRead(SENSOR_EMG);
    vRealAccelerometerx[t] = accelerometer_x;
    vRealAccelerometery[t] = accelerometer_y;
    vRealAccelerometerz[t] = accelerometer_z;
    vRealTemperature[t] = Temperature;
    particleSensor.nextSample();
    delay(timedelay);
//    Serial.print(t);  Serial.print(" | Time One Sempling Data = "); Serial.print(millis() - times2); Serial.println("ms");
  }
  long end1 = millis();
  Serial.println("Start CS and Send Data Task 1");
  Serial.print(" | Time Sempling Data = "); Serial.print(millis() - times1); Serial.println("ms");
  long times3 = millis();
  SendAndCS();
  //  Serial.print(" | Time CS and Send Data = "); Serial.print(millis() - times3); Serial.println("ms");
  //  Serial.print(" | Total Time = "); Serial.print(millis() - times1); Serial.println("ms");
  if (((end1 - times1) < 4995) or ((end1 - times1) > 5005)) {
    timedelay = ((5000 * timedelay) / (end1 - times1) );
  }
}

void coreTaskOne( void * pvParameters ) {
  while (true) {
    sensors.requestTemperatures();
    Temperature = sensors.getTempCByIndex(0);
  }
}
