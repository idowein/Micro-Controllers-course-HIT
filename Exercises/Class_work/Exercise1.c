#include <stdio.h>
#include <math.h>

void displayBits( unsigned value );
unsigned int inverBitsUsingXor(unsigned int value);
int hammingDistance(unsigned int a, unsigned int b);
unsigned int countBits(unsigned int num);
unsigned int swapBits(unsigned int value, int index1, int index2);

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
int hammingDistanceCalculator(unsigned int a, unsigned int b) {
    unsigned int diff = a ^ b; 
    printf("\n Value of the XOR between the 2 values: \n");
    displayBits(diff);
    // XOR between a and b will set new 32 bits int that set up where there is diffrence between them.
    int diffCounter = countBits(diff); // counting the differentiated bits
    return diffCounter;
}

// This function counts how many bits are set up to '1'
unsigned int countBits(unsigned int num) {
    unsigned int counter = 0;
    unsigned int mask = 1; // 0000...001
    int i;
    for (i = 0; i < 32; i++) {
        if (num & mask)
            counter++;
        mask <<= 1; // mask = mask << 1
    }
    return counter;
}

// Task 3
// Get value from index
unsigned int getValueFromIndex(unsigned int value, int index) {
    int unsigned mask = pow(2, index);
    int unsigned valueInIndex = mask & value;
    // if value is 1
    if (countBits(valueInIndex) == 1) {
        printf("Value in index is: %d\n", countBits(valueInIndex));
        return valueInIndex;
    }
    // if value is zero
    printf("Value in index is: %d\n", countBits(valueInIndex));
    return valueInIndex;
}

unsigned int swapBits(unsigned int value, int index1, int index2) {
    unsigned int value1 = getValueFromIndex(value, index1); // the 32 bit 
    displayBits(value1);
    unsigned int value2 = getValueFromIndex(value, index2);
    displayBits(value2);
    unsigned int newVal = value;

    if (countBits(value1) == countBits(value2)) // if the values are equal ( 0,0 or 1,1 d- nothing)
        return value;

    // if the values are different make them opposite using XOR
    newVal = value ^ value1;
    newVal = value ^ value2;
    displayBits(newVal);
    return newVal;
}

void main()
{
    unsigned int value = 5;

    printf("--- Task 1 ---\n");

    // Check that Display bits function works
    printf(" Original Number \n");
    displayBits(value);

    // Check that Task 1 works
    unsigned int result = inverBitsUsingXor(value);

    printf("\n After XOR Invert \n");
    displayBits(result);

    printf("\n--- Task 2 ---\n");

    // Check that CountBits actually counts the set up '1' bits.
    printf("\n CountBits Checking \n");
    unsigned int num1 = 75;
    displayBits(num1);

    printf("\n");
    unsigned int num2 = countBits(num1);
    printf("number of bits %u ", num2);

    // Check that Task 2 works
    unsigned int value1 = 74;
    unsigned int value2 = 15;
    printf("\n Values for task 2 are: \n");
    displayBits(value1);
    displayBits(value2);
    int hammingDistance = hammingDistanceCalculator(value1, value2);
    printf("\n The hamming distance is : %d\n", hammingDistance);

    printf("\n--- Task 3 ---\n");
    int index1 = 2;
    int index2 = 0;
    unsigned int swappedValue = swapBits(value2, index1, index2);
    displayBits(swappedValue);
    printf("\n");

}

