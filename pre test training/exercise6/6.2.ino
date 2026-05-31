volatile uint16_t adc_value;

void setup() {
  // Initialize the Serial Monitor at 9600 baud rate
  Serial.begin(9600);

  // Set ADMUX to use AVcc as reference voltage and select input channel 4 (ADC4/A4)
  ADMUX |= (1 << REFS0) | (1 << MUX2); 

  // Configure ADCSRA:
  // 1. ADEN: Enable the ADC peripheral
  // 2. ADIE: Enable ADC Conversion Complete Interrupt
  // 3. ADPS2, ADPS1, ADPS0: Set prescaler to 128 (16 MHz / 128 = 125 kHz ADC clock)
  ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // Enable global interrupts
  sei();
  
  // Start the very first ADC conversion
  ADCSRA |= (1 << ADSC);
}

// ADC conversion complete interrupt service routine (ISR)
// This function triggers automatically by hardware when a conversion finishes
ISR(ADC_vect) {
  // Read the 10-bit converted value from the combined ADC register (ADCL + ADCH)
  adc_value = ADC;
  
  // Print the digital value only if it is strictly above the defined threshold of 400
  if (adc_value > 400) {
    Serial.println(adc_value);
  }
      
  // Start the next ADC conversion to keep the cycle running asynchronously
  ADCSRA |= (1 << ADSC);
}

void loop() {
  // The main loop remains completely empty and unblocked, freeing up the CPU
}