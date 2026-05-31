#define RED_PIN (1 << 3)
#define YELLOW_PIN (1 << 4)
#define GREEN_PIN (1 << 5)

uint16_t PART1 = 1024/3;
uint16_t PART2 = 1024*2/3;
// uint16_t PART3 = 1024; // not required..

volatile uint16_t digitalValue;

void adc_setup()
{
  // Set ADMUX to use AVcc as reference voltage and select ADC0 as input channel
  ADMUX |= (1 << REFS0);

  // Set ADCSRA to enable ADC
  ADCSRA|= (1 << ADEN);

  // Set ADC prescaler to 128 (16 MHz / 128 = 125 kHz ADC clock)
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  
  // Enable ADC Interrupts
  ADCSRA |= (1 << ADIE);
}

void setup() {
  
  // Set pins 11 (PB3), 12 (PB4), and 13 (PB5) as outputs
  PORTB |= RED_PIN | YELLOW_PIN | GREEN_PIN;
  
  // Initialize the Serial Monitor at 9600 baud rate
  Serial.begin(9600);
  
  cli();
  
  // Call "adc_setup" function
  adc_setup();
  
  sei();
  
  // Start next ADC conversion
  	ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect) {
  // Read the converted value (10 bits) from ADCL and ADCH registers
  digitalValue = ADC;
  
  if (digitalValue <= PART1)
  {
    PORTB |= GREEN_PIN;
    PORTB &= ~YELLOW_PIN;
    PORTB &= ~RED_PIN;
  }
  else if (digitalValue <= PART2)
  {
    PORTB |= YELLOW_PIN;
    PORTB &= ~GREEN_PIN;
    PORTB &= ~RED_PIN;
  }
  else
  {
    PORTB |= RED_PIN;
    PORTB &= ~YELLOW_PIN;
    PORTB &= ~GREEN_PIN;
  }
  
  // Print the digital value to the Serial Monitor
  Serial.println(digitalValue);
  
  // Start next ADC conversion
  ADCSRA |= (1 << ADSC);
}

void loop() {
}
