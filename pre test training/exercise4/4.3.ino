// Defining the Pin numbers as macros for better code maintenance
#define BUTTON_PIN2      2    // Button is on Port D, Pin 2 (INT0)
#define BUTTON_PIN3      3    // Button is on Port D, Pin 3 (INT1)

#define RED_LED_PIN   5    // Green LED is on Port B, Pin 5 (Digital Pin 13)
#define GREEN_LED_PIN 4    // Red LED is on Port B, Pin 4 (Digital Pin 13)

void setup() {
    /* 1. Configure I/O Directions using (1 << pin) */
    // buttons declarations 
  	DDRD &= ~(1 << BUTTON_PIN2); // Set Pin 2 as INPUT
  	DDRD &= ~(1 << BUTTON_PIN3); // Set Pin 2 as INPUT
  	
  	// LED declarations
    DDRB |= (1 << GREEN_LED_PIN);
  	DDRB |= (1 << RED_LED_PIN);
  
    // Zeroing out the INT0&INT1 control bits 
    EICRA &= 0b1111000; 
  
    /* 2. Configure EICRA for Any Logical Change */
    // Setting ISC01 = 1, ISC00 = 1 - RISING EDGE BUTTON_PIN2
    EICRA |= (1 << 1);
  	EICRA |= (1 << 1);
  
  	// Setting ISC10 = 1, ISC11 = 1 - RISING EDGE BUTTON_PIN3
    EICRA |= (1 << 2);
  	EICRA |= (1 << 3);

    /* 3. Configure External Interrupt Mask Register (EIMSK) */
    EIMSK |= (1 << INT0); // Enable INT0
  	EIMSK |= (1 << INT1); // Enable INT1

    /* 4. Enable Global Interrupts */
    sei(); 
}

void loop() {
    // Empty
}

/* 5. Interrupt Service Routine (ISR) for INT0 */
ISR(INT0_vect) {
    PORTB ^= (1 << GREEN_LED_PIN);  // Turn ON the LED
  	PORTB ^= (1 << RED_LED_PIN);  // Turn ON the LED - any SW1 press effect on RED2	
}

ISR(INT1_vect) {
    PORTB ^= (1 << RED_LED_PIN);  // Turn ON the LED
}