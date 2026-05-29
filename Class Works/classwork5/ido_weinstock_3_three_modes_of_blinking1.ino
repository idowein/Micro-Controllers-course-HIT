unsigned int timerCount = 0;
unsigned int state = 0; // 0=mode1, 1=mode2
unsigned int stateDelay = 0; // Delay variable used for state transitions within the ISR

void setup()
{
    // Set digital pin 13 (PORTB5) as output
    DDRB |= (1 << DDB5);

    // Disable global interrupts
    cli();

    // Clear Timer2 control registers
    TCCR2A = 0;
    TCCR2B = 0;

    // Clear Timer2 count register
    TCNT2 = 0;

    // Set prescaler bits (CS20, CS21, CS22)
    TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22);
    
    // Enable Timer2 overflow interrupt
    TIMSK2 |= (1 << TOIE2);

    // Enable global interrupts
    sei();
}

// Timer2 Overflow Interrupt Service Routine
ISR(TIMER2_OVF_vect)
{
    timerCount++;

    // Mode 1: 1 sec interval
    if (state == 0)
    {
        if (timerCount >= 61)
        {
            PORTB ^= (1 << PORTB5); // Toggle LED
            timerCount = 0;
            stateDelay++;
        }
        if (stateDelay == 10)
        {
            state = 1; // Switch to Mode 2
            stateDelay = 0;
        }
    }
    else // Mode 2: 2 sec interval
    {
        if (timerCount >= 123) // 2 sec..
        {
            PORTB ^= (1 << PORTB5); // Toggle LED
            timerCount = 0;
            stateDelay++;
        }
        if (stateDelay == 5)
        {
            state = 0; // Switch back to Mode 1
            stateDelay = 0;
        }
    }
}

void loop()
{
}