void setup() {
	DDRD |= 0b00001000; // setting port 3 as output
  	DDRD |= 0b00010000; // setting port 4 as output
}

void loop() {
  	PORTD |= 0b00001000; // yellow on 
  	PORTD &= ~0b00010000; // green off: 1 & 0 = 0
  	delay(1000); // delay 1000 mili seconds = 1 second
  	PORTD &= ~0b00001000; // yellow off
  	PORTD |= 0b00010000; // green on
   	delay(1000); // delay 1000 mili seconds = 1 second

}