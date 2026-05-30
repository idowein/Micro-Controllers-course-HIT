// Defining the Pin numbers as macros for better code maintenance
#define BUTTON_PIN      3    // Button is on Port D, Pin 3 (INT1)
#define GREEN_LED_PIN   4    // Green LED is on Port B, Pin 4 (Digital Pin 12)
#define PORT_LED_PIN    PORTB4  // The corresponding bit for LED inside PORTB register

void setup() {
    /* 1. Configure I/O Directions using (1 << pin) */
    // Clear bit 3 in DDRD to set it as INPUT
    DDRD &= ~(1 << BUTTON_PIN); 
    
    // Set bit 4 in DDRB to set it as OUTPUT
    DDRB |= (1 << GREEN_LED_PIN);  

    /* 2. Configure External Interrupt Control Register A (EICRA) */
    // Set INT1 to trigger on a RISING EDGE (ISC11 = 1, ISC10 = 1)
    EICRA |= (1 << 3) | (1 << 2); 

    /* 3. Configure External Interrupt Mask Register (EIMSK) */
    // Enable External Interrupt Request 1 (INT1)
    EIMSK |= (1 << INT1);  

    /* 4. Enable Global Interrupts */
    sei(); 
}

void loop() {
    // Main loop remains empty. The microcontroller waits in hardware for the interrupt.
}

/* 5. Interrupt Service Routine (ISR) for INT1 */
ISR(INT1_vect) {
    // Toggle the Green LED using the (1 << pin) configuration inside the XOR operation
    PORTB ^= (1 << PORT_LED_PIN); 
}