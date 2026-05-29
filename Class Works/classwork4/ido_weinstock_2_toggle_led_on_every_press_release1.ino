// LED output macro definitions
#define LED_PIN 5                   // Pin 12 on Arduino Uno maps to PB4
#define LED_PORT PORTB              // Data Register for Port B
#define LED_DDR DDRB               // Data Direction Register for Port B


#define TURN_ON_LED(port, pin)  (port |= (1 << pin))

#define TURN_OFF_LED(port, pin) (port &= ~(1 << pin))

// Switch (SW) input macro definitions
#define SW_PIN 2                    // Pin 3 on Arduino Uno maps to PD3
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
  // Polling the input register to check pushbutton status
  if (BUTTON_IS_PRESSED(SW_INPUT, SW_PIN)) { // There is no need for != question
    // Logic: If voltage detected at PD3, drive PB4 HIGH
    TURN_ON_LED(LED_PORT, LED_PIN);
  } 
  else {
    // Logic: If no voltage detected, drive PB4 LOW
    TURN_OFF_LED(LED_PORT, LED_PIN);
  }
}