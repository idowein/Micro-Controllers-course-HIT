// This program demonstrates the usage of Timers Overflow Interrupts.
// Configuring a Timer with a prescaler of 1024.
// Counting Frequency of Timer = 16,000,000 (16MHZ - internal clock) / 1024 = 15,625[Hz]
// Timer2 is 8-bit. Hence it can store values between 0-255.
// This timer is expected to be "re-filled" at 15,625/256 = ~61[Per Second]

// Enabling Timer2 "Overflow Interrupt". Once it reaches max value (to zero)
// it is expected to raise a "flag" and interrupt.

// This program also uses the ISR to handle the Timer OverFlow Interrupt.

// Global variable to keep track of the number of timer overflows
unsigned int timerCounter = 0;

void setup()
{
  // Set pin 13 (PB5) as an output
  DDRB |= (1 << DDB5);
  
  // Disable interrupts
  cli();
  
  // Clear Timer2 control registers - page 84
  TCCR2A = 0b00000000;
  TCCR2B = 0b00000000;
  
  // Set Timer2 counter value to 0
  TCNT2 = 0b00000000;
  
  // Set Timer2 prescaler to 1024 - page 130-131 atmel datasheet
  TCCR2B |= (1<<0) | (1<<1) | (1<<2);
  
  // Enable Timer2 overflow interrupt - page 132 - ISR when the timer counter is overflowed
  TIMSK2 |= (1<<0);
  
  // Enable interrupts
  sei();
}

// Interrupt Service Routine (ISR) for Timer2 overflow interrupt
ISR(TIMER2_OVF_vect)
{
  // Increment the timerCounter variable
  timerCounter++;
  
  // If the timerCounter variable has reached ________________ (i.e. 61 timer overflows), toggle the state of pin 13
  if (timerCounter >= 61)
  {
    PORTB ^= (1 << PORTB5); // LED TOGGLE
    // Reset the timerCounter variable
    timerCounter = 0;
  }
}

void loop()
{
  // Nothing to do here since all timing and pin toggling is handled by the Timer2 overflow interrupt
}
