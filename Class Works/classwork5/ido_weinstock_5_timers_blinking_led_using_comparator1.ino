// Global variable to keep track of the number of timer overflows
unsigned int timerCount = 0;

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
  TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22);
  
  // Configure CTC Mode where TOP = OCRA (!)
  // In this case (CTC Mode), 
  // the timer is reset to zero when it reaches the value 
  // stored in the Output Compare Register (OCR),
  // and then starts counting again from zero
  TCCR2A |= (1 << WGM21);
  
  
  // Set the value for the output compare register
  // Calculate this value: 15,625/x = 125  ->  x = 15,625/125 = 125
  // Since it counts from 0, we subtract 1: 125 - 1 = 124
  OCR2A = 124;

  // Enable Timer2 compare match interrupt
  TIMSK2 |= (1 << OCIE2A);

  // Enable interrupts
  sei();
}

// Interrupt Service Routine (ISR) for Timer2 compare match interrupt
ISR(TIMER2_COMPA_vect)
{
  // Increment the timerCount variable
  timerCount++;

  // If the timerCount variable has reached 125
  if (timerCount >= 125)
  {
    PORTB ^= (1 << PORTB5);
    // Reset the timerCount variable
    timerCount = 0;
  }
}

void loop()
{
  // Nothing to do here since all timing and pin toggling is handled by the Timer2 compare match interrupt
}