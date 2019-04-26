#define ENC_PIN1 5
#define ENC_PIN2 6

//#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

Encoder myEnc(ENC_PIN1, ENC_PIN2);

void setup() {
  Serial.begin(115200);
}

long position  = 0;

void loop() {
  long newPos = myEnc.read()/4;
  if (newPos != position) {
    String output = "left";
    if (newPos > position) {
      output = "right";
    }
    position = newPos;
    Serial.println(output);
    Serial.flush();
  }
}
