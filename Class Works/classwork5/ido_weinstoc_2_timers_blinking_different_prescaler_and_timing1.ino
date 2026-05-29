// This program demonstrates the usage of Timers Overflow Interrupts.
// Configuring a Timer with a prescaler of 128.
// Counting Frequency of Timer = 16,000,000 / 128 = 125,000[Hz]
// Timer2 is 8-bit. Hence it can store values between 0-255.
// This timer is expected to be "re-filled" at 125k/256 = ~488[Per Second]

// That means that 488 interupts of the timer equal to 1 sec

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
  
  // Clear Timer2 control registers
  TCCR2A = 0;
  TCCR2B = 0;
  
  // Set Timer2 counter value to 0
  TCNT2 = 0;
  
  // Set Timer2 prescaler to 1024
  TCCR2B |= (1 << CS20) | (1 << CS22); 
  // according to the datasheet this is 1024 clock prescaler
  
  // Enable Timer2 overflow interrupt
  TIMSK2 |= (1 << TOIE2);
  
  // Enable interrupts
  sei();
}

// Interrupt Service Routine (ISR) for Timer2 overflow interrupt
ISR(TIMER2_OVF_vect)
{
  // Increment the timerCounter variable
  timerCounter++;
  
  // If the timerCounter variable has reached ________________ (i.e. 61 timer overflows), toggle the state of pin 13
  if (timerCounter >= 244) // 1 second passed
  {
    PORTB ^= (1 << PORTB5); // LED toggle
    // Reset the timerCounter variable
    timerCounter = 0;
  }
}

void loop()
{
  // Nothing to do here since all timing and pin toggling is handled by the Timer2 overflow interrupt
}
