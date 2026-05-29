void setup()
{
  // NOTE: '0' - input, '1' - OUTPUT
  // DDR'x' allows to set section's bits values.
  DDRD &= ~0b00001000; // config DDRD(the top right)PIN 3 LOW (inpput) while masking it (whatever the initial values are).
  DDRB |= ~0b00100000; // config DDRB (top left) 13 pin HIGH (output) responsibble for the green LED.
  DDRB |= ~0b00010000; // config DDRB (top left) 12 pin HIGH (output) responsibble for the red LED.
}

void loop()
{
  // NOTE: the button ACTIVATES the current from pin 5V to pin num 3
  unsigned char result;
  result = PIND & 0b00001000; // PIND reads the data about SECTION-D and pin 3 (HIGH or LOW)
  if (result == 0){ // if there is no voltage on pin 3 
    PORTB &= ~0b00100000; // PORTB pin 13 HIGH (green)
  	PORTB |= 0b00010000; // PORTB pin 12 LOW (red)
  }
  else{
    PORTB &= ~0b00010000; // PORTB pin 12 HIGH (red)
  	PORTB |= 0b00100000; // PORTB pin 13 LOW (green)
  }
}