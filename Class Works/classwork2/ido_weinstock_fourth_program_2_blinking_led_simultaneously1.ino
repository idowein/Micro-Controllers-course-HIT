void setup() {
  DDRD |= 0b00001000;
  DDRB |= 0b00000001;
}

void loop() {
  PORTD |= 0b00001000;    // Yellow
  PORTB |= 0b00000001;    // Green
  delay(5000);
  
  PORTD &= ~0b00001000;   // Yellow
  PORTB &= 0b11111110;    // Green
  delay(1000);
}