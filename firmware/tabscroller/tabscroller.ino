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
#define LONG_PRESS_DELAY_MS 500

#define TAB1_BTN_PIN 8
#define TAB2_BTN_PIN 9
#define TAB3_BTN_PIN 10
#define TAB4_BTN_PIN 11

Debouncer encoder_switch_debouncer(SW_PIN, DEBOUNCE_MS);

int numTabButtons = 4;
Debouncer tab_button_debouncers[] = {
  Debouncer(TAB1_BTN_PIN, DEBOUNCE_MS),
  Debouncer(TAB2_BTN_PIN, DEBOUNCE_MS),
  Debouncer(TAB3_BTN_PIN, DEBOUNCE_MS),
  Debouncer(TAB4_BTN_PIN, DEBOUNCE_MS)
};

Encoder myEnc(ENC_PIN1, ENC_PIN2);

void setup() {
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(TAB1_BTN_PIN, INPUT_PULLUP);
  pinMode(TAB2_BTN_PIN, INPUT_PULLUP);
  pinMode(TAB3_BTN_PIN, INPUT_PULLUP);
  pinMode(TAB4_BTN_PIN, INPUT_PULLUP);
}

long position  = 0;
unsigned long encoderPressedTime = 0;
unsigned long buttonPressedTime[4] = {0, 0, 0, 0};

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

  encoder_switch_debouncer.update();
  if (encoder_switch_debouncer.edge()) {
    if (encoder_switch_debouncer.falling()) {
      encoderPressedTime = millis();
    }
    if (encoder_switch_debouncer.rising()) {
      if (millis() - encoderPressedTime > LONG_PRESS_DELAY_MS){
        Serial.println("click-long");
      } else{
        Serial.println("click-short");
      }
    }
  }

  for (int i = 0; i < numTabButtons; i++) {
    tab_button_debouncers[i].update();
    if (tab_button_debouncers[i].edge()) {
      if (tab_button_debouncers[i].falling()) {
        buttonPressedTime[i] = millis();
      }
      if (tab_button_debouncers[i].rising()) {
          Serial.print("btn-");
          Serial.print(i+1);
        if (millis() - buttonPressedTime[i] > LONG_PRESS_DELAY_MS){
          Serial.println("-long");
        } else{
          Serial.println("-short");
        }
      }
    }
  }

  Serial.flush();
}
