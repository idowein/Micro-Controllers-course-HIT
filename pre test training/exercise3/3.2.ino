void setup()
{
  DDRD &= ~0b00000100; // configure pin 2 INPUT - '0'
  DDRB |= 0b00100000; // configure pin 13 OUTPUT - '1'
}


void loop()
{
 	uint8_t btn1 = PIND & 0b00000100;	// check PIN2 status
    
    if(btn1 != 0){ // if btn is pressed
      	PORTB |= 0b00100000; 	// LED turn on
      	delay(50); // debouncing time
    }  

  	else{
		PORTB &= ~0b00100000; // Turn OFF LED  
  		delay(50);	// debounce time
  	}
        
}