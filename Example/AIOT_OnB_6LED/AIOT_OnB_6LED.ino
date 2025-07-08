#include <Adafruit_NeoPixel.h>

#define KEY_S1 23  // Button S1
#define KEY_S2 19  // Button S2
#define LED_BUILTIN 0
#define NUMPIXELS 6

Adafruit_NeoPixel pixels(NUMPIXELS, LED_BUILTIN, NEO_GRB + NEO_KHZ800);  // On-board 6 LEDs

void setup() {
  //ตั่งค่า serial monitor
  Serial.begin(115200);
  pixels.begin();  //set up 6 on-board LEDs

  pinMode(KEY_S1, INPUT);
  pinMode(KEY_S2, INPUT);
}

void loop() {
  bool input1 = digitalRead(KEY_S1);
  bool input2 = digitalRead(KEY_S2);
  if (input1 == 0) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(150, 0, 0));
      pixels.show();
    }
  } 
  else if (input2 == 0) {
    pixels.clear();
    pixels.show();
  }
  delay(500);
}
