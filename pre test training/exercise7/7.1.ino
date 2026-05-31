void setup_pwm() {
  // 1. Set Pin 3 (PD3 / OC2B) as an OUTPUT
  DDRD |= (1 << DDD3);

  // 2. Configure Timer2 for Fast PWM Mode (WGM21=1, WGM20=1)
  // And configure Clear OC2B on Compare Match, set OC2B at BOTTOM (Non-inverting mode)
  TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);

  // 3. Set Timer2 Prescaler to 64 (CS22=1)
  // This provides a smooth PWM frequency (~976 Hz)
  TCCR2B = (1 << CS22);

  /* * =========================================================================
   * BLOCK 4: DUTY CYCLE INITIALIZATION (OCR2B = 0)
   * =========================================================================
   * EXPLANATION:
   * In Non-Inverting Fast PWM mode, Timer2 constantly counts from 0 to 255.
   * - Hardware Rule 1: Pin 3 turns HIGH (5V) when the timer resets to 0 (BOTTOM).
   * - Hardware Rule 2: Pin 3 turns LOW (0V) when the timer matches the OCR2B value.
   * * By initializing OCR2B to 0, a unique hardware condition occurs:
   * 1. The timer starts at 0 -> Pin 3 tries to switch HIGH.
   * 2. Immediately, the hardware detects that the timer equals OCR2B (0 == 0).
   * 3. Pin 3 is instantly forced LOW within a fraction of a microsecond.
   * 4. For the rest of the cycle (1 to 255), the pin remains completely LOW.
   * * RESULT:
   * The pin stays LOW for 100% of the cycle, meaning the Duty Cycle is 0%.
   * This ensures the LED starts completely OFF, preventing any unwanted voltage 
   * glitches or bright flashes when the microcontroller powers up.
   * * -------------------------------------------------------------------------
   * EXAMPLES FOR COMPARISON:
   * * Example A (This Block):
   * OCR2B = 0    -> ON-time = 0 counts, Total-time = 256 counts.
   * Formula      -> (0 / 256) * 100% = 0% Duty Cycle (LED is Completely OFF).
   * * Example B (Mid-brightness during Loop):
   * OCR2B = 128  -> ON-time = 128 counts, Total-time = 256 counts.
   * Formula      -> (128 / 256) * 100% = 50% Duty Cycle (LED is Half bright).
   * * Example C (Max brightness during Loop):
   * OCR2B = 255  -> ON-time = 255 counts, Total-time = 256 counts.
   * Formula      -> (255 / 256) * 100% = ~100% Duty Cycle (LED is Fully ON).
   * =========================================================================
   */
  OCR2B = 0; // Initialize Duty Cycle to 0% (LED safely off at startup)
}

void setup() {
  // Call the PWM register configuration function
  setup_pwm();
}

void loop() {
  // Fade In: Gradually make the LED brighter (increase duty cycle)
  for (int brightness = 0; brightness <= 255; brightness++) {
    OCR2B = brightness; // Update Timer2 compare register B directly
    delay(10);          
  }

  // Fade Out: Gradually make the LED dimmer (decrease duty cycle)
  for (int brightness = 255; brightness >= 0; brightness--) {
    OCR2B = brightness; // Update Timer2 compare register B directly
    delay(10);          
  }
}