// --- MACROS AS REQUESTED ---
#define TIMER_PRESCALER_BITS            ((1 << CS20) | (1 << CS21) | (1 << CS22)) // Prescaler = 1024
#define TIMER_OVERFLOW_INTERRUPT_ENABLE_BIT (1 << TOIE2)

// Interrupt count thresholds to achieve the required blink rate (based on your previous logic)
#define TIMER_THRESHOLD_MODE_1          61  // 1 sec toggle rate
#define TIMER_THRESHOLD_MODE_2          122 // 2 sec toggle rate
#define TIMER_THRESHOLD_MODE_3          305 // 5 sec toggle rate

// Number of toggles required to finish 10 seconds in each mode
#define STATE_DELAY_MODE_1              10  // 10 toggles * 1 sec = 10 sec
#define STATE_DELAY_MODE_2              5   // 5 toggles * 2 sec = 10 sec
#define STATE_DELAY_MODE_3              2   // 2 toggles * 5 sec = 10 sec

// --- GLOBAL VARIABLES ---
volatile unsigned int timerCount = 0;
volatile unsigned int state = 0;      // 0 = Mode 1, 1 = Mode 2, 2 = Mode 3
volatile unsigned int stateDelay = 0; // Tracks duration spent in the current mode

void setup()
{
    // Set digital pin 13 (PORTB5) as output
    DDRB |= (1 << DDB5);

    // Disable global interrupts during configuration
    cli();

    // Clear Timer2 control registers
    TCCR2A = 0;
    TCCR2B = 0;

    // Clear Timer2 count register
    TCNT2 = 0;

    // Apply configuration using the defined macros
    TCCR2B |= TIMER_PRESCALER_BITS;
    TIMSK2 |= TIMER_OVERFLOW_INTERRUPT_ENABLE_BIT;

    // Enable global interrupts
    sei();
}

// --- TIMER2 OVERFLOW INTERRUPT SERVICE ROUTINE ---
ISR(TIMER2_OVF_vect)
{
    timerCount++;

    // --- MODE 1: 1 Second Blink Rate ---
    if (state == 0)
    {
        if (timerCount >= TIMER_THRESHOLD_MODE_1)
        {
            PORTB ^= (1 << PORTB5); // Toggle LED
            timerCount = 0;
            stateDelay++;
        }
        if (stateDelay >= STATE_DELAY_MODE_1)
        {
            state = 1;              // Switch to Mode 2
            stateDelay = 0;
        }
    }
    // --- MODE 2: 2 Second Blink Rate ---
    else if (state == 1)
    {
        if (timerCount >= TIMER_THRESHOLD_MODE_2)
        {
            PORTB ^= (1 << PORTB5); // Toggle LED
            timerCount = 0;
            stateDelay++;
        }
        if (stateDelay >= STATE_DELAY_MODE_2)
        {
            state = 2;              // Switch to Mode 3
            stateDelay = 0;
        }
    }
    // --- MODE 3: 5 Second Blink Rate ---
    else if (state == 2)
    {
        if (timerCount >= TIMER_THRESHOLD_MODE_3)
        {
            PORTB ^= (1 << PORTB5); // Toggle LED
            timerCount = 0;
            stateDelay++;
        }
        if (stateDelay >= STATE_DELAY_MODE_3)
        {
            state = 0;              // Reset back to Mode 1
            stateDelay = 0;
        }
    }
}

void loop ()
{
}