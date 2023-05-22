#include <esp_now.h>
#include <WiFi.h>
#include <AccelStepper.h>

AccelStepper stepper1(1, 26,27); // driver, step, dir
AccelStepper stepper2(1, 25,23); //
AccelStepper stepper3(1,16,17); //

typedef struct struct_message {
    float joint0;
    float joint1;
    float joint2;
    float joint3;
    float joint4;
    float joint5;
  
} struct_message;

struct_message myData;


// call back when data is received

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
memcpy(&myData, incomingData, sizeof(myData));
  stepper1.moveTo(myData.joint0*21.33);
  stepper2.moveTo(myData.joint1*21.33);
  stepper3.moveTo(myData.joint2*21.33);
Serial.print("Joint0 value received: ");
Serial.println(myData.joint0);
Serial.print("Joint1 value received: ");
Serial.println(myData.joint1);
Serial.print("Joint2 value received: ");
Serial.println(myData.joint2);

// Serial.print("Joint3 value received: ");
// Serial.println(myData.joint3);
// Serial.print("Joint4 value received: ");
// Serial.println(myData.joint4);
// Serial.print("Joint5 value received: ");
// Serial.println(myData.joint5);
}

void setup() {
  Serial.begin(57600);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.println("Setup");
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
  stepper1.setMaxSpeed(200.0);
  stepper1.setAcceleration(50.0);
  stepper1.setCurrentPosition(180*21.33);
  
  stepper2.setMaxSpeed(200.0);
  stepper2.setAcceleration(50.0);
  stepper2.setCurrentPosition(180*21.33);
  
  stepper3.setMaxSpeed(200.0);
  stepper3.setAcceleration(50.0);  
  stepper3.setCurrentPosition(180*21.33);
}

void loop() {
  stepper1.run();
  stepper2.run();
  stepper3.run();
}
