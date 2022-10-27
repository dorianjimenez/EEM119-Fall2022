#include <Arduino_LSM6DS3.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

}

void loop() {
  float ax, ay, az;
  float gx, gy, gz;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);

    Serial.print("ax: ");
    Serial.print(ax);
    Serial.print('\t');
    Serial.print("ay: ");
    Serial.print(ay);
    Serial.print('\t');
    Serial.print("az: ");
    Serial.print(az);
    Serial.print('\t');
  }

  if(IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);

    Serial.print("gx: ");
    Serial.print(gx);
    Serial.print('\t');
    Serial.print("gy: ");
    Serial.print(gy);
    Serial.print('\t');
    Serial.print("gz: ");
    Serial.println(gz);
  }

  delay(200);
}
