#include "HomeSpan.h"

struct DEV_Identify : Service::AccessoryInformation {
    SpanCharacteristic* identify;   // reference to the Identify Characteristic
    DEV_Identify(const char* name, const char* manu, const char* sn, const char* model, const char* version) : Service::AccessoryInformation() {
        new Characteristic::Name(name);                   // create all the required Characteristics with values set based on above arguments
        new Characteristic::Manufacturer(manu);
        new Characteristic::SerialNumber(sn);
        new Characteristic::Model(model);
        new Characteristic::FirmwareRevision(version);
        identify = new Characteristic::Identify();
    }
};