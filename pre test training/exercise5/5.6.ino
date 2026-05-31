void setup()
{
  // Set pin 13 (PB5) as an output
  DDRB |= (1 << DDB5);

  // Disable global interrupts during configuration
  cli();

  // Clear Timer1 control registers to start from a clean state
  TCCR1A = 0;
  TCCR1B = 0;

  // Initialize Timer1 counter value to 0
  TCNT1 = 0;

  // Configure Timer1:
  // 1. Enable CTC Mode (Clear Timer on Compare Match) by setting WGM12
  // 2. Set Prescaler to 1024 by setting CS12 and CS10
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
  
  // Set the output compare register value for a 1-second interval
  // Calculation: 16,000,000 Hz / 1024 = 15,625 ticks per second
  // Subtract 1 because the counter starts from 0: 15,625 - 1 = 15,624
  OCR1A = 15624;

  // Enable Timer1 Output Compare Match A Interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Enable global interrupts
  sei();
}

// Interrupt Service Routine (ISR) for Timer1 Compare Match A
// This function triggers automatically exactly once every second
ISR(TIMER1_COMPA_vect)
{
  // Toggle the onboard LED (Pin 13 / PB5)
  // No software counter needed since Timer1 (16-bit) can count a full second in hardware
  PORTB ^= (1 << PORTB5); 
}

void loop()
{
  // Nothing to do here; all timing and LED toggling are handled by the hardware interrupt
}