#include <stdio.h>
#include <math.h>

void displayBits( unsigned value );
unsigned int inverBitsUsingXor(unsigned int value);
int hammingDistance(unsigned int a, unsigned int b);
unsigned int countBits(unsigned int num);
unsigned int swapBits(unsigned int value, int index1, int index2);
unsigned int manipulateBits(unsigned int value, int index1, int index2, int index3);

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
    int newIndex1 = 31 - index1;
    int newIndex2 = 31 - index2;
    unsigned int value1 = getValueFromIndex(value, newIndex1); // the 32 bit 
    displayBits(value1);
    unsigned int value2 = getValueFromIndex(value, newIndex2);
    displayBits(value2);
    unsigned int newVal = value;

    if (countBits(value1) == countBits(value2)) { // if the values are equal ( 0,0 or 1,1 d- nothing)
        printf("The swapped value is: ");
        displayBits(value);
        return value;
    }

    // if the values are different make them opposite using XOR
    newVal = value ^ value1;
    newVal = newVal ^ value2;
    printf("The swapped value is: ");
    displayBits(newVal);
    return newVal;
}

// Task 4
unsigned int manipulateBits(unsigned int value, int index1, int index2, int index3) {
    // set index from left to right
    int newIndex1 = 31 - index1;
    int newIndex2 = 31 - index2;
    int newIndex3 = 31 - index3;

    unsigned int newValue = value;

    unsigned int newIndex1Value = getValueFromIndex(value, newIndex1);
    unsigned int newIndex2Value = getValueFromIndex(value, newIndex2);
    unsigned int newIndex3Value = getValueFromIndex(value, newIndex3);

    // Task 4.1 - set index1 bit to '1'
    if (countBits(newIndex1Value) == 0) {
        unsigned int mask = pow(2, newIndex1);
        newValue = value | mask; // newIndex1Value stands as a mask, and than OR to flip the inde
        printf("After 4.1 task value is: ");
        displayBits(newValue);
    }

    // Task 4.2 - set index 2 bit to '0'
    if (countBits(newIndex2Value) == 1) {
        unsigned int mask = 0xFFFFFFFF;
        mask = mask ^ newIndex2Value;
        newValue = newValue & mask; // turn off the index2 bit
        printf("After 4.2 task value is: ");
        displayBits(newValue);
    }

    // Task 4.3 - flip index3 bit
    newValue = newValue ^ newIndex3Value; // flip the bit value using XOR
    printf("After 4.3 task value is: ");
    displayBits(newValue);

    return newValue;
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
    printf("\nexample for non-same indexes\n");
    int index1 = 2;
    int index2 = 30;
    unsigned int swappedValue = swapBits(value2, index1, index2);

    printf("\n--- Task 4 ---\n");
    printf("\nThe given value is: \n");
    displayBits(value2);
    unsigned int manipulatedValue = manipulateBits(value2, 27, 28, 29);
    displayBits(manipulatedValue);
}

