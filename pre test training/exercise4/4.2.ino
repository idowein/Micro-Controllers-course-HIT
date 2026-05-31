// Defining the Pin numbers as macros for better code maintenance
#define BUTTON_PIN      2    // Button is on Port D, Pin 2 (INT0 - wired in the board)
// pin3 wired to INT1
#define GREEN_LED_PIN   5    // Green LED is on Port B, Pin 5 (Digital Pin 13)

void setup() {
    /* 1. Configure I/O Directions using (1 << pin) */
    // Clear bit 3 in DDRD to set it as INPUT
    DDRD &= ~(1 << BUTTON_PIN); 
    
    // Set bit 4 in DDRB to set it as OUTPUT
    DDRB |= (1 << GREEN_LED_PIN);  
  
  	EICRA &= 0b11111100; // register zero configuration
  
    /* 2. Configure External Interrupt Control Register A (EICRA) */
    // Set INT0 to trigger on a LOGIC CHANGE (ISC01 = 0, ISC00 = 0)
    EICRA |= (1 << 0); 

    /* 3. Configure External Interrupt Mask Register (EIMSK) */
    // Enable External Interrupt Request 1 (INT0)
  	EIMSK |= (1 << INT0);

    /* 4. Enable Global Interrupts */
    sei(); 
}

void loop() {
    // Main loop remains empty. The microcontroller waits in hardware for the interrupt.
}

/* 5. Interrupt Service Routine (ISR) for INT0 */
ISR(INT0_vect) {
    // Toggle the Green LED using the (1 << pin) configuration inside the XOR operation
    if(PIND & (1<<BUTTON_PIN))	
  		PORTB |= (1 << GREEN_LED_PIN); 
    else
       	PORTB &= ~(1 << GREEN_LED_PIN);
}