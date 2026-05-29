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
	PORTB |= 0b00000100; 	// red on
  	PORTB &= ~0b00001000;	// yellow off
  	PORTB &= ~0b00010000;	// green off
  	delay(7000); 
  
  	PORTB |= 0b00001000;	// yellow on
  	delay(4000);
  	
	PORTB &= ~0b00000100; 	// red off
  	PORTB &= ~0b00001000;	// yellow off
  	PORTB |= 0b00010000;	// green on
  	delay(2000);
  	
  	PORTB &= ~0b00010000;	// green off
  	PORTB |= 0b00001000;	// yellow on
  	delay(4000);
  	
}



