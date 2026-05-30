void setup()
{
  // NOTE: '0' - input, '1' - OUTPUT
  // DDR'x' allows to set section's bits values.
  DDRD &= ~0b00001000; // config DDRD(the top right)PIN 3 LOW (inpput) while masking it (whatever the initial values are).
  DDRB |= 0b00100000; // config DDRB (top left) 13 pin HIGH (output) responsibble for the green LED.
  DDRB |= 0b00010000; // config DDRB (top left) 12 pin HIGH (output) responsibble for the red LED.
}

void loop(){
  
  uint8_t btn1 = PIND & 0b00001000;	// check pin3 voltage
  if (btn1 != 0){	// if btn 1is pressed
	PORTB |= 0b00100000; 	// turn green LED on
    PORTB &= ~0b00010000;	// turn red LIGHT off
    delay(50); 	// debounce time
  } else{
    PORTB &= ~0b00100000; 	// turn green LED off
    PORTB |= 0b00010000;	// turn green LIGHT on
    delay(50); 	// debounce time
  }
}