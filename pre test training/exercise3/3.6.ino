volatile int state = 0;

void setup(){
	DDRD &= ~0b00001000; // input port3
  	DDRD &= ~0b00000100; // input port2
	DDRD |= 0b10000000; // output port - LED1 - pin7
	DDRB |= 0b00000001; // output port - LED2 - pin8
	DDRB |= 0b00001000; // output port - LED3 - pin11	
}

void loop()
{
	uint8_t btn1 = PIND & 0b00001000; // check pin3 status
  	uint8_t btn2 = PIND & 0b00000100; // check pin2 status
  
  	if (btn1 != 0){ // if button is pressed

      delay(50); // debouncer

      while(btn1 !=0) // while btn1 is pressed - don't proceed to compile
      {
		btn1 = PIND & 0b00001000;
      }

      delay(50); // debouncer
      state ++;
      
      if(state > 7){
        	state = 0;
        	PORTB &= ~0b00001000; // turn off pin11
            PORTB &= ~0b00000001;	// turn off pin8
        	PORTD &= ~0b10000000;
      }
    }
  
  	if(btn2 != 0){
      
      delay(50); // debouncer

      while(btn2 !=0) // while btn2 is pressed - don't proceed to compile
      {
		btn2 = PIND & 0b00000100;
      }

      delay(50); // debouncer
      state = 0; // reset the count
      
       PORTB &= ~0b00001000; // turn off pin11
       PORTB &= ~0b00000001;	// turn off pin8
       PORTD &= ~0b10000000;
    }
  
  	if(state == 1)
      PORTB |= 0b00001000;	// turn on pin11
  	if(state ==2){
      PORTB &= ~0b00001000; // turn off pin11
      PORTB |= 0b00000001; 	// turn on pin8
    }
  	if(state ==3){
      PORTB |= 0b00001000;	// turn on pin11
    }
  	if(state ==4){
      PORTB &= ~0b00001000; // turn off pin11
      PORTB &= ~0b00000001;	// turn off pin8
      PORTD |= 0b10000000; 	// turn on pin7
    }
  	if(state ==5){
	  PORTB |= 0b00001000;	// turn on pin11
    }
    if(state ==6){
      PORTB &= ~0b00001000; // turn off pin11
      PORTB |= 0b00000001; 	// turn on pin8
    }
   	if(state == 7)
      PORTB |= 0b00001000;	// turn on pin11
}