void setup()
{
  // Set pin 13 (PB5) as an output
  DDRB |= (1 << DDB5);

  // Disable interrupts
  cli();

  // Clear Timer1 control registers
  TCCR1A = 0;
  TCCR1B = 0;

  // Set Timer1 counter value to 0
  TCNT1 = 0;

  // Set Timer1 prescaler to 1024
  // NOTE ON TIMER DIFFERENCE (Prescaler Bits):
  // In Timer2 (8-bit), a 1024 prescaler requires setting CS20, CS21, and CS22.
  // In Timer1 (16-bit), a 1024 prescaler only requires setting CS12 and CS10.
  TCCR1B |= (1 << CS12) | (1 << CS10);
  
  // Configure CTC Mode where TOP = OCR1A
  // NOTE ON TIMER DIFFERENCE (CTC Bit Location):
  // In Timer2, the CTC mode bit (WGM21) is located in the TCCR2A register.
  // In Timer1, the CTC mode bit (WGM12) is located in the TCCR1B register.
  TCCR1B |= (1 << WGM12);
  
  // Set the value for the output compare register
  // =========================================================================
  // THE ULTIMATE COUNTER DIFFERENCE (8-bit vs 16-bit):
  //
  // 1. In the Timer2 exercise, OCR2A could only hold a max value of 255 (8-bit).
  //    Because 255 was too small to reach a 1-second delay, we had to set OCR2A = 124
  //    and use a software counter ('timerCount') inside the ISR to count up to 125.
  //    Formula: 125 hardware matches * 125 software loops = 15,625 total ticks.
  //    This forced the CPU to jump into the ISR 125 times every second!
  //
  // 2. In this Timer1 exercise, OCR1A can hold values up to 65,535 (16-bit).
  //    Therefore, we can load the entire 15,625 ticks directly into hardware!
  //    Calculation: (16,000,000 Hz / 1024) * 1 sec = 15,625 steps.
  //    We set OCR1A to 15,624 (counting from 0). No software counter needed!
  // =========================================================================
  OCR1A = 15624;

  // Enable Timer1 compare match interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Enable interrupts
  sei();
}

// Interrupt Service Routine (ISR) for Timer1 compare match interrupt
// =========================================================================
// CPU EFFICIENCY DIFFERENCE:
// In Timer2, this ISR was called 125 times per second to manually increment 'timerCount'.
// In Timer1, this ISR is called EXACTLY ONCE PER SECOND, completely handled by hardware!
// =========================================================================
ISR(TIMER1_COMPA_vect)
{
  // Toggle the LED directly - no software counters or 'if' statements required.
  PORTB ^= (1 << PORTB5);
}

void loop()
{
  // Nothing to do here since all timing and pin toggling is handled by the Timer1 compare match interrupt
}