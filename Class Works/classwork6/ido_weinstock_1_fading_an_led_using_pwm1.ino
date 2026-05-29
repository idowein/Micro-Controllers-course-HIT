void setup_pwm() {
  // 1. Set Pin 3 (PD3 / OC2B) as an OUTPUT
  DDRD |= (1 << DDD3);

  // 2. Configure Timer2 for Fast PWM Mode (WGM21=1, WGM20=1)
  // And configure Clear OC2B on Compare Match, set OC2B at BOTTOM (Non-inverting mode: COM2B1=1, COM2B0=0)
  TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);

  // 3. Set Timer2 Prescaler to 64 (CS22=1, CS21=0, CS20=0)
  // This provides a smooth PWM frequency (~976 Hz) so the human eye won't see blinking
  TCCR2B = (1 << CS22);

  // Initialize Duty Cycle to 0 (LED off)
  OCR2B = 0;
}

void setup() {
  // Call the PWM register configuration function
  setup_pwm();
}

void loop() {
  // Fade In: Gradually make the LED brighter (increase duty cycle)
  for (int brightness = 0; brightness <= 255; brightness++) {
    OCR2B = brightness; // Update Timer2 compare register B directly
    delay(10);          // Allowed delay by the guidelines
  }

  // Fade Out: Gradually make the LED dimmer (decrease duty cycle)
  for (int brightness = 255; brightness >= 0; brightness--) {
    OCR2B = brightness; // Update Timer2 compare register B directly
    delay(10);          // Allowed delay by the guidelines
  }
}