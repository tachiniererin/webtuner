// Fully Automated WebTuner prototype - Arduino sketch
// (c) 2019 Fully Automated Technologies
// Licensed under the 2-clause BSD/Molotov
// See LICENSE in the repository

// You need to install the 
// * Encoder and 
// * Debouncer 
// libraries in the Arduino IDE (Ctrl-Shift-I)

//#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
#include <Debouncer.h>

#define ENC_PIN1 5
#define ENC_PIN2 6
#define SW_PIN 4
#define DEBOUNCE_MS 22

Debouncer debouncer(SW_PIN, DEBOUNCE_MS);

Encoder myEnc(ENC_PIN1, ENC_PIN2);
boolean sw_state;

void setup() {
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP);
}

long position  = 0;

void loop() {
  debouncer.update();
  long newPos = myEnc.read()/4;
  if (newPos != position) {
    String output = "left";
    if (newPos > position) {
      output = "right";
    }
    position = newPos;
    Serial.println(output);
  }
  if (debouncer.edge()) {
    if (debouncer.falling()) {
      Serial.println("click");
      
    }
  }
  Serial.flush();
}
