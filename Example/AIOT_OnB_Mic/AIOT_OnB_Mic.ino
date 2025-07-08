#define MIC_PIN 33

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  int mn = 1024;
  int mx = 0;

  for (int i = 0; i < 10000; ++i) {

    int val = analogRead(MIC_PIN);
    
    mn = min(mn, val);
    mx = max(mx, val);
  }

  int delta = mx - mn;

  Serial.print("Min=");
  Serial.print(mn);
  Serial.print(" Max=");
  Serial.print(mx);
  Serial.print(" Delta=");
  Serial.println(delta);
  delay(500);
}
