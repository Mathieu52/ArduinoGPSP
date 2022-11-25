#include <GPSP.h>

GPSP protocol(Serial);

void setup() {
    Serial.begin(9600);
    protocol.defineCommand({ECHO, "ECHO", "Send back it's parameters"});
    protocol.defineCommand({FIBONACCI, "FIBONACCI", "Display Fibonacci Series up to first argument value"});
}

void loop() {
  protocol.update();
}

void ECHO(const char args[][50], int size) {
  for (int i = 0; i < size; i++) {
    if (i != 0)
      Serial.write(',');
    Serial.print(args[i]);
  }
  Serial.println();
}

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



