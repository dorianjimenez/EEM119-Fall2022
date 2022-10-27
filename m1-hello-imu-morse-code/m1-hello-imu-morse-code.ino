
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {

  // H
  quickBurst();
  quickBurst();
  quickBurst();
  quickBurst();

  // E
  quickBurst();

  // L
  quickBurst();
  longBurst();
  quickBurst();
  quickBurst();

  // L
  quickBurst();
  longBurst();
  quickBurst();
  quickBurst();

  // O
  longBurst();
  longBurst();
  longBurst();

  // Space
  delay(1000);

  // I
  quickBurst();
  quickBurst();

  // M
  longBurst();
  longBurst();

  // U
  quickBurst();
  quickBurst();
  longBurst();

  // End
  delay(5000);

}

void quickBurst() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
}

void longBurst() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}