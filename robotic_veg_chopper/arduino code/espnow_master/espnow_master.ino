#include <esp_now.h>
#include <WiFi.h>

int int_val;
float float_val;
bool bool_val =  true;

// MAC address of the receiver 2
// esp 2 E8:DB:84:17:3C:38   {0xE8, 0xDB, 0x84, 0x17, 0x3C, 0x38}
// esp 1 C0:49:EF:FA:0D:BC   {0xC0, 0x49, 0xEF, 0xFA, 0x0D, 0xBC}

uint8_t broadcastAddress[] = {0xC0, 0x49, 0xEF, 0xFA, 0x0D, 0xBC};

typedef struct struct_message {
  int int_val;
  float float_val;
  bool bool_val;
} struct_message;

struct_message myData;
 
 //peer information
 esp_now_peer_info_t slave1;

 // callback function that will be executed when data is sent 

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  // Register peer
  memcpy(slave1.peer_addr, broadcastAddress, 6);
  slave1.channel = 0; // pick a channel
  slave1.encrypt = false;
  // add peer
  if (esp_now_add_peer(&slave1) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
    myData.int_val = int_val;
    myData.float_val = float_val;
    myData.bool_val = bool_val;
  // send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
  delay(1000);
  int_val++;
  float_val += 0.1;
  bool_val = !bool_val;
}



