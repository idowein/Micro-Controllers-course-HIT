#include <stdio.h>

void displayBits( unsigned value );
unsigned int inverBitsUsingXor(unsigned int value);
int hammingDistance(unsigned int a, unsigned int b);
unsigned int countBits(unsigned int num);

void displayBits( unsigned value )
{ 
   unsigned c; /* counter */
   
   /* declare displayMask and left shift 31 bits */
   unsigned displayMask = 1 << 31;

   printf( "%7u = ", value );

   /* loop through bits */
   for ( c = 1; c <= 32; c++ ) { 
      putchar( value & displayMask ? '1' : '0' );
      value <<= 1; /* shift value left by 1 */

      if ( c % 8 == 0 ) { /* output a space after 8 bits */
         putchar( ' ' );
      } /* end if */

   } /* end for */

   putchar( '\n' );
} /* end function displayBits */

// Task 1
unsigned int inverBitsUsingXor(unsigned int value){
    unsigned int mask = 0xFFFFFFFF; // mask definition
    // Note: unsigned - MSB is not a sign bit. always positive value
    // int - 32 bits, 4 bytes, 2 words.
    // 0x - Exa
    // 8 * F = 32 * 1 = 1111 ... 11 (32 times)
    return value ^ mask; // ^ = XOR operation
}

// Task 1 - second way (using not gate)
// Note - not to check!! only for myself
unsigned int inverBitsUsingNot(unsigned int value){
    return ~value; // ~ filps each bit
}

// Task 2 - Hamming Distance
int hammingDistance(unsigned int a, unsigned int b) {

}

// This function counts how many bits are set up to '1'
unsigned int countBits(unsigned int num) {
    unsigned int counter = 0;
    unsigned int mask = 1; // 0000001
    int i;
    for (i = 0; i < 8; i++) {
        if (num & mask)
            counter++;
        mask <<= 1; // mask = mask << 1
    }
    return counter;
}

void main()
{
    unsigned int value = 5;

    // Check that Display bits function works
    printf("--- Original Number ---\n");
    displayBits(value);

    // Check that Task 1 works
    unsigned int result = inverBitsUsingXor(value);

    printf("\n--- After XOR Invert ---\n");
    displayBits(result);

    // Check that CountBits actually counts the set up '1' bits.
    printf("\n--- After set up bits counting ---\n");
    unsigned int num1 = 75;
    displayBits(num1);
    unsigned int num2 = countBits(num1);
    printf("number of bits %u ", num2);

}

