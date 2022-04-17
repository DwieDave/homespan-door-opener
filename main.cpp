#include <Arduino.h>
#include "HomeSpan.h"
#include "DEV_Switch.h"
#include "DEV_Doorbell.h"
#include "DEV_Identify.h"

// PINS
#define pinLed LED_BUILTIN
#define pinRelay D1
#define pinDoorbell D2

// CONSTANTS
#define sketchVersion "0.9"

void setup() {
  // Hardware Setup
  Serial.begin(115200);

  // HomeSpan Init
  homeSpan.setWifiCredentials("WifiName", "WifiPassword");
  homeSpan.setPairingCode("12233344");
  homeSpan.setSketchVersion(sketchVersion);
  homeSpan.enableOTA();
  homeSpan.begin(Category::Bridges, "Door Opener Bridge");

  // HAP Definitions
  new SpanAccessory();  
    new DEV_Identify("Door Opener Bridge","Developer","7777-7777","DOB1",sketchVersion);
    new Service::HAPProtocolInformation();
      new Characteristic::Version("1.1.0");

  new SpanAccessory();
    new DEV_Identify("Door Opener", "Developer", "7777-7777", "DO1", sketchVersion);
    new DEV_Switch(pinRelay, pinLed);

  new SpanAccessory();
    new DEV_Identify("Doorbell", "Developer", "7777-7777", "DB1", sketchVersion);
    new DEV_Doorbell(pinDoorbell);
}

void loop() {
  homeSpan.poll();
}