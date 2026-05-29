// State Machine Implementation
// Changing the LEDs status based on the number of times the Button S1 is pressed.

// Initializing a global variable state with "initial state 0"
unsigned int state = 0;

void setup()
{
  // Define pin 3 as INPUT
  DDRD &= ~0b00001100; // nice trick to set 2 and 3 together as inputs
  
  // Define OUTPUTs
  DDRD |= 0b10000000; // pin 7 as output (LED1)
  DDRB |= 0b00000001; // pin 8 as output (LED2)
  DDRB |= 0b00001000; // pin 11 as output (LED3)
  
  // Start with all LEDs OFF
  turnOffAllLeds();
}

void turnOffAllLeds() {
    // Turning all the LEDs off 
    PORTD &= ~0b10000000; // LED1 OFF
    PORTB &= ~0b00001001; // LED2, LED3 OFF
}

void loop()
{
  // RST check - Checking pin 2 (PIND bit 2)
  if ((PIND & 0b00000100) != 0) 
  {
    state = 0;
    turnOffAllLeds(); // close all the LEDs
    delay(50); // Debounce
    while((PIND & 0b00000100) != 0); // waiting for the release of the button
    delay(50);
  }
  // Extract information about pin 3 (PIND bit 3) to find if button is pressed/released
  else if ((PIND & 0b00001000) != 0) 
  {
    delay(50); // basic debouncing after pressing
    
    // Wait while button is pressed (Polling) - Read the value over and over again..
    while((PIND & 0b00001000) != 0);
    
    delay(50); // basic debouncing after releasing
    
    state++; // Increment state by 1
    if (state == 8)
      state = 0; // Return to the initial state
    
    switch(state){
      case 0: // 000
        PORTD &= ~0b10000000; // LED1 OFF
        PORTB &= ~0b00001001; // LED2, LED3 OFF
        break;
      case 1: // 001
        PORTD &= ~0b10000000; // LED1 OFF
        PORTB &= ~0b00000001; // LED2 OFF
        PORTB |=  0b00001000; // LED3 ON
        break;
      case 2: // 010
        PORTD &= ~0b10000000; // LED1 OFF
        PORTB &= ~0b00001000; // LED3 OFF
        PORTB |=  0b00000001; // LED2 ON
        break;
      case 3: // 011
        PORTD &= ~0b10000000; // LED1 OFF
        PORTB |=  0b00001001; // LED2, LED3 ON
        break;
      case 4: // 100
        PORTD |=  0b10000000; // LED1 ON
        PORTB &= ~0b00001001; // LED2, LED3 OFF
        break;
      case 5: // 101
        PORTD |=  0b10000000; // LED1 ON
        PORTB &= ~0b00000001; // LED2 OFF
        PORTB |=  0b00001000; // LED3 ON
        break;
      case 6: // 110
        PORTD |=  0b10000000; // LED1 ON
        PORTB &= ~0b00001000; // LED3 OFF
        PORTB |=  0b00000001; // LED2 ON
        break;
      case 7: // 111
        PORTD |=  0b10000000; // LED1 ON
        PORTB |=  0b00001001; // LED2, LED3 ON
        break;
      default: // if i streched out of 0-7
        state = 0; // return to 0 state
        turnOffAllLeds(); // close all the LEDs
        break;
    }
  }
}