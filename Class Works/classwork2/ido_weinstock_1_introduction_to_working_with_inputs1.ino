void setup()
{
  DDRD &= ~0b00000100; // configure pin 2 INPUT
  DDRB |= 0b00100000; // configure pin 13 OUTPUT
}


void loop()
{
  unsigned char isPressed;
  isPressed = PIND & 0b00000100;
  if (isPressed == 0)
    PORTB &= ~0b00100000; // Turn ON LED
  else
        PORTB |= 0b00100000; // Turn OFF LED
}

