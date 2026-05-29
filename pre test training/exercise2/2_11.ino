// bank B is the TOP LEFT bank
// bank D is the TOP RIGHT bank 
// bank C is the analog bank, in the BOTTOM RIGHT of thre board

void setup()
{
  DDRB |= 0b00100000; // DDRB port 13 setup to HIGH '1'
  // High means this is OUTPUT port
  // DDR - Data Direction Resgister (set port as output)
}

void loop()
{
  PORTB |= 0b00100000; // PORTB port 13 config to 1
  delay(2000); // Wait for 1000 millisecond(s)
  PORTB &= 0b11011111;; // flip PORTB port 13 
  delay(1000); // Wait for 1000 millisecond(s)
}