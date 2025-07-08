#include <oled.h>

OLED display(4, 5, NO_RESET_PIN, OLED::W_128, OLED::H_64); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  display.begin();  //set up OLED display
}

void loop() {
  //display can put upto 7 rows
  display.clear();
  display.inverse();                       // white tab on the line
  display.drawString(0, 0, "AIOT board");  // first line
  display.noInverse();
  String line1 = "Hello World! ";
  display.drawString(0, 1, line1.c_str());
  String line2 = "");
  display.drawString(0, 2, line2.c_str());
  String line3 = "";
  display.drawString(0, 3, line3.c_str());
  display.display();

  delay(1000);
}
