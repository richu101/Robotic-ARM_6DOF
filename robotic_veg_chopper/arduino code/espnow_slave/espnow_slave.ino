#include <esp_now.h>
#include <WiFi.h>

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
Serial.print("Joint0 value received: ");
Serial.println(myData.joint0);
Serial.print("Joint1 value received: ");
Serial.println(myData.joint1);
Serial.print("Joint2 value received: ");
Serial.println(myData.joint2);
Serial.print("Joint3 value received: ");
Serial.println(myData.joint3);
Serial.print("Joint4 value received: ");
Serial.println(myData.joint4);
Serial.print("Joint5 value received: ");
Serial.println(myData.joint5);
}

void setup() {
  Serial.begin(115200);
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
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}
