// --- Configuration ---

// LEDs (Outputs) - Using Pins 11, 12, 13
#define LED1_PIN PB3 // Digital 11 (MSB)
#define LED2_PIN PB4 // Digital 12
#define LED3_PIN PB5 // Digital 13 (LSB)
#define LED_PORT PORTB
#define LED_DDR  DDRB

// Switches (Interrupts)
#define SW1_PIN PD2 // INT0 - Increment State
#define SW2_PIN PD3 // INT1 - Reset State

// Macro for Interrupt Setup
#define SET_INT0_RISING_EDGE EICRA |= ((1 << ISC01) | (1 << ISC00))
#define SET_INT1_RISING_EDGE EICRA |= ((1 << ISC11) | (1 << ISC10))
#define ENABLE_INT0          EIMSK |= (1 << INT0)
#define ENABLE_INT1          EIMSK |= (1 << INT1)

// Global state variable (0 to 7)
volatile uint8_t currentState = 0;

/**
 * @brief Updates the LED outputs based on the currentState (Binary representation)
 */
void updateLEDs() {
    // Clear the bits first
    LED_PORT &= ~((1 << LED1_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN));
    
    // Set bits based on binary value of currentState
    if (currentState & 0x04) LED_PORT |= (1 << LED1_PIN); // MSB
    if (currentState & 0x02) LED_PORT |= (1 << LED2_PIN);
    if (currentState & 0x01) LED_PORT |= (1 << LED3_PIN); // LSB
}

void setup() {
    cli(); // Disable interrupts during setup

    // 1. Configure LEDs as Output
    LED_DDR |= (1 << LED1_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN);
    
    // 2. Configure Switches as Input
    DDRD &= ~((1 << SW1_PIN) | (1 << SW2_PIN));
    
    // 3. Configure External Interrupts on Rising Edge
    SET_INT0_RISING_EDGE;
    SET_INT1_RISING_EDGE;
    
    // 4. Enable Interrupts
    ENABLE_INT0;
    ENABLE_INT1;

    updateLEDs(); // Start with Initial State (All 0)
    
    sei(); // Enable global interrupts
}

void loop() {
    // Main loop remains empty as logic is fully interrupt-driven
}

/**
 * ISR for SW1 (INT0) - Increment Logic
 */
ISR(INT0_vect) {
    currentState++;
    
    // After 7th press (State 7), return to Initial State (0)
    if (currentState > 7) {
        currentState = 0;
    }
    
    updateLEDs();
}

/**
 * ISR for SW2 (INT1) - Reset Logic
 */
ISR(INT1_vect) {
    // Reset to Initial State regardless of current progress
    currentState = 0;
    updateLEDs();
}