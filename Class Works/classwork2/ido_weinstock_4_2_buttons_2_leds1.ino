void setup()
{
  // NOTE: '0' - input, '1' - OUTPUT
  // DDR'x' allows to set section's bits values.
  DDRD &= ~0b00001000; // config DDRD(the top right)PIN 3 LOW (inpput) while masking it (whatever the initial values are).
  DDRB |= 0b00100000; // config DDRB (top left) 13 pin HIGH (output) responsibble for the red LED.
  DDRB |= 0b00010000; // config DDRB (top left) 12 pin HIGH (output) responsibble for the green LED.
}

void loop() {
  uint8_t btn1_right = PIND & 0b00001000; // adressing button 1 value
  uint8_t btn2_left = PIND & 0b00100000; // adressing button 2 value 

  if(btn1_right != 0) // if button 1 is pressed
  {
    PORTB |= 0b00010000; // pin 13 (green LED) HIGH
    delay(50); // debuncer
  }
  if(btn2_left != 0) // if button 2 is pressed
  {
    PORTB |= 0b00100000; // pin 12 (red LED) HIGH
    delay(50);
  }
  else{
    PORTB &= ~0b00010000; // green - LOW
    PORTB &= ~0b00100000; // red - LOW
    delay(50);
  }
}