// =====================================================================================
// THE 'volatile' KEYWORD EXPLANATION:
// 
// By declaring 'adc_value' as 'volatile', we tell the compiler's optimizer:
// "This variable can change its value at any moment outside the normal program flow 
// (specifically, from inside a hardware interrupt service routine)."
//
// Without 'volatile', the compiler looks at the empty 'void loop()' and thinks:
// "Nobody updates 'adc_value' inside the main program loop, so its value will always be 0.
// I can optimize the code by keeping it in a CPU register or ignoring its updates."
//
// 'volatile' forces the compiler to ALWAYS read the actual value directly from the RAM 
// every single time it is accessed, ensuring the main program (or other interrupts) 
// will always see the real, updated data written by the hardware.
// =====================================================================================
volatile uint16_t adc_value;

void setup() {
  // Initialize the Serial Monitor at 9600 baud rate
  Serial.begin(9600);

  // Set ADMUX to use AVcc as reference voltage and select relevant input channel (defined in PDF)
  ADMUX |= (1 << REFS0);

  // Set ADCSRA to enable ADC, enable ADC interrupt, set prescaler to 128 (16 MHz / 128 = 125 kHz ADC clock)
  ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // Enable global interrupts
  sei();
  
  // Start ADC conversion
  ADCSRA |= (1 << ADSC);
}

// ADC conversion complete interrupt service routine - auto active when ADIE active
ISR(ADC_vect) {
  // =====================================================================================
  // Inside this ISR, 'adc_value' is updated whenever the hardware finishes a conversion.
  // Because it was declared 'volatile', the compiler knows that this write operation 
  // must immediately update the variable's true location in memory (RAM), so that any 
  // future code reading it will get the freshly captured analog-to-digital value.
  // =====================================================================================
  adc_value = ADC;
  
  // COMPLETE: Print the digital values only above defined threshold (PDF)
  if (adc_value > 400) {
    Serial.println(adc_value);
  }
      
  // Start next ADC conversion
  ADCSRA |= (1 << ADSC);
}

void loop() {
  // Even though this loop is empty, if you decide to read 'adc_value' here in the future,
  // the 'volatile' keyword ensures that you read the latest value captured by the ISR,
  // preventing the CPU from using old, cached, or optimized-out data.
}