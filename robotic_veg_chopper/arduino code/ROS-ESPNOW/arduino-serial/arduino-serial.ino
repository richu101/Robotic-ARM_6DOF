#include <ros.h>
#include <std_msgs/Float32.h>
#include <ESP32Servo.h> 
#include <esp_now.h>
#include <WiFi.h>
typedef struct struct_message {
  float fldata;
} struct_message;

struct_message myData;

ros::NodeHandle  nh;

// MAC address of the receiver 2
// esp 2 E8:DB:84:17:3C:38   {0xE8, 0xDB, 0x84, 0x17, 0x3C, 0x38}
// esp 1 C0:49:EF:FA:0D:BC   {0xC0, 0x49, 0xEF, 0xFA, 0x0D, 0xBC}

uint8_t broadcastAddress[] = {0xC0, 0x49, 0xEF, 0xFA, 0x0D, 0xBC}; // esp 1 slave



void messageCb( const std_msgs::Float32& float_msg){
  myData.fldata = float_msg.data;
  if (myData.fldata == 5)
  {
    digitalWrite(2, !digitalRead(2));
  }
  
  send_data();
}
ros::Subscriber<std_msgs::Float32> sub("chatter", &messageCb );
esp_now_peer_info_t slave1;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void send_data() {
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
}

void setup(){
  nh.initNode();
  nh.subscribe(sub);
  Serial.begin(57600);
  pinMode(2, OUTPUT);
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
void loop(){
  nh.spinOnce();
  delay(1);
}