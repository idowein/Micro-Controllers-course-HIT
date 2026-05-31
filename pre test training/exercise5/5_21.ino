// Global variable to keep track of the number of timer overflows
unsigned int timerCounter = 0;

void setup()
{
  // Set pin 13 (PB5) as an output
  DDRB |= (1 << DDB5);
  
  // Disable interrupts
  cli();
  
  // Clear Timer2 control registers
  TCCR2A = 0;
  TCCR2B = 0;
  
  // Set Timer2 counter value to 0
  TCNT2 = 0;
  
  // Set Timer2 prescaler to 128
  TCCR2B |= (1<<0) | (1<<2);
  
  // Enable Timer2 overflow interrupt
  TIMSK2 |= (1 << 0);
  
  // Enable interrupts
  sei();
}

// Interrupt Service Routine (ISR) for Timer2 overflow interrupt
ISR(TIMER2_OVF_vect)
{
  // Increment the timerCounter variable
  timerCounter++;
  
  // Toggle every half a second (~0.5 seconds)
  // 16M / 128 = 125k
  // 125k/256 (0-255, 8 bits) = 488 overflows per seconds
  // 244 overflows per 1/2 second
  if (timerCounter >= 244)
  {
    PORTB ^= (1 << PORTB5);
    // Reset the timerCounter variable
    timerCounter = 0;
  }
}

void loop()
{
  // Nothing to do here since all timing and pin toggling is handled by the Timer2 overflow interrupt
}
