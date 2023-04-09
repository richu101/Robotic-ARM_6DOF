#include <WiFi.h>

void setup(){
    // blink debug LED
    pinMode(2, OUTPUT);
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);
    Serial.println("ESP32 MAC Address");
    Serial.println(WiFi.macAddress());
}

void loop(){
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
    Serial.println("ESP32 MAC Address");
    Serial.println(WiFi.macAddress());
}