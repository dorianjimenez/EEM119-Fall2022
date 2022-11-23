// Make sure you run the Node.js code, then run the Arduino code after.

#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

#define BLE_UUID_ACCELEROMETER_SERVICE "1101"
#define BLE_UUID_ACCELEROMETER_X "2101"
#define BLE_UUID_ACCELEROMETER_Y "2102"
#define BLE_UUID_ACCELEROMETER_Z "2103"
#define BLE_UUID_GYROSCOPE_X "2104"
#define BLE_UUID_GYROSCOPE_Y "2105"
#define BLE_UUID_GYROSCOPE_Z "2106"

#define BLE_DEVICE_NAME "Dorian's Arduino"
#define BLE_LOCAL_NAME "Dorian's Arduino"

BLEService bleService(BLE_UUID_ACCELEROMETER_SERVICE);

BLEFloatCharacteristic accelerometerCharacteristicX(BLE_UUID_ACCELEROMETER_X, BLERead | BLENotify);
BLEFloatCharacteristic accelerometerCharacteristicY(BLE_UUID_ACCELEROMETER_Y, BLERead | BLENotify);
BLEFloatCharacteristic accelerometerCharacteristicZ(BLE_UUID_ACCELEROMETER_Z, BLERead | BLENotify);
BLEFloatCharacteristic gyroscopeCharacteristicX(BLE_UUID_GYROSCOPE_X, BLERead | BLENotify);
BLEFloatCharacteristic gyroscopeCharacteristicY(BLE_UUID_GYROSCOPE_Y, BLERead | BLENotify);
BLEFloatCharacteristic gyroscopeCharacteristicZ(BLE_UUID_GYROSCOPE_Z, BLERead | BLENotify);

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

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");

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
  bleService.addCharacteristic(accelerometerCharacteristicX);
  bleService.addCharacteristic(accelerometerCharacteristicY);
  bleService.addCharacteristic(accelerometerCharacteristicZ);
  bleService.addCharacteristic(gyroscopeCharacteristicX);
  bleService.addCharacteristic(gyroscopeCharacteristicY);
  bleService.addCharacteristic(gyroscopeCharacteristicZ);

  BLE.addService(bleService);


  // start advertising
  BLE.advertise();

  Serial.println("BLE Accelerometer Peripheral");
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

      
      accelerometerCharacteristicX.writeValue(ax);
      accelerometerCharacteristicY.writeValue(ay);
      accelerometerCharacteristicZ.writeValue(az);
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

      gyroscopeCharacteristicX.writeValue(gx);
      gyroscopeCharacteristicY.writeValue(gy);
      gyroscopeCharacteristicZ.writeValue(gz);
    }

    


    delay(40);
  }
}
