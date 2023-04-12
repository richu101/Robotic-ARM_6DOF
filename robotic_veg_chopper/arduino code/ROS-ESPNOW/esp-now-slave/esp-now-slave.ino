#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  float fldata;
} struct_message;

struct_message myData;

// call back when data is received

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
memcpy(&myData, incomingData, sizeof(myData));
Serial.print("Int value received: ");
Serial.println(myData.fldata);
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
