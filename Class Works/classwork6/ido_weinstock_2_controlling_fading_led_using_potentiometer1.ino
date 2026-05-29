void setup_pwm() {
  // 1. Set Pin 3 (PD3 / OC2B) as an OUTPUT
  DDRD |= (1 << DDD3);

  // 2. Configure Timer2 for Fast PWM Mode (WGM21=1, WGM20=1)
  // Clear OC2B on Compare Match, set OC2B at BOTTOM (Non-inverting mode: COM2B1=1, COM2B0=0)
  TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);

  // 3. Set Timer2 Prescaler to 64 (CS22=1, CS21=0, CS20=0)
  TCCR2B = (1 << CS22);

  // Initialize Duty Cycle to 0 (LED off)
  OCR2B = 0;
}

void setup() {
  // Initialize Timer2 PWM registers
  setup_pwm();
  
  // Initialize Serial Monitor (Optional, helpful for debugging)
  Serial.begin(9600);
}

void loop() {
  // a. Read the value from the potentiometer using "analogRead()" (for simplicity)
  int potValue = analogRead(A0);

  // b. Map this value to a range suitable for PWM (0-1023 mapped to 0-255)
  int pwmValue = potValue / 4; 

  // c. Adjust the PWM duty cycle based on the mapped value by updating OCR2B
  OCR2B = pwmValue;

  // Small delay to stabilize the readings
  delay(10);
}