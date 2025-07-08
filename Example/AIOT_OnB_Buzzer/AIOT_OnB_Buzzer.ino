#include <Arduino.h>
#include "pitches.h"

#define BUZZER_PIN 13
#define TONE_CHANNEL 15


void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  Serial.println("Start music");
  tone(BUZZER_PIN, NOTE_C4, 500);
  tone(BUZZER_PIN, NOTE_D4, 500);
  tone(BUZZER_PIN, NOTE_E4, 500);
  noTone(BUZZER_PIN);
  delay(1000);
}