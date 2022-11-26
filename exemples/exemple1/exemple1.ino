#include <GPSP.h>
#include <SoftwareSerial.h>

GPSP protocol(Serial);

void setup() {
    serial.begin(9600);
    protocol.defineCommand({ECHO, "ECHO", "Send back it's parameters"});
    protocol.defineCommand({FIBONACCI, "FIBONACCI", "Display Fibonacci Series up to first parameter value"});
    protocol.defineCommand({ANALOG, "ANALOG", "Control a pin"});
    pinMode(13, OUTPUT);
}

void loop() {
  protocol.update();
}

void ANALOG(const char args[][50], int size) {
  if (size < 2)
    return;

  int pin = atoi(args[0]);
  int value = constrain(atoi(args[1]), 0, 255);
  analogWrite(pin, value);
}

void ECHO(const char args[][50], int size) {
  for (int i = 0; i < size; i++) {
    if (i != 0)
      serial.write(',');
    serial.print(args[i]);
  }
  serial.println();
}

void FIBONACCI(const char args[][50], int size) {
  serial.println(size);
  int n = size > 0 ? atoi(args[0]) : 50;

  int t1 = 0, t2 = 1, nextTerm = 0;

  serial.println(t1);
  serial.println(t2);

  nextTerm = t1 + t2;

  while(nextTerm <= n) {
      serial.println(nextTerm);
      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
  }
}



