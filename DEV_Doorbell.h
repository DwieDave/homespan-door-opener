#include "HomeSpan.h"

struct DEV_Doorbell : Service::StatelessProgrammableSwitch {

    int relayPin;
    SpanCharacteristic* doorbell;

    DEV_Doorbell(int relayPin) {
        this->relayPin = relayPin;
        pinMode(relayPin, INPUT_PULLUP);
        doorbell = new Characteristic::ProgrammableSwitchEvent();
        new SpanButton(relayPin);
    }

    void button(int pin, int pressType) override {
        doorbell->setVal((int)SpanButton::SINGLE);
    }

};
