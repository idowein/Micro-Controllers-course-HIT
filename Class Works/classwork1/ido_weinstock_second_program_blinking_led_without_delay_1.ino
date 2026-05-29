void setup()
{
  DDRD |= 0b10000000; // Set the relevant pin in the relevant port as OUTPUT
}

void loop()
{
  PORTD ^= 0b10000000; // Toggle relevant pin (using XOR)
  
  // fill in a guess for your CPU speed to get the desired time - part 1
  long i=100000;
  do {i--;}
  while (i != 0);
  
  PORTD ^= 0b10000000; // Toggle relevant pin (using XOR)
  
  // fill in a guess for your CPU speed to get the desired time - part 2
  long j=100000;
  do {j--;}
  while (j != 0);
}