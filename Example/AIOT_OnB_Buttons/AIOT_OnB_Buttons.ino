#define KEY_S1 23  // Button S1
#define KEY_S2 19  // Button S2

void setup() {
  Serial.begin(115200);
  pinMode(KEY_S1, INPUT);
  pinMode(KEY_S2, INPUT);
}

void loop() {
  bool input1 = digitalRead(KEY_S1);
  bool input2 = digitalRead(KEY_S2);
  Serial.println("S1: " + String(input1));
  Serial.println("S2: " + String(input2));
  delay(500);
}
