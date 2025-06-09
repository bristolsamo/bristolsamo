#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Replace with your Blynk authentication token
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";

// Replace with your Wi-Fi credentials
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// Relay pins on the ESP32 (NodeMCU style numbering)
const int relayPins[6] = {2, 4, 5, 13, 12, 14};

LiquidCrystal_I2C lcd(0x27, 20, 4); // change address if needed

void setupRelays() {
  for (int i = 0; i < 6; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // start all relays off
  }
}

void updateLCD() {
  lcd.clear();
  for (int i = 0; i < 6; i++) {
    int row = i / 2;        // two relays per LCD row
    int col = (i % 2) * 10; // columns 0 or 10
    lcd.setCursor(col, row);
    lcd.print("R");
    lcd.print(i + 1);
    lcd.print(":");
    lcd.print(digitalRead(relayPins[i]) ? "ON " : "OFF");
  }
}

BLYNK_WRITE(V1) { digitalWrite(relayPins[0], param.asInt()); updateLCD(); }
BLYNK_WRITE(V2) { digitalWrite(relayPins[1], param.asInt()); updateLCD(); }
BLYNK_WRITE(V3) { digitalWrite(relayPins[2], param.asInt()); updateLCD(); }
BLYNK_WRITE(V4) { digitalWrite(relayPins[3], param.asInt()); updateLCD(); }
BLYNK_WRITE(V5) { digitalWrite(relayPins[4], param.asInt()); updateLCD(); }
BLYNK_WRITE(V6) { digitalWrite(relayPins[5], param.asInt()); updateLCD(); }

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL
  lcd.init();
  lcd.backlight();
  setupRelays();
  updateLCD();
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
