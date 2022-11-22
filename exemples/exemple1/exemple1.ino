#include <GPSP.h>

GPSP protocol(Serial);

void setup() {
    Serial.begin(9600);
    protocol.defineCommand("ECHO", ECHO);
}

void loop() {
    protocol.update();
}

void ECHO(String args, ...) {
    Serial.println(args[0]);
}