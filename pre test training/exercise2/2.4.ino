void setup() {
  DDRD |= 0b00001000;
  DDRB |= 0b00000001;
}

void loop() {
  PORTD |= 0b00001000; 	// yellow on
  PORTB |= 0b00000001;	// green off
  delay(1000);
  
  PORTD &= ~0b00001000;
  PORTB &= ~0b00000001;
  delay(1000);
}