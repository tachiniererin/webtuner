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

#define STORE_BTN_PIN 8
#define TAB1_BTN_PIN 9
#define TAB2_BTN_PIN 10
#define TAB3_BTN_PIN 11


Debouncer debouncer_sw(SW_PIN, DEBOUNCE_MS);
Debouncer debouncer_store_btn(STORE_BTN_PIN, DEBOUNCE_MS);
Debouncer debouncer_tab1_btn(TAB1_BTN_PIN, DEBOUNCE_MS);
Debouncer debouncer_tab2_btn(TAB2_BTN_PIN, DEBOUNCE_MS);
Debouncer debouncer_tab3_btn(TAB3_BTN_PIN, DEBOUNCE_MS);

Encoder myEnc(ENC_PIN1, ENC_PIN2);
boolean sw_state;

void setup() {
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(STORE_BTN_PIN, INPUT_PULLUP);
  pinMode(TAB1_BTN_PIN, INPUT_PULLUP);
  pinMode(TAB2_BTN_PIN, INPUT_PULLUP);
  pinMode(TAB3_BTN_PIN, INPUT_PULLUP);
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
  }

  debouncer_sw.update();
  if (debouncer_sw.edge()) {
    if (debouncer_sw.falling()) {
      Serial.println("click");
    }
  }

  debouncer_store_btn.update();
  if (debouncer_store_btn.edge()) {
    if (debouncer_store_btn.falling()) {
      Serial.println("store");
    }
  }

  debouncer_tab1_btn.update();
  if (debouncer_tab1_btn.edge()) {
    if (debouncer_tab1_btn.falling()) {
      Serial.println("tab1");
    }
  }

  debouncer_tab2_btn.update();
  if (debouncer_tab2_btn.edge()) {
    if (debouncer_tab2_btn.falling()) {
      Serial.println("tab2");
    }
  }

  debouncer_tab3_btn.update();
  if (debouncer_tab3_btn.edge()) {
    if (debouncer_tab3_btn.falling()) {
      Serial.println("tab3");
    }
  }
  Serial.flush();
}
