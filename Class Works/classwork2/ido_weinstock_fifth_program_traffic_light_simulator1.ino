/*
  Simluate Light Traffic based exactly on 
  the instructions provided in the PDF file.
*/

void setup()
{
    
  DDRB |= 0b00000100; // Set up red as output
  DDRB |= 0b00001000; // Set up yellow as output
  DDRB |= 0b00010000; // Set up green as output
}

void loop()
{
  PORTB |= 0b00000100;    // RED HIGH
  delay(3000);
  PORTB |= 0b00001000;    // YELLOW HIGH
  delay(4000);
  
  PORTB &= ~0b00001000;   // Yellow LOW
  PORTB &= ~0b00000100;   // RED LOW
  PORTB |= 0b00010000;    // GREEN HIGH
  delay(2000);
  
  PORTB &= ~0b00010000;   // GREEN LOW  
  PORTB |= 0b00001000;    // YELLOW HIGH
  delay(4000);
  
  PORTB &= ~0b00001000;   // Yellow LOW
  PORTB |= 0b00000100;    // RED HIGH
  delay(7000);

}



