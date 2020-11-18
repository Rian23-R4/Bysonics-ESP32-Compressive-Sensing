const int oneWireBus = 5; //suhu

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

#define SENSOR_EKG 32

#define SENSOR_EMG 34

MAX30105 particleSensor;
const int MPU_ADDR_Oximeter = 0x57;

#define sdaPin 4
#define sclPin 0
const int MPU_ADDR = 0x68;
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z;                            // variables for gyro raw data
int16_t temperature;                                       // variables for temperature data
char tmp_str[7];                                           // temporary variable used in convert function
char *convert_int16_to_str(int16_t i)
{ // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
