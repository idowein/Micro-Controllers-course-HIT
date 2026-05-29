void setup() {
  DDRD |= 0b00001000;
  DDRD |= 0b00010000;
}

void loop() {
  PORTD |= 0b00001000;    // Yellow
  PORTD &= 0b11101111;    // Green
  delay(1000);
  
  PORTD &= ~0b00001000;   // Yellow
  PORTD |= 0b00010000;    // Green
  delay(1000);
}