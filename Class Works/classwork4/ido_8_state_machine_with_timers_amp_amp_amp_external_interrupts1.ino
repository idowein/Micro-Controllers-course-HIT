#include <avr/io.h>
#include <avr/interrupt.h>

// --- PIN DEFINITIONS (PORTB) ---
#define LED1_PIN   (1 << DDB3) // Pin 11
#define LED2_PIN   (1 << DDB4) // Pin 12
#define LED3_PIN   (1 << DDB5) // Pin 13
#define ALL_LEDS   (LED1_PIN | LED2_PIN | LED3_PIN)

// --- TIMER1 CONFIGURATION ---
#define TIMER1_PRESCALER_1024  ((1 << CS12) | (1 << CS10))
#define TIMER1_CTC_MODE        (1 << WGM12)
#define TIMER1_COMPA_ENABLE    (1 << OCIE1A)

// Calculation for exactly 2 seconds delay:
// (16,000,000 Hz / 1024 prescaler) * 2 seconds = 31,250 steps.
// Counts from 0, so: 31,250 - 1 = 31,249
#define COMPARE_VALUE_2_SEC    31249

// --- GLOBAL STATE MACHINE VARIABLES ---
// volatile is required because these variables change inside ISRs
volatile uint8_t currentState = 0; 

// Array defining the binary representation for LEDs for each state (0 to 7)
// Bit 0 -> LED3, Bit 1 -> LED2, Bit 2 -> LED1
const uint8_t stateTable[8] = {
    0b000, // State 0 (Initial State): All off
    0b001, // State 1: LED3 on
    0b010, // State 2: LED2 on
    0b011, // State 3: LED2 & LED3 on
    0b100, // State 4: LED1 on
    0b101, // State 5: LED1 & LED3 on
    0b110, // State 6: LED1 & LED2 on
    0b111  // State 7: All on
};

// --- FUNCTION TO UPDATE LEDS BASED ON STATE ---
void updateLEDs(uint8_t state) {
    uint8_t binValue = stateTable[state];
    
    // Clear current LED pins, then set them according to the state table
    PORTB &= ~ALL_LEDS;
    
    if (binValue & 0b100) PORTB |= LED1_PIN; // MSB controls LED1
    if (binValue & 0b010) PORTB |= LED2_PIN; // Middle bit controls LED2
    if (binValue & 0b001) PORTB |= LED3_PIN; // LSB controls LED3
}

void setup()
{
    // 1. Configure LED Pins as Outputs
    DDRB |= ALL_LEDS;
    
    // 2. Configure Button Pin (PD2 / INT0) as Input with Pull-up
    DDRD &= ~(1 << DDD2);   // Set PD2 as input
    PORTD |= (1 << PORTD2); // Enable internal pull-up resistor

    // Disable interrupts during configurations
    cli();

    // 3. Configure Timer1 for 2-Second CTC Interrupts
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    
    OCR1A = COMPARE_VALUE_2_SEC;
    TCCR1B |= TIMER1_CTC_MODE | TIMER1_PRESCALER_1024;
    TIMSK1 |= TIMER1_COMPA_ENABLE;

    // 4. Configure External Interrupt 0 (INT0) for the Switch
    // ISC01 = 1, ISC00 = 0 -> Trigger on Falling Edge (button press pulls to GND)
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0);  // Enable External Interrupt 0

    // Set initial state representation on boot
    updateLEDs(currentState);

    // Enable global interrupts
    sei();
}

// --- TIMER1 ISR: AUTOMATIC STATE TRANSITION (EVERY 2 SECONDS) ---
ISR(TIMER1_COMPA_vect)
{
    currentState++;
    if (currentState > 7) {
        currentState = 0; // Wrap around to Initial State after State #7
    }
    updateLEDs(currentState);
}

// --- EXTERNAL INTERRUPT 0 ISR: RESET BUTTON PRESSED ---
ISR(INT0_vect)
{
    currentState = 0;   // Reset state back to Initial State
    TCNT1 = 0;          // Clear Timer1 counter to reset the 2-second period
    updateLEDs(currentState);
}

void loop()
{
    // The entire application runs asynchronously using hardware timers 
    // and external interrupts. The main loop stays perfectly clean.
}