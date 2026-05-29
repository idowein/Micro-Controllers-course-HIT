void setup() 
{
  // Initialize hardware serial communication at a baud rate of 9600 bits per second
  Serial.begin(9600);

  // Configure ADC Voltage Reference:
  // Setting REFS0 to 1 selects AVcc (5V) as the voltage reference.
  ADMUX |= (1 << REFS0);

  // Configure ADC Input Channel Selection:
  // To select ADC0 (Channel 0), all MUX bits (MUX3:0) must be 0.
  // Since ADMUX is 0 by default, we don't need to set any MUX bits here.

  // Configure ADC Prescaler:
  // Setting ADPS2, ADPS1, and ADPS0 to 1 selects a division factor of 128.
  // This divides 16 MHz down to 125 kHz for maximum accuracy.
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // Enable the ADC module by setting the ADC Enable (ADEN) bit to 1
  ADCSRA |= (1 << ADEN);
}

void loop() 
{
  // Start a single Analog-to-Digital conversion by setting the ADC Start Conversion (ADSC) bit to 1
  ADCSRA |= (1 << ADSC);

  // Wait/Poll until the conversion is complete:
  // The ADSC bit remains high (1) as long as the conversion is in progress.
  while (ADCSRA & (1 << ADSC));

  // Read the raw 10-bit digital result from the ADC data register
  uint16_t digital_value = ADC;

  // Transmit the read digital value over the serial port followed by a newline character
  Serial.println(digital_value);

  // Block execution/delay for 400 milliseconds as requested
  delay(400);
}