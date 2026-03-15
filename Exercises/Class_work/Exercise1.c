#include <stdio.h>

void displayBits( unsigned value );


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

void main()
{
	unsigned value = 5;
	displayBits( value );
    printf( '\n');
    printf("%u\n", inverBitsUsingXor(value));
}

