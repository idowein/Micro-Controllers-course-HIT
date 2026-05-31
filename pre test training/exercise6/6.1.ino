void setup() {
  // Initialize the Serial Monitor at 9600 baud rate
  Serial.begin(9600);

  // Set ADMUX to use AVcc as reference voltage and select relevant input channel (defined in PDF)
  ADMUX |= (1 << REFS0) | (1 << MUX2); // MUX2 = ADC4 = A4 get the input from A4
  
  // all the pins in page 217

  // Set ADCSRA to enable ADC, set prescaler to 128 (16 MHz / 128 = 125 kHz ADC clock)
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void loop() {
  // Start ADC conversion - ADSC - A.D Start Conversion
  ADCSRA |= (1 << ADSC);

  // Wait for conversion to complete
  while (ADCSRA & (1 << ADSC)); // ADCSRSA & (1 << ADSC) = 1 while A/D is going on

  // Read the converted value (10 bits) from ADCL and ADCH registers
  uint16_t digital_value = ADC;

  // Print the digital value to the Serial Monitor
  Serial.println(digital_value);

  // Wait for defined time (PDF) before the next reading
  delay(400);
}
