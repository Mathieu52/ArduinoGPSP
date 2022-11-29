#include <GPSP.h>

GPSP protocol(Serial);

void setup() {
    Serial.begin(9600);
    protocol.defineCommand({ECHO, "ECHO", "Send back it's parameters"});
    protocol.defineCommand({FIBONACCI, "FIBONACCI", "Display Fibonacci Series up to first parameter value"});
    protocol.defineCommand({ANALOG, "ANALOG", "Control a pin"});
    protocol.defineCommand({ANALOG, "PINMODE", "Sets the mode of a pin"});
}

void loop() {
  protocol.update();
}

// PINMODE={pin},{INPUT or OUTPUT}
void PINMODE(const char args[][50], int size) {
  if (size < 2)
    return;

  int pin = atoi(args[0]);
  if (strcmp(args[1], "INPUT") == 0) {
    PINMODE(pin, INPUT);
  } else if (strcmp(args[1], "OUTPUT") == 0) {
    PINMODE(pin, OUTPUT);
  }
}

// ANALOG={pin},{[0-255]}
void ANALOG(const char args[][50], int size) {
  if (size < 2)
    return;

  int pin = atoi(args[0]);
  int value = constrain(atoi(args[1]), 0, 255);
  analogWrite(pin, value);
}

// ECHO={message}
void ECHO(const char args[][50], int size) {
  for (int i = 0; i < size; i++) {
    if (i != 0)
      Serial.write(',');
    Serial.print(args[i]);
  }
  Serial.println();
}

// FIBONACCI={Max value}
// FIBONACCI
void FIBONACCI(const char args[][50], int size) {
  Serial.println(size);
  int n = size > 0 ? atoi(args[0]) : 50;

  int t1 = 0, t2 = 1, nextTerm = 0;

  Serial.println(t1);
  Serial.println(t2);

  nextTerm = t1 + t2;

  while(nextTerm <= n) {
      Serial.println(nextTerm);
      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
  }
}



