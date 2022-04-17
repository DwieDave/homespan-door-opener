#include "HomeSpan.h"

#define relayTime 2000
#define relayOff LOW
#define ledOff LOW

struct DEV_Switch : Service::Switch {

    int relayPin;
    int ledPin;
    SpanCharacteristic* door;

    DEV_Switch(int relayPin, int ledPin) : Service::Switch() {
        this->relayPin = relayPin;
        this->ledPin = ledPin;
        door = new Characteristic::On();

        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, ledOff);

        pinMode(relayPin, OUTPUT);
        digitalWrite(relayPin, relayOff);
    }

    boolean update() {
        // Get new Value
        int newVal = door->getNewVal();
        // Set Relay & LED Pin accordingly
        digitalWrite(relayPin, newVal ? !relayOff : relayOff);
        digitalWrite(ledPin, newVal ? !ledOff : ledOff);
        // If setted on delay relayTime and set everything to false
        if (newVal) {
            delay(relayTime);
            door->setVal(!newVal);
            digitalWrite(relayPin, relayOff);
            digitalWrite(ledPin, ledOff);
        }
        return(true);
    }

};
