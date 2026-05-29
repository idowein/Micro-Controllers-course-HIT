// LED output macro definitions
#define LED_PIN 4                   // Pin 12 on Arduino Uno maps to PB4
#define LED_PORT PORTB              // Data Register for Port B
#define LED_DDR DDRB               // Data Direction Register for Port B

#define TOGLE_LED(port, pin)  (port ^= (1 << pin))

// Switch (SW) input macro definitions
#define SW_PIN 3                    // Pin 3 on Arduino Uno maps to PD3
#define SW_DDR DDRD                 // Data Direction Register for Port D
#define SW_INPUT PIND               // Port Input Pins Register for Port D (Read-only)

#define SET_SW_AS_INPUT(port, pin) (port &= ~(1 << pin))

#define BUTTON_IS_PRESSED(port, pin) (port & (1 << pin))

void setup() {
  // Initialize LED_PIN as OUTPUT by setting the corresponding bit
  LED_DDR |= (1 << LED_PIN);        
  
  // Initialize SW_PIN as INPUT by clearing the corresponding bit
  SET_SW_AS_INPUT(SW_DDR, SW_PIN);  
}

void loop() {
  // 1. Check if button is pressed
  if (BUTTON_IS_PRESSED(SW_INPUT, SW_PIN)) { 
    
    // Perform the Toggle
    TOGLE_LED(LED_PORT, LED_PIN);
    
    // 2. Simple Debounce: wait for contacts to stabilize
    delay(50); 
    
    // 3. Busy Wait: stay here as long as the button is still held down
    // This prevents multiple toggles during a single long press
    while (BUTTON_IS_PRESSED(SW_INPUT, SW_PIN)) {
      // Do nothing, just wait for release
    }
    
    // 4. Another small delay to handle the release bounce
    delay(50);
  } 
}