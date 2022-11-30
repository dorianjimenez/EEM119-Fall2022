#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

bool led = false;
int rate = 200;

// sample rate of 20 ---> ~26.8 mA
// sample rate of 50 ---> ~26 mA
// sample rate of 100 --> ~24.4 mA


void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  // initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }

}

void loop() {
  
  float ax, ay, az;
  float gx, gy, gz;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }

  if(IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);
  }

  if(led == false) {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    led = true;
    delay(rate);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    led = false;
    delay(rate);    
  }
      

}
