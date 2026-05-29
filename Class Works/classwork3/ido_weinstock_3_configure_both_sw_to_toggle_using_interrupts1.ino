// --- Macro Definitions ---
#define GREEN_LED PB4 // Pin 12
#define RED_LED   PB5 // Pin 13
#define LED_PORT  PORTB
#define LED_DDR   DDRB

// Configuration Macros
#define SET_INT0_RISING_EDGE EICRA |= ((1 << ISC01) | (1 << ISC00))
#define SET_INT1_RISING_EDGE EICRA |= ((1 << ISC11) | (1 << ISC10))
#define ENABLE_INT0          EIMSK |= (1 << INT0)
#define ENABLE_INT1          EIMSK |= (1 << INT1)

void setup() {
    cli(); // Disable interrupts during configuration

    // i. Configure Inputs/Outputs
    LED_DDR |= (1 << GREEN_LED) | (1 << RED_LED); // Outputs
    DDRD &= ~((1 << DDD2) | (1 << DDD3));         // Inputs (Pins 2, 3)

    // ii. Configure both switches to work with interrupts on Rising Edge
    SET_INT0_RISING_EDGE;
    SET_INT1_RISING_EDGE;
    
    ENABLE_INT0;
    ENABLE_INT1;

    sei(); // Enable global interrupts
}

void loop() {
    // Logic is fully interrupt-driven
}

/**
 * ISR for SW1 (INT0 - Left Button)
 * This button affects BOTH Green and Red LEDs.
 */
ISR(INT0_vect) {
    LED_PORT ^= (1 << GREEN_LED); // Toggle Green
    LED_PORT ^= (1 << RED_LED);   // Toggle Red
}

/**
 * ISR for SW2 (INT1 - Right Button)
 * This button affects ONLY the Red LED.
 */
ISR(INT1_vect) {
    LED_PORT ^= (1 << RED_LED);   // Toggle Red
}