#include "Arduino.h"
#include "GPSP.h"
#include <ArxContainer.h>

void GPSP::HELP(String args, ...) {
    serial->println("help");
}

GPSP::GPSP(HardwareSerial &serial) {
    this->serial = &serial;
}

void GPSP::defineCommand(String key, Command command, String description) {
    if (command != nullptr)
        command_map.insert(key, command);

    defineDescription(key, description);
}

void GPSP::defineDescription(String key, String description) {
    description_map.insert(key, description);
}

String GPSP::update() {

}