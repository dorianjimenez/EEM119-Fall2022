// Make sure you run the Node.js code, then run the Arduino code after.

#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>
#include <LinkedList.h>

#define BLE_UUID_ACCELEROMETER_SERVICE "1200"
#define JUMPING_JACK "2101"
#define MOTION_COUNT "2102"


#define BLE_DEVICE_NAME "Dorian's Arduino"
#define BLE_LOCAL_NAME "Dorian's Arduino"

BLEService bleService(BLE_UUID_ACCELEROMETER_SERVICE);

BLEFloatCharacteristic jumpingJack(JUMPING_JACK, BLERead | BLENotify);
BLEFloatCharacteristic motionCount(MOTION_COUNT, BLERead | BLENotify);


LinkedList<float> linkedList_gz = LinkedList<float>();
LinkedList<float> linkedList_ax = LinkedList<float>();
LinkedList<float> linkedList_ay = LinkedList<float>();
LinkedList<float> linkedList_az = LinkedList<float>();
int count = 0;

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

  // Want a LinkedList of max size 50 (2 seconds worth of data, given 40ms sampling rate)
  while(linkedList_gz.size() < 50) {
    linkedList_gz.add(0);
  }

  // Want a LinkedList of max size 10
  while(linkedList_ax.size() < 10) {
    linkedList_ax.add(0);
  }

  // Want a LinkedList of max size 10
  while(linkedList_ay.size() < 10) {
    linkedList_ay.add(0);
  }

  // Want a LinkedList of max size 10
  while(linkedList_az.size() < 10) {
    linkedList_az.add(0);
  }

  Serial.println("BLE Accelerometer Peripheral");

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

bool check_a_values(LinkedList<float> &linkedList_ax, LinkedList<float> &linkedList_ay, LinkedList<float> &linkedList_az) {
  bool ax_check = false;
  bool ay_check = false;
  bool az_check = false;

  // for(int i = 0; i < 10; i++) {
  //   int value = linkedList_ax.get(i);
  //   if(value <= -1) {
  //     ax_check = true;
  //     break;
  //   }
  // }
  ax_check = true;

  for(int i = 0; i < 10; i++) {
    int value = linkedList_ay.get(i);
    if(value >= 2) {
      ay_check = true;
      break;
    }
  }

  // for(int i = 0; i < 10; i++) {
  //   int value = linkedList_az.get(i);
  //   if(value >= 1.0) {
  //     az_check = true;
  //     break;
  //   }
  // }
  az_check = true;

  Serial.print(ax_check);
  Serial.print("   ");
  Serial.print(ay_check);
  Serial.print("   ");
  Serial.println(az_check);
  

  if(ax_check && ay_check && az_check) {
    return true;
  }
  return false;
}

bool jumping_jack(LinkedList<float> &linkedList_gz, LinkedList<float> &linkedList_ax, LinkedList<float> &linkedList_ay, LinkedList<float> &linkedList_az) {
  bool motion1 = false;
  bool motion2 = false;
  for(int i = 0; i < 50; i++) {
    float value = linkedList_gz.get(i);

    if(motion1 == false) {
      if(value <= -225) {
        motion1 = true;
        continue;
      }
    }
    else {
      if(value >= 225) {
        if(check_a_values(linkedList_ax, linkedList_ay, linkedList_az)) {
          return true;
        }
        else {
          return false;
        }
      }
    }
    
  }
  
  return false;
}

void loop() {

  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  // if (central) {

    // Serial.print("Connected to central: ");
    // Serial.println();

    float ax, ay, az;
    float gx, gy, gz;

    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(ax, ay, az);
    }

    if(IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(gx, gy, gz);
    }

    linkedList_gz.remove(0);
    linkedList_gz.add(gz);

    linkedList_ax.remove(0);
    linkedList_ax.add(ax);

    linkedList_ay.remove(0);
    linkedList_ay.add(ay);

    linkedList_az.remove(0);
    linkedList_az.add(az);

    Serial.print(gz);
    Serial.print("   ");
    Serial.print(ax);
    Serial.print("   ");
    Serial.print(ay);
    Serial.print("   ");
    Serial.println(az);


    if(jumping_jack(linkedList_gz, linkedList_ax, linkedList_ay, linkedList_az)) {
      Serial.println("jumpingJack");
      count++;
      linkedList_gz.clear();
      linkedList_ax.clear();
      linkedList_ay.clear();
      linkedList_az.clear();
      // Want a LinkedList of max size 50 (2 seconds worth of data, given 40ms sampling rate)
      while(linkedList_gz.size() < 50) {
        linkedList_gz.add(0);
      }

      // Want a LinkedList of max size 10
      while(linkedList_ax.size() < 10) {
        linkedList_ax.add(0);
      }

      // Want a LinkedList of max size 10
      while(linkedList_ay.size() < 10) {
        linkedList_ay.add(0);
      }

      // Want a LinkedList of max size 10
      while(linkedList_az.size() < 10) {
        linkedList_az.add(0);
      }
    }

    delay(40);
  // }
}
