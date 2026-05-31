volatile uint16_t secondsCounter = 0;
volatile uint16_t digitalValue;

void timer_setup()
{
  // Clear Timer1 control registers to start from a clean state
  TCCR1A = 0;
  TCCR1B = 0;

  // Initialize Timer1 counter value to 0
  TCNT1 = 0;

  // Set Timer1 prescaler to 256 - page 110
  TCCR1B |= (1 << CS12);

  // Configure CTC Mode where TOP = OCR1A
  TCCR1B |= (1<<WGM12); // page 10 - CTC mode in timer 1
  
  // Set the value for the output compare register
  // 16MHZ / 256 = 62,500
  // each 62,500 cycles 1 second passed. 
  OCR1A = 62499; // from 0 to 62499 = 62500 numbers

  // Enable Timer1 compare match interrupt
  TIMSK1 |= (1 << OCIE1A); // enable the comparison between cycle and 62499
}

void adc_setup()
{
  // Set ADMUX to use AVcc as reference voltage and select relevant input channel (defined in PDF)
  ADMUX |= (1 << REFS0) | (1<<MUX2); // listen to port A4

  // Set ADCSRA to enable ADC
   ADCSRA |= (1 << ADEN)| (1<<ADIE); // enabling the interupt of the adc

  // Set ADC prescaler to 128 (16 MHz / 128 = 125 kHz ADC clock)
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  
  // Enable ADC Interrupts
  ADCSRA |= (1 << ADSC);
}

void setup() {
  // Initialize the Serial Monitor at 9600 baud rate
  Serial.begin(9600);
  
  cli();
  
  // Call "timer_setup" function
  timer_setup();
  
  // Call "adc_setup" function
  adc_setup();
  
  sei();
}

// Interrupt Service Routine (ISR) for Timer1 compare match interrupt
ISR(TIMER1_COMPA_vect)
{
  secondsCounter++;
  if (secondsCounter == 1)
  {
    // Start next ADC conversion
  	ADCSRA |= (1 << ADSC);
    secondsCounter = 0;
  }
}

ISR(ADC_vect) {
  // Read the converted value (10 bits) from ADCL and ADCH registers
  digitalValue = ADC;

  // Print the digital value to the Serial Monitor
  Serial.println(digitalValue);
}

void loop() {
}