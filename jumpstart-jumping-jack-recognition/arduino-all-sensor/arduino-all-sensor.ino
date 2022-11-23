// Make sure you run the Node.js code, then run the Arduino code after.

#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

#define BLE_UUID_ACCELEROMETER_SERVICE "1200"
#define JUMPING_JACK "2101"
#define MOTION_COUNT "2102"


#define BLE_DEVICE_NAME "Dorian's Arduino"
#define BLE_LOCAL_NAME "Dorian's Arduino"

BLEService bleService(BLE_UUID_ACCELEROMETER_SERVICE);

BLEFloatCharacteristic jumpingJack(JUMPING_JACK, BLERead | BLENotify);
BLEFloatCharacteristic motionCount(MOTION_COUNT, BLERead | BLENotify);

float x, y, z;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  // initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }

  // print_values_to_serial_csv("gz");          

  // initialize BLE
  if (!BLE.begin()) {
    Serial.println("Starting Bluetooth® Low Energy module failed!");
    while (1)
      ;
  }

  // set advertised local name and service UUID
  BLE.setLocalName("Dorian's Arduino");
  BLE.setAdvertisedService(BLE_UUID_ACCELEROMETER_SERVICE);
  

  // add characteristics and service
  bleService.addCharacteristic(jumpingJack);
  bleService.addCharacteristic(motionCount);

  BLE.addService(bleService);


  // start advertising
  BLE.advertise();

}

void print_values_to_serial_csv(String value) {

  float ax, ay, az;
  float gx, gy, gz;

  while(true) {

    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(ax, ay, az);

      if(value == "ax") {
        Serial.println(ax); 
      }
      
      else if(value == "ay") {
        Serial.println(ay);
      }

      else if(value == "az") {
        Serial.println(az);
      }

    }

    if(IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(gx, gy, gz);

      if(value == "gx") {
        Serial.println(gx); 
      }
      
      else if(value == "gy") {
        Serial.println(gy);
      }

      else if(value == "gz") {
        Serial.println(gz);
      }
      
    }

  }
}

void loop() {

  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {

    Serial.print("Connected to central: ");
    Serial.println();

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
      Serial.print('\t');
      Serial.println();

    }

    


    delay(40);
  }
}
