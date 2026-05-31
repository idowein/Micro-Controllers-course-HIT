// Defining the Pin numbers as macros for better code maintenance
#define BUTTON_PIN      2    // Button is on Port D, Pin 2 (INT0)
#define GREEN_LED_PIN   5    // Green LED is on Port B, Pin 5 (Digital Pin 13)

void setup() {
    /* 1. Configure I/O Directions using (1 << pin) */
    DDRD &= ~(1 << BUTTON_PIN); // Set Pin 2 as INPUT
    DDRB |= (1 << GREEN_LED_PIN); // Set Pin 13 as OUTPUT
  
    // Zeroing out the INT0 control bits (ISC01 and ISC00) safely
    EICRA &= ~((1 << ISC01) | (1 << ISC00)); 
  
    /* 2. Configure EICRA for Any Logical Change */
    // Setting ISC01 = 0, ISC00 = 1 triggers the ISR on both PRESS and RELEASE
    EICRA |= (1 << ISC00);  

    /* 3. Configure External Interrupt Mask Register (EIMSK) */
    EIMSK |= (1 << INT0); // Enable INT0

    /* 4. Enable Global Interrupts */
    sei(); 
}

void loop() {
    // Empty
}

/* 5. Interrupt Service Routine (ISR) for INT0 */
ISR(INT0_vect) {
    // Read the current physical state of Port D Pin 2
    if (PIND & (1 << BUTTON_PIN)) {
        // Button is currently PRESSED (Signal is HIGH due to external pull-down)
        PORTB |= (1 << GREEN_LED_PIN);  // Turn ON the LED
    } 
    else {
        // Button is currently RELEASED (Signal dropped to LOW)
        PORTB &= ~(1 << GREEN_LED_PIN); // Turn OFF the LED
    }
}