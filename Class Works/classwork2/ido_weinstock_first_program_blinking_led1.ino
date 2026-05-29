/*
  This program turns on for 1 sec and then turns off for 1 sec
  pin 13 of the Arduino (the built-in LED) - HIGH/LOW
*/

void setup()
{
  DDRB |= 0b00000010;
}

void loop()
{
  PORTB |= 0b00000010;
  delay(1000);
  PORTB &= 0b11111101;
  delay(3000);
}